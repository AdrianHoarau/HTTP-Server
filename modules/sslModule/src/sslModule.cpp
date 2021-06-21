/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** sslModule.cpp
*/

#include "sslModule.hpp"
#include <memory>
#include <cstring>

sslModule::sslModule() : ASocketHandler()
{
}

void sslModule::processRequest([[maybe_unused]] HTTP::HTTPObject& req)
{
}

void sslModule::init([[maybe_unused]] const std::string& path)
{
}

moduleType sslModule::getModuleType() const
{
    return (moduleType::SSL_MODULE);
}

void sslModule::prepareSocketHandler(boost::asio::io_context& ioContext, const moduleManager& modManager, boost::asio::ssl::context& ctx)
{
    _socket = std::make_shared<sslSocket>(ioContext, ctx);
    _reqManager->addModuleManager(modManager);
}

void sslModule::start()
{
    std::memset(_data, '\0', BUFFER_SIZE);
    auto this_shared = shared_from_this();
    _socket->async_handshake(boost::asio::ssl::stream_base::server,
    [=](const boost::system::error_code& err)
        {
            this_shared->handleHandshake(err);
        }
    );
}

boost::asio::basic_socket<boost::asio::ip::tcp>& sslModule::getSocket()
{
    return (_socket->lowest_layer());
}

void sslModule::handleHandshake(const boost::system::error_code& error)
{
    if (!error) {
        std::cout << "Handshake Done!" << std::endl;
        auto this_shared = shared_from_this();
        _socket->async_read_some(boost::asio::buffer(_data, BUFFER_SIZE),
        [=](const boost::system::error_code& err, size_t bytesTransferred)
            {
                this_shared->handleRead(err, bytesTransferred);
            }
        );
    }
    else {
        std::cout << "Session ended ..." << std::endl;
        if (this) {
            close();
        }
    }
}

void sslModule::reset(void)
{
    std::memset(_data, '\0', BUFFER_SIZE);
    auto this_shared = shared_from_this();
    _socket->async_read_some(boost::asio::buffer(_data, BUFFER_SIZE),
    [=](const boost::system::error_code& err, size_t bytesTransferred)
        {
            this_shared->handleRead(err, bytesTransferred);
        }
    );
}

void sslModule::handleRead(const boost::system::error_code& err, [[maybe_unused]] size_t bytesTransferred)
{
    if (_alive == false) {
        close();
        return;
    }
    if (!err) {
        std::string req(_data);
        if (req.empty()) {
            reset();
            return;
        }
        std::cout << "ssl :";
        std::cout << req << std::endl;
        std::thread reqThread(static_cast<void (requestManager::*)(const std::string&, sslSocket&)>(&requestManager::launchRequest), _reqManager, std::ref(req), std::ref(*_socket));
        if (reqThread.joinable() == true)
            reqThread.join();
        // boost::asio::write(*_socket.get(), boost::asio::buffer("HTTP/1.1 200 OK\n", 17));
        reset();
    } else {
        std::cerr << "error: " << err.message() << std::endl;
        close();
    }
}

void sslModule::close()
{
    if (_socket->lowest_layer().is_open() == true)
        _socket->lowest_layer().close();
}

#if defined (_WIN32)
    
    extern "C"  __declspec(dllexport)
    void *entryPoint()
    {
        return (new std::shared_ptr<sslModule>(new sslModule));
    }

#else

    extern "C" std::shared_ptr<IModule> entryPoint()
    {
        return (std::make_shared<sslModule>());
    }

#endif
