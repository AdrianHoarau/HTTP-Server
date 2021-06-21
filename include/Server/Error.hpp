/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** Error.hpp
*/


#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <fstream>

class Error : public std::exception
{
    private:
        const std::string _message;

    public:
        Error(std::string const& message);
        Error(const Error& other) = default;
        const char *what() const noexcept override;
        Error& operator=(const Error& other) = default;
        ~Error() = default;
};

class ErrorDLLoader : public Error
{
    public:
        ErrorDLLoader(const std::string& err);
        ErrorDLLoader(const ErrorDLLoader& other) = default;
        ErrorDLLoader& operator=(const ErrorDLLoader& other) = default;
        ~ErrorDLLoader() = default;
};

class ErrorJsonReader : public Error
{
    public:
        ErrorJsonReader(const std::string& err);
        ErrorJsonReader(const ErrorJsonReader& other) = default;
        ErrorJsonReader& operator=(const ErrorJsonReader& other) = default;
        ~ErrorJsonReader() = default;
};

class ErrorBadConfigPath : public ErrorJsonReader 
{
    public:
        ErrorBadConfigPath();
        ErrorBadConfigPath(const ErrorBadConfigPath& other) = default;
        ErrorBadConfigPath& operator=(const ErrorBadConfigPath& other) = default;
        ~ErrorBadConfigPath() = default;
};

class ErrorArgs : public Error
{
    public:
        ErrorArgs(const std::string& err);
        ErrorArgs(const ErrorArgs& other) = default;
        ErrorArgs& operator=(const ErrorArgs& other) = default;
        ~ErrorArgs() = default;
};

class ErrorNbArgs : public ErrorArgs
{
    public:
        ErrorNbArgs();
        ErrorNbArgs(const ErrorNbArgs& other) = default;
        ErrorNbArgs& operator=(const ErrorNbArgs& other) = default;
        ~ErrorNbArgs() = default;
};

class ErrorConfigPath : public ErrorArgs
{
    public:
        ErrorConfigPath();
        ErrorConfigPath(const ErrorConfigPath& other) = default;
        ErrorConfigPath& operator=(const ErrorConfigPath& other) = default;
        ~ErrorConfigPath() = default;
};

class ErrorDirPath : public ErrorArgs
{
    public:
        ErrorDirPath();
        ErrorDirPath(const ErrorDirPath& other) = default;
        ErrorDirPath& operator=(const ErrorDirPath& other) = default;
        ~ErrorDirPath() = default;
};

/** HTTPObject Error classes **/

class ErrorHTTPObject : public Error
{
    public:
        ErrorHTTPObject(const std::string& err);
        ErrorHTTPObject(const ErrorHTTPObject& other) = default;
        ErrorHTTPObject& operator=(const ErrorHTTPObject& other) = default;
        ~ErrorHTTPObject() = default;
};

class ErrorBadRequest : public ErrorHTTPObject
{
    public:
        ErrorBadRequest(const std::string& err);
        ErrorBadRequest(const ErrorBadRequest& other) = default;
        ErrorBadRequest& operator=(const ErrorBadRequest& other) = default;
        ~ErrorBadRequest() = default;
};

class ErrorRequestParams : public ErrorHTTPObject
{
    public:
        ErrorRequestParams(const std::string& err);
        ErrorRequestParams(const ErrorRequestParams& other) = default;
        ErrorRequestParams& operator=(const ErrorRequestParams& other) = default;
        ~ErrorRequestParams() = default;
};

class ErrorContentSize : public ErrorBadRequest
{
    public:
        ErrorContentSize();
        ErrorContentSize(const ErrorContentSize& other) = default;
        ErrorContentSize& operator=(const ErrorContentSize& other) = default;
        ~ErrorContentSize() = default;
};

class ErrorNoHost : public ErrorBadRequest
{
    public:
        ErrorNoHost();
        ErrorNoHost(const ErrorNoHost& other) = default;
        ErrorNoHost& operator=(const ErrorNoHost& other) = default;
        ~ErrorNoHost() = default;
};

/** Config File **/

class ErrorConfigFile : public Error
{
    public:
        ErrorConfigFile(const std::string& err);
        ErrorConfigFile(const ErrorConfigFile& other) = default;
        ErrorConfigFile& operator=(const ErrorConfigFile& other) = default;
        ~ErrorConfigFile() = default;
};

class ErrorConfigTag : public ErrorConfigFile
{
    public:
        ErrorConfigTag();
        ErrorConfigTag(const ErrorConfigTag& other) = default;
        ErrorConfigTag& operator=(const ErrorConfigTag& other) = default;
        ~ErrorConfigTag() = default;
};

class ErrorConfigSo : public ErrorConfigFile
{
    public:
        ErrorConfigSo();
        ErrorConfigSo(const ErrorConfigSo& other) = default;
        ErrorConfigSo& operator=(const ErrorConfigSo& other) = default;
        ~ErrorConfigSo() = default;
};

class ErrorConfigPhpFile : public ErrorConfigFile
{
    public:
        ErrorConfigPhpFile();
        ErrorConfigPhpFile(const ErrorConfigPhpFile& other) = default;
        ErrorConfigPhpFile& operator=(const ErrorConfigPhpFile& other) = default;
        ~ErrorConfigPhpFile() = default;
};

class ErrorConfigDefault : public ErrorConfigFile
{
    public:
        ErrorConfigDefault();
        ErrorConfigDefault(const ErrorConfigDefault& other) = default;
        ErrorConfigDefault& operator=(const ErrorConfigDefault& other) = default;
        ~ErrorConfigDefault() = default;
};
#endif /* !ERROR_HPP_ */
