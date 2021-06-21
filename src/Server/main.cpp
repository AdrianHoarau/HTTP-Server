/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** main.cpp
*/

#include <nlohmann/json.hpp>
#include <iostream>
#include "Error.hpp"
#include "serverCore.hpp"
#include "pathHandler.hpp"
#include "HTTPObject.hpp"
#include <openssl/ssl.h>
#include <boost/asio/ssl.hpp>

int main(int ac, char **av)
{
    if (ac < 3) {
        std::cout << "./zia [configPath] [dirModulesPath]" << std::endl;
        std::cout << "[configPath]: Path to the JSON configuration file." << std::endl;
        std::cout << "[dirModulesPath]: Path to the modules directory." << std::endl;
        return (0);
    }
    try
    {
        pathHandler hdl(pathType::REGULAR_FILE);
        pathHandler hdlDir(pathType::DIR);
        if (ac > 3)
            throw ErrorNbArgs();
        else if (ac == 3) {
            hdl.setPath(av[1]);
            hdlDir.setPath(av[2]);
        }
        if (hdl.isFileValid() == false)
            throw ErrorConfigPath();
        else if (hdlDir.isDirValid() == false)
            throw ErrorDirPath();
        boost::asio::io_context ioContext;
        serverCore server(ioContext, hdl.getPath(), hdlDir.getPath());
        server.start();
    } catch (Error& e) {
        std::cerr << e.what() << std::endl;
        return (84);
    } catch (nlohmann::json::exception const& jsonErr) {
        std::cout << jsonErr.what();
        return (84);
    } catch(boost::system::system_error& e) {
        std::cout << e.what() << std::endl;
        return (84);
    }
    return (0);
}