/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** phpCgiModule
*/

#ifndef PHPCGIMODULE_HPP_
#define PHPCGIMODULE_HPP_

#include "IModule.hpp"
#include "LinuxCmdExec.hpp"
#include "WindowsCmdExec.hpp"
#include <fstream>
#include <memory>
#include <filesystem>
#include <cstring>

/** @class phpCgiModule
*  @brief The phpCgiModule class is a class that will execute PHP scripts as CGI
*/
class phpCgiModule : public IModule {
    public:
        /** @brief Default ctor of phpCgiModule */
        phpCgiModule();
        /** @brief This function will be call by the server and will exec our different methods
        *  @param request send by the server, that will contain all information
        */
        void processRequest(HTTP::HTTPObject& req);
        /** @brief This function will return the module type like PHPCGI, SSL_MODULE, SNAKE, FILE_SERVER
        *  @return module type PHPCGI
        */
        moduleType getModuleType() const;
        /** @brief Ctor copy of phpCgiModule
        *  @param other phpCgiModule to copy
        */
        phpCgiModule(const phpCgiModule& other) = default;
        /** @brief Default overloaded '=' operator of phpCgiModule */
        phpCgiModule& operator=(const phpCgiModule& other) = default;
        /** @brief Default dtor of phpCgiModule */
        ~phpCgiModule() = default;
        /** @brief This function will init the path of directory PHP script
        *  @param path of directory PHP script
        */
        void init(const std::string& path);
        /** @brief This function will sort and fill args of the request param
        *  @param key of sort
        *  @param request send by the server, that will contain all information
        *  @param conditional param to take args if he's true
        *  @param array that will be sort at the end
        */
        void fillArg(const std::string& arg, HTTP::HTTPObject& req, bool& take, std::vector <std::string>& names);
    protected:
    private:
        /** @brief The path of the directory PHP scripts */
        std::string _path;
        /** @brief This function will exec the cmd given as parameter
        *  @param cmd to exec, like "php-cgi test.php"
        */
        std::string exec(const std::string& cmd);
        /** @brief Map of our php methods */
        std::unordered_map<std::string, void (phpCgiModule::*)(HTTP::HTTPObject& req)> _methods;
        /** @brief This function will exec the helloWord script
        *  @param request send by the server, that will contain all information
        */
        void helloWorld(HTTP::HTTPObject& req);
        /** @brief This function will exec the webName script
        *  @param request send by the server, that will contain all information
        */
        void webName(HTTP::HTTPObject& req);
        /** @brief This function will exec the calendar script
        *  @param request send by the server, that will contain all information
        */
        void calendar(HTTP::HTTPObject& req);
        /** @brief This function will check if the execution work fine or fill the right error code
        *  @param output of the php execution script
        *  @param request send by the server, that will contain all information
        */
        void setExecBody(const std::string& output, HTTP::HTTPObject& req);
        LinuxCmdExec _linuxExec;
        WindowsCmdExec _windowsExec;
};


#endif /* !PHPCGIMODULE_HPP_ */
