/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** tcpConnection
*/

#ifndef TCPCONNECTION_HPP_
#define TCPCONNECTION_HPP_

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "ASocketHandler.hpp"

/** @class tcpConnection
    * @brief The class tcpConnection allows us to handle a simple tcp connection
*/
class tcpConnection : public ASocketHandler {
    public:
        /** @brief Ctor of SignalHandler */
        tcpConnection();
        /** @brief This function launches the asynchronous usage of the socket */
        void start();
        /** @brief This function will prepare the socketHandler to be able to work autonomously
            *  @param ioContext Context of the accepted connection, needed to create a socket
            *  @param modManager Class moduleManager
            *  @param ctx Boost asio ssl context, useful for the ssl certificate
        */
        void prepareSocketHandler(boost::asio::io_context& ioContext, const moduleManager& modManager, boost::asio::ssl::context& ctx);
        /** @brief This function will return the socket of the ISocketHandler
            * @return boost::asio::basic_socket<boost::asio::ip::tcp> The lowest layer of a tcp socket
        */
        boost::asio::basic_socket<boost::asio::ip::tcp>& getSocket();
        /** @brief This function closes the socket manually */
        void close();
        /** @brief This function will be the callback called after each read on the socket
            *  @param err It contains the value of the potential error, false if there is no error
            *  @param bytesTransferred It contains the number of bytes that has been readed
        */
        void handleRead(const boost::system::error_code& err, size_t bytesTransferred);
        /** @brief This functions will start the ssl handshake
            *  @param err It contains the value of the potential error, false if there is no error
        */
        void handleHandshake(const boost::system::error_code& error);
        /** @brief Default copy ctor of tcpConnection */
        tcpConnection(const tcpConnection& other) = default;
        /** @brief Default overloaded '=' operator of tcpConnection */
        tcpConnection& operator=(const tcpConnection& other) = default;
        /** @brief Dtor of tcpConnection */
        ~tcpConnection() = default;
    private:
        /** @brief Shared pointer of a boost asio tcp socket */
        std::shared_ptr<boost::asio::ip::tcp::socket> _socket;
};
#endif /* !TCPCONNECTION_HPP_ */