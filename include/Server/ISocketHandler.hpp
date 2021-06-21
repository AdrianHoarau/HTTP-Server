/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** ISocketHandler
*/

#ifndef ISOCKETHANDLER_HPP_
#define ISOCKETHANDLER_HPP_

#include <openssl/ssl.h>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <string>
#include "moduleManager.hpp"
#include "processingList.hpp"
/** @class ISocketHandler
    *  @brief The ISocketHandler class is an interface class that gather common methods between all class considered as socketHandlers
*/
class ISocketHandler : public std::enable_shared_from_this<ISocketHandler> {
    public:
        /** @brief Dtor of ISocketHandler (virtual cause Interface) */
        virtual ~ISocketHandler() = default;
        /** @brief This function will prepare the socketHandler to be able to work autonomously
            *  @param ioContext Context of the accepted connection, needed to create a socket
            *  @param modManager Class moduleManager
            *  @param ctx Boost asio ssl context, useful for the ssl certificate
        */
        virtual void prepareSocketHandler(boost::asio::io_context& ioContext, const moduleManager& modManager, boost::asio::ssl::context& ctx) = 0;
        /** @brief This function will reload the modules and the processing list used by the appropriate ISocketHandler
            *  @param modulePaths Map containing the type of the module and on the other hand containing the exact path to its .so
            *  @param cgiPath Exact path to the dir where CGI scripts are stocked
            *  @param processList Class processingList
        */
        virtual void reload(std::unordered_map<moduleType, std::string>& modulePaths, const std::string& cgiPath, const processingList& processList) = 0;
        /** @brief This function launches the asynchronous usage of the socket */
        virtual void start() = 0;
        /** @brief This function will return the socket of the ISocketHandler
            * @return boost::asio::basic_socket<boost::asio::ip::tcp> The lowest layer of a tcp socket
        */
        virtual boost::asio::basic_socket<boost::asio::ip::tcp>& getSocket() = 0;
        /** @brief This function notifies the socket that it is destroyed from the server */
        virtual void killSocket() = 0;
        /** @brief This function closes the socket manually */
        virtual void close() = 0;
        /** @brief This function will be the callback called after each read on the socket
            *  @param err It contains the value of the potential error, false if there is no error
            *  @param bytesTransferred It contains the number of bytes that has been readed
        */
        virtual void handleRead(const boost::system::error_code& err, size_t bytesTransferred) = 0;
        /** @brief This functions will start the ssl handshake
            *  @param err It contains the value of the potential error, false if there is no error
        */
        virtual void handleHandshake(const boost::system::error_code& error) = 0;
    private:
};

#endif /* !ISOCKETHANDLER_HPP_ */
