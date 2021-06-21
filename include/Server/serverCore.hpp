/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** serverCore
*/

#ifndef SERVERCORE_HPP_
#define SERVERCORE_HPP_

#include <ctime>
#include <iostream>
#include <string>
#include "tcpConnection.hpp"
#include "SignalHandler.hpp"
#include "configHandler.hpp"
#include "INetwork.hpp"
#include <filesystem>
#include <chrono>

/** @class serverCore
    * @brief The serverCore manages the acceptance of connections, and give to the sockerHandlers the necessary information
*/  
class serverCore : public INetwork {
    public:
        /** @brief Ctor of processingList
            * @param ioContext Context of the accepted connection, needed to create a socket
            * @param configPath Exact path to the config file
            * @param dirPath Exact path to the directory containing the shared libraries
        */
        serverCore(boost::asio::io_context& ioContext, const std::string& configPath, const std::string& dirPath);
        /** @brief Start the network functionality */
        void start();
        /** @brief Stop the network functionality */
        void stop();
        /** @brief Default copy ctor of serverCore */
        serverCore(const serverCore& other) = default;
        /** @brief Default overloaded '=' operator of serverCore */
        serverCore& operator=(const serverCore& other) = default;
        /** @brief Dtor of serverCore */
        ~serverCore() = default;
    private:
        /** @brief Check if the way to handle socket has been changed, this function must be call before the call reload of Json File in order to save, and then recalled to update the way to handle sockets if needed.
            * @param before True if it's called before the reload of Json, else False 
        */
        void checkSocketChanges(const bool before);
        /** @brief Start connection's network functionality */
        void startAccept();
        /** @brief This function will be the callback called after each acceptance on the acceptor
            * @param newConnection Shared pointer corresponding to the new socketHandler created
            * @param error It contains the value of the potential error, false if there is no error
        */
        void handleAccept(std::shared_ptr<ISocketHandler>& newConnection, const boost::system::error_code& error);
        /** @brief This function will be the callback called each n seconds to catch CTRL+C or to check change of the config file 
            * @param configPath Exact path to the config file
            * @param error It contains the value of the potential error, false if there is no error
        */
        void serverEndHandler(const std::string& configPath, const boost::system::error_code& error);
        /** @brief Boost asio acceptor, allows us to accept connection */
        boost::asio::ip::tcp::acceptor _acceptor;
        /** @brief configPaths structure */
        configPaths _paths;
        /** @brief SignalHandler class */
        SignalHandler _sigHandler;
        /** @brief Boost asio timer, allows us to call a callback function each n seconds */
        boost::asio::steady_timer _t;
        /** @brief Boost asio ssl context, useful for the ssl certificate */
        boost::asio::ssl::context _ctx;
        /** @brief Date of the last update of the config file */
        std::chrono::time_point<std::filesystem::__file_clock> _lastUpdate;
        /** @brief configHandler class */
        configHandler _confHandler;
        /** @brief moduleManager class */
        moduleManager _modManager;
        /** @brief Vector of shared pointer of socketHandlers, it stocks all entities of ISocketHandler created while accepting with the acceptor */
        std::vector<std::shared_ptr<ISocketHandler>> _sockHandlers;
};

#endif /* !SERVERCORE_HPP_ */
