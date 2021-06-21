/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** requestManager
*/

#include "requestManager.hpp"

requestManager::requestManager()
{
}


void requestManager::addModuleManager(const moduleManager& modManager)
{
    _modManager = modManager;
}

void requestManager::launchRequest(const std::string& req, boost::asio::ip::tcp::socket& socket)
{
    try {
        processingList cpyList = _processList;
        HTTP::HTTPObject request(req);
        moduleType type = cpyList.getCurrentType();

        while (type != moduleType::NONE) {
            _modManager.getModule(type)->processRequest(request);
            cpyList.remove();
            type = cpyList.getCurrentType();
        }
        // request.setHTTPCode("200");
        auto answer = request.createResponse().toString();
        boost::asio::write(socket, boost::asio::buffer(answer));
        // socket.send(boost::asio::buffer(answer));
    } catch (ErrorHTTPObject& e) {
        boost::asio::write(socket, boost::asio::buffer("400 Bad Request Error"));
        return;
    }
}

void requestManager::launchRequest(const std::string& req, boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket)
{
    try {
        processingList cpyList = _processList;
        HTTP::HTTPObject request(req);
        moduleType type = cpyList.getCurrentType();

        while (type != moduleType::NONE) {
            std::cout << type << std::endl;
            _modManager.getModule(type)->processRequest(request);
            cpyList.remove();
            type = cpyList.getCurrentType();
        }
        // request.setHTTPCode("200");
        auto answer = request.createResponse().toString();
        boost::asio::write(socket, boost::asio::buffer(answer));
        // socket.send(boost::asio::buffer(answer));
    } catch (ErrorHTTPObject& e) {
        std::cout << e.what() << std::endl;
        boost::asio::write(socket, boost::asio::buffer("400 Bad Request Error"));
        return;
    }
}

void requestManager::reload(std::unordered_map<moduleType, std::string>& modulePaths, const processingList& processList, const std::string& cgiPath)
{
    _modManager.loadLoaders(modulePaths);
    _modManager.loadModules();
    _processList = processList;
    if (_modManager.doesModuleExist(moduleType::PHPCGI))
        _modManager.getModule(moduleType::PHPCGI)->init(cgiPath);
}