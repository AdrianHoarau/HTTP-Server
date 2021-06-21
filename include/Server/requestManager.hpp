/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** requestManager
*/

#ifndef REQUESTMANAGER_HPP_
#define REQUESTMANAGER_HPP_

#include <memory>
#include <boost/asio.hpp>
#include "processingList.hpp"
#include "moduleManager.hpp"
#include <openssl/ssl.h>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

/** @class requestManager
    *  @brief The requestManager handles the request and send it through modules
*/
class requestManager {
    public:
        /** @brief Ctor of requestManager */
        requestManager();
         /** @brief This function will reload the modules and the processing list
            *  @param modulePaths Map containing the type of the module and on the other hand containing the exact path to its .so
            *  @param cgiPath Exact path to the dir where CGI scripts are stocked
            *  @param processList Class processingList
        */
        void reload(std::unordered_map<moduleType, std::string>& modulePaths, const processingList& processList, const std::string& cgiPath);
        /** @brief This function will copy the moduleManager to stock it
            *  @param modManager Class moduleManager
        */
        void addModuleManager(const moduleManager& modManager);
        /** @brief This function will receive the request as string, put it in HTTPObject, and make it go through the modules in the same order as in the processingList
            *  @param req String containing the request that has been received
            *  @param socket Boost asio tcp socket
        */
        void launchRequest(const std::string& req, boost::asio::ip::tcp::socket& socket);
        /** @brief This function will receive the request as string, put it in HTTPObject, and make it go through the modules in the same order as in the processingList
            *  @param req String containing the request that has been received
            *  @param socket Boost asio tcp ssl socket
        */
        void launchRequest(const std::string& req, boost::asio::ssl::stream<boost::asio::ip::tcp::socket>& socket);
        /** @brief Default copy ctor of requestManager */
        requestManager(const requestManager& other) = default;
        /** @brief Default overloaded '=' operator of requestManager */
        requestManager& operator=(const requestManager& other) = default;
        /** @brief Dtor of requestManager */
        ~requestManager() = default;
    private:
        /** @brief Class moduleManager */
        moduleManager _modManager;
        /** @brief Class processingList */
        processingList _processList;
        
};

#endif /* !REQUESTMANAGER_HPP_ */
