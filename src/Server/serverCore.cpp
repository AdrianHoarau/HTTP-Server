/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** serverCore
*/

#include "serverCore.hpp"
#include "tcpConnection.hpp"


serverCore::serverCore(boost::asio::io_context& ioContext, const std::string& configPath, const std::string& dirPath) :
_acceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 8084)), _paths({dirPath ,configPath}), _sigHandler(), _t(ioContext, boost::asio::chrono::seconds(3)), _ctx(boost::asio::ssl::context::sslv23),
_confHandler(_paths)
{
    _modManager.loadLoaders(_confHandler.getListModules());
    std::filesystem::path p(_paths.configPath);
    if (std::filesystem::exists(p)){
        auto ftime = std::filesystem::last_write_time(p);
        _lastUpdate = ftime;
    } else
        throw ErrorConfigPath();
    _t.async_wait(boost::bind(&serverCore::serverEndHandler, this, _paths.configPath, boost::asio::placeholders::error));
    _ctx.set_options(
        boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_sslv2
        | boost::asio::ssl::context::single_dh_use);
    // _ctx.set_password_callback(boost::bind(&server::get_password, this));
    _ctx.use_certificate_chain_file(_confHandler.getCertificatePath());
    _ctx.use_private_key_file(_confHandler.getCertificatePath(), boost::asio::ssl::context::pem);
    startAccept();
}

void serverCore::startAccept()
{
    try {
        if (_modManager.doesLoaderExist(moduleType::SSL_MODULE) == true) {
            auto sslMod = _modManager.getNewModule(moduleType::SSL_MODULE);
            if (std::dynamic_pointer_cast<ISocketHandler>(sslMod) != NULL) {
                std::cout << "ssl Creation" << std::endl;
                _sockHandlers.push_back(std::dynamic_pointer_cast<ISocketHandler>(sslMod));
            }
        } else {
            std::cout << "tcp Creation" << std::endl;
            _sockHandlers.push_back(std::make_shared<tcpConnection>());
        }
        _sockHandlers.back()->prepareSocketHandler(_acceptor.get_executor().context(), _modManager, _ctx);
        _sockHandlers.back()->reload(_confHandler.getListModules(), _confHandler.getCgiPath(), _confHandler.getCopyProcessList());
        _acceptor.async_accept(_sockHandlers.back()->getSocket(), boost::bind(&serverCore::handleAccept, 
        this, _sockHandlers.back(),boost::asio::placeholders::error));
    } catch (Error& e) {
        std::cout << "Fail to connect because " << e.what() << std::endl;
        _acceptor.async_wait(
        boost::asio::ip::tcp::acceptor::wait_read,
        boost::bind(&serverCore::startAccept, this));
    }
}

void serverCore::handleAccept(std::shared_ptr<ISocketHandler>& newConnection, const boost::system::error_code& error)
{
    if (!error)
    {
        try {
            newConnection->start();
        } catch (Error& e) {
            std::cout << e.what() << std::endl;
        }
    }
    startAccept();
}

void serverCore::start()
{
    _acceptor.get_io_service().run();
}

void serverCore::checkSocketChanges(const bool before)
{
    static moduleType save = moduleType::NONE;

    if (before == true) {
        if (_modManager.doesLoaderExist(moduleType::SSL_MODULE))
            save = moduleType::SSL_MODULE;
        else
            save = moduleType::NONE;
    } else {
        if ((_modManager.doesLoaderExist(moduleType::SSL_MODULE) && save == moduleType::NONE) || (_modManager.doesLoaderExist(moduleType::SSL_MODULE) == false && save == moduleType::SSL_MODULE)) {
            for (auto& sock : _sockHandlers) 
                sock->killSocket();
            _sockHandlers.clear();
        }
    }
}

void serverCore::serverEndHandler(const std::string& configPath, const boost::system::error_code& err)
{
    if (err)
        return;
    checkSocketChanges(true);
    std::filesystem::path p(configPath);
    if (std::filesystem::exists(p)) {
        auto ftime = std::filesystem::last_write_time(p);
        if (_lastUpdate != ftime) {
            _confHandler.reload();
            _modManager.loadLoaders(_confHandler.getListModules());
            checkSocketChanges(false);
            for (auto& sock : _sockHandlers) 
                sock->reload(_confHandler.getListModules(), _confHandler.getCgiPath(), _confHandler.getCopyProcessList());
            _lastUpdate = ftime;
        }
    } else
        throw ErrorConfigPath();
    if (_sigHandler.isInterrupted() == true) {
        std::cerr << "Server's leaving." << std::endl;
        stop();
    }
    _t.expires_at(_t.expires_at() + boost::asio::chrono::seconds(3));
    _t.async_wait(boost::bind(&serverCore::serverEndHandler, this, configPath, boost::asio::placeholders::error));
}

void serverCore::stop()
{
    if (_acceptor.is_open() == true)
        _acceptor.get_io_service().stop();
}