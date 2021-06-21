/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** Error.cpp
*/

#include "Error.hpp"

Error::Error(const std::string& err) : _message(err)
{
}

const char *Error::what() const noexcept
{
    return (_message.c_str());
}

ErrorDLLoader::ErrorDLLoader(const std::string& err) : Error(err)
{
}

ErrorJsonReader::ErrorJsonReader(const std::string& err) : Error(err)
{
}

ErrorBadConfigPath::ErrorBadConfigPath() : ErrorJsonReader("Error: The given path isn't valid.")
{
}


ErrorArgs::ErrorArgs(const std::string& err) : Error(err)
{
}

ErrorNbArgs::ErrorNbArgs() : ErrorArgs("Error: wrong number of arguments.")
{
}

ErrorConfigPath::ErrorConfigPath(): ErrorArgs("Error: the default's path or the path given as argument isn't valid.")
{
}

ErrorDirPath::ErrorDirPath() : ErrorArgs("Error: the path given as argument isn't a directory.")
{
}

ErrorHTTPObject::ErrorHTTPObject(const std::string& err) : Error(err)
{
}

ErrorBadRequest::ErrorBadRequest(const std::string& err) : ErrorHTTPObject(err)
{
}

ErrorRequestParams::ErrorRequestParams(const std::string& err) : ErrorHTTPObject(err)
{
}

ErrorContentSize::ErrorContentSize() : ErrorBadRequest("Error: The content-length is not valid.")
{
}

ErrorNoHost::ErrorNoHost() : ErrorBadRequest("Error: No host was specified in the request headers")
{
}

ErrorConfigFile::ErrorConfigFile(const std::string& err) : Error(err)
{
}

ErrorConfigTag::ErrorConfigTag() : ErrorConfigFile("Error config file: one module name doesn't exist")
{
}

ErrorConfigSo::ErrorConfigSo() : ErrorConfigFile("Error config file: one module doesn't exist")
{
}

ErrorConfigPhpFile::ErrorConfigPhpFile() : ErrorConfigFile("Error config file: the config folder is not correct")
{
}

ErrorConfigDefault::ErrorConfigDefault() : ErrorConfigFile("Error config file: the default config is not correct")
{
}