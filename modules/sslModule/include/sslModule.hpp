/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** sslModule
*/

#ifndef SSLMODULE_HPP_
#define SSLMODULE_HPP_

#include "IModule.hpp"
#include "ASocketHandler.hpp"

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> sslSocket;

/** @class sslModule
    * @brief The class sslModule allows us to handle a ssl tcp connection, this class is also considered as a module
*/
class sslModule : public IModule, public ASocketHandler {
    public:
        /** @brief Ctor of sslModule */
        sslModule();
        /** @brief This function will be called each time a request is received
            *  @param req HTTPObject class filled with request's information
        */
        void processRequest(HTTP::HTTPObject& req);
        /** @brief This function will be called for each module after its creation
            *  @param path Needed path for the right operation of the module (optional)
        */
        void init(const std::string& path);
        /** @brief This function will return the moduleType of the current instance of IModule
            *  @return moduleType Type of module
        */
        moduleType getModuleType() const;
        /** @brief This function will prepare the socketHandler to be able to work autonomously
            *  @param ioContext Context of the accepted connection, needed to create a socket
            *  @param modManager Class moduleManager
            *  @param ctx Boost asio ssl context, useful for the ssl certificate
        */
        void prepareSocketHandler(boost::asio::io_context& ioContext, const moduleManager& modManager, boost::asio::ssl::context& ctx);
         /** @brief This function launches the asynchronous usage of the socket */
        void start();
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
        /** @brief Default copy ctor of sslModule */
        sslModule(const sslModule& other) = default;
        /** @brief Default overloaded '=' operator of sslModule */
        sslModule& operator=(const sslModule& other) = default;
        /** @brief Dtor of sslModule */
        ~sslModule() = default;
    private:
        /** @brief Restart the async read */
        void reset();
        /** @brief Shared pointer of a boost asio ssl tcp socket */
        std::shared_ptr<sslSocket> _socket;
};

#endif /* !SSLMODULE_HPP_ */
