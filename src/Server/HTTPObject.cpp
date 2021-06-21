/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud [WSL: Debian]
** File description:
** HTTPObject
*/

#include "HTTPObject.hpp"
#include "Error.hpp"

HTTP::HTTPObject::HTTPObject(const std::string& request, const HTTP::HTTPType& type)
try : _type(type), _httpCode("UNKNOWN"), _bodyContent("")
{
    parseRequest(request);
    checkContent();
    createHTTPCodesMap();

} catch(const ErrorHTTPObject& e)
{
    throw e;
}

HTTP::reqType& HTTP::HTTPObject::operator[](const HTTP::reqElem& elem)
{
    if (elem == HTTP::STARTLINES)
        return (_startLine);
    else if (elem == HTTP::HEADERS)
        return (_headers);
    else
        return (_body);
}

bool HTTP::HTTPObject::isKey(const reqElem& elem, const std::string& key)
{
    if (this->operator[](elem).count(key) == 0)
        return (false);
    return (true);
}

std::string HTTP::HTTPObject::getElemConcatContent(const reqElem& elem, const std::string& key, bool displayMode)
{
    std::string toReturn;

    if (!isKey(elem, key))
        return (toReturn);
    for (std::size_t i = 0; i != this->operator[](elem)[key].size(); i++) {
        if (!this->operator[](elem)[key][i].empty())
            toReturn += this->operator[](elem)[key][i];
        if (displayMode)
            toReturn += '\n';
    }
    return (toReturn);
}

void HTTP::HTTPObject::deleteElemContent(const reqElem& elem, const std::string& key, std::size_t pos)
{
    std::size_t size = 0;

    if (!isKey(elem, key) || (elem == HTTP::HEADERS && (key.compare("Content-Length") == 0)))
        return;
    size = this->operator[](elem)[key].size();
    if (size > 0) {
        if (pos == std::string::npos) {
            for (std::size_t i = 0; i != size; i++)
                this->operator[](elem)[key][i].clear();
        }
        else if (pos <= size)
            this->operator[](elem)[key][pos].clear();
    }
}

void HTTP::HTTPObject::modifyElemContent(const reqElem& elem, const std::string& key, const std::string& newVal, [[maybe_unused]]std::size_t pos)
{
    std::size_t size = 0;

    if (!isKey(elem, key) || (elem == HTTP::HEADERS && (key.compare("Content-Length") != 0)))
        return;
    size = this->operator[](elem)[key].size();
    for (std::size_t i = 0; i != size; i++) {
        this->operator[](elem)[key][i] = newVal;
    }
}

void HTTP::HTTPObject::parseRequest(const std::string& request)
{
    std::string newReq;

    if (request.empty())
        throw (ErrorBadRequest("Error: Request is empty."));
    newReq = decodeRequest(request);
    parseStartLine(newReq);
    parseHeaders(newReq);
    parseBody(newReq);
    if (_startLine["Method"][0].compare("PUT") == 0 || _startLine["Method"][0].compare("PUT") == 0) {
        _params.clear();
        createParamsMap(_body["Body"][0]);
    }
}

void HTTP::HTTPObject::createParamsMap(const std::string& strParams)
{
    std::vector<std::string> vec;
    std::string p1;
    std::string p2;
    std::size_t pos = 0;

    vec = strToStringVector(strParams, "&");
    // check if '/' after the arguments like this -> param=2&super=cool/roblox

    for (size_t i = 0; i != vec.size(); i++) {
        if (!vec.at(i).empty() && (vec.at(i).find("=") != std::string::npos)) {
            pos = vec.at(i).find("=");
            p1 = vec.at(i).substr(0, pos);
            p2 = vec.at(i).substr(pos+1, vec.at(i).size()+pos);
            _params[p1] = p2;
        }
    }
}

HTTP::paramsMap& HTTP::HTTPObject::getParams()
{
    return (_params);
}

std::string HTTP::HTTPObject::decodeRequest(const std::string& request)
{
    std::string ret;
    char ch;
    std::size_t i = 0;
    unsigned int j = 0;

    for(; i < request.length(); i++){
        if (static_cast<int>(request[i]) == '%') {
            sscanf(request.substr(i+1,2).c_str(), "%x", &j);
            ch = static_cast<char>(j);
            ret += ch;
            i = i+2;
        }
        else
            ret += request[i];
    }
    return (ret);
}

void HTTP::HTTPObject::parseTarget(std::string& target)
{
    std::vector<std::string> vec;
    bool isParams = false;

    // maybe decode the target as it may be encoded and CHECK IF VALID
    if ((target.find('?') != std::string::npos)) {
        isParams = true;
        vec = strToStringVector(target, "?");
        _startLine["Target"].push_back(vec.at(1));
        target = vec.at(0);
    }
    vec = strToStringVector(target, "/");
    for (size_t i = 0; i != vec.size(); i++) {
        if (!vec.at(i).empty())
            _startLine["Target"].push_back(vec.at(i));
    }
    if (isParams) {
        createParamsMap(_startLine["Target"][1]);
        _startLine["Target"].erase((_startLine["Target"].begin() + 1));
    }
}

void HTTP::HTTPObject::parseStartLine(const std::string& request)
{
    std::string strRaw = request.substr(0, request.find_first_of('\n'));
    std::string strMethod = strRaw.substr(0, strRaw.find_first_of(' '));
    std::string strTarget = strRaw.substr(strRaw.find_first_of(' ')+1, (strRaw.find_last_of(' ')-strMethod.size()-1));
    std::string strVersion = strRaw.substr(strRaw.find_last_of(' ')+1, strRaw.size());

    if (strMethod.compare("GET") == 0 || strMethod.compare("POST") == 0 ||\
    strMethod.compare("DELETE") == 0 || strMethod.compare("PUT") == 0) {
        _startLine["Raw"].push_back(strRaw);
        _startLine["Method"].push_back(strMethod);
        _startLine["Target"].push_back(strTarget);
        parseTarget(strTarget);
        _startLine["Version"].push_back(strVersion);
    }
    else
        throw (ErrorBadRequest("Error: Unknown HTTP Method"));
}

std::vector<std::string> HTTP::HTTPObject::strToStringVector(const std::string& str, const std::string& delim)
{
    std::vector<std::string> toReturn;
    std::string word = "";

    if (str.find(delim) == std::string::npos) {
        toReturn.push_back(str);
        return (toReturn);
    }

    for (auto x : str)
    {
        if (x == delim.c_str()[0]) {
            if (word.compare(delim) != 0)
                toReturn.push_back(word);
            word = "";
        }
        else
            word = word + x;
    }
    if (word.compare(delim) != 0)
        toReturn.push_back(word);
    return (toReturn);
}

void HTTP::HTTPObject::parseHeaders(const std::string& request)
{
    std::size_t first = request.find_first_of('\n')+1;
    std::size_t last = request.find_last_of('\n');
    std::string header = request.substr(first, last - first + 1);
    std::vector<std::string> strs;
    std::string elem;
    std::string key;

    if (header.empty())
        throw ErrorBadRequest("Error: No header (bad formatting)");
    header[header.find_last_of('\n')] = '\0';
    _headers["Raw"].push_back(header);
    strs = strToStringVector(header, "\n");
    for (std::size_t i = 0; i < strs.size(); i++) {
        if (!strs[i].empty()) {
            elem = strs[i].substr(0, strs[i].find_first_of(':'));
            key = strs[i].substr(strs[i].find_first_of(':')+2, strs[i].size());
            if (!elem.empty() && !key.empty()) {
                _headers[elem].push_back(key);
                _headersOrderList.push_back(elem);
            }
        }
    }
}

HTTP::HTTPObject& HTTP::HTTPObject::createResponse(void)
{
    std::string strRes;

    clear();
    strRes = "HTTP/1.1 ";
    strRes += _httpCode+" ";
    strRes += getCodeDesc(_httpCode);
    _startLine["Raw"].push_back(strRes);
    _startLine["Version"].push_back("HTTP/1.1");
    _startLine["Code"].push_back(_httpCode);
    _startLine["Description"].push_back(getCodeDesc(_httpCode));
    _type = HTTP::RES;
    if (_bodyContent.empty()) {
        std::string defaultHtml1 = "<!DOCTYPE html><head><title>Zia</title></head><body><center><h1>HTTP ";
        defaultHtml1 += _httpCode+" "+_httpCodes[_httpCode]+"</h1></center></body>";
        _headers["Content-Length"].push_back(std::to_string(defaultHtml1.size()));
        _headersOrderList.push_back("Content-Length");
        _body["Body"].push_back(defaultHtml1);
        return (*this);
    }
    _headers["Content-Length"].push_back(std::to_string(_bodyContent.size()));
    _headersOrderList.push_back("Content-Length");
    _body["Body"].push_back(_bodyContent);
    return (*this);
}

void HTTP::HTTPObject::clear(void)
{
    _startLine.clear();
    _headers.clear();
    _headersOrderList.clear();
    _body.clear();
}

void HTTP::HTTPObject::parseBody(const std::string& request)
{
    std::string body = request.substr(request.find_last_of('\n')+1, request.size());
    if (!body.empty())
        _body["Body"].push_back(body);
}

std::string HTTP::HTTPObject::toString(void)
{
    std::string result;
    std::string s;

    result += getElemConcatContent(HTTP::STARTLINES, "Raw")+"\n";
    for (std::size_t i = 0; i < _headersOrderList.size(); ++i) {
        s = _headersOrderList[i];
        result += s+": "+getElemConcatContent(HTTP::HEADERS, s)+"\n";
    }
    if (!getElemConcatContent(HTTP::BODY, "Body").empty()) {
        for (auto& it: this->operator[](HTTP::BODY))
            result += "\n"+getElemConcatContent(HTTP::BODY, it.first);
    }
    return (result);
}

int HTTP::HTTPObject::checkContent(void)
{
    int contentLength = 0;
    int bodySize = 0;

    if (getElemConcatContent(HTTP::BODY, "Body").empty())
        return (0);
    if (getElemConcatContent(HTTP::HEADERS, "Host").empty())
        throw ErrorNoHost();
    if (getElemConcatContent(HTTP::HEADERS, "Content-Length").empty())
        throw ErrorBadRequest("Error: No 'Content-Length' field but with a body");
    contentLength = std::stoi(this->operator[](HTTP::HEADERS)["Content-Length"][0]);
    bodySize = getElemConcatContent(HTTP::BODY, "Body").size();
    if (contentLength < 0 || contentLength != bodySize)
        throw ErrorContentSize();
    return (0);
}

const std::string HTTP::HTTPObject::getCodeDesc(const std::string& code)
{
    if (_httpCodes.count(code) == 0)
        return ("UNKOWN");
    return (_httpCodes[code]);
}

void HTTP::HTTPObject::setHTTPCode(const std::string& newCode)
{
    if (_httpCodes.count(newCode) == 0)
        return;
    _httpCode = newCode;
}

void HTTP::HTTPObject::setBody(const std::string& newBody)
{
    _bodyContent = newBody;
}

std::string& HTTP::HTTPObject::getBody(void)
{
    return (_bodyContent);
}

const std::string& HTTP::HTTPObject::getHTTPCode(void) const
{
    return (_httpCode);
}

void HTTP::HTTPObject::createHTTPCodesMap(void)
{
    /** Success Resonses **/
    _httpCodes.insert(std::make_pair<std::string, std::string>("200", "OK"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("201", "Created"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("202", "Accepted"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("203", "Non-Authoritative Information"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("204", "No Content"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("205", "Reset Content"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("206", "Partial Content"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("207", "Multi-Status"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("208", "Multi-Status"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("226", "IM Used"));
    /** Redirect Messages **/
    _httpCodes.insert(std::make_pair<std::string, std::string>("300", "Multiple Choice"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("301", "Moved Permanently"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("302", "Found"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("303", "See Other"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("304", "Not Modified"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("305", "Use Proxy"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("306", "Temporary Redirect"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("307", "IM Used"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("308", "Permanent Redirect"));
    /** Error Responses Client-Side **/
    _httpCodes.insert(std::make_pair<std::string, std::string>("400", "Bad Request"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("401", "Unauthorized"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("402", "Payment Required"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("403", "Forbidden"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("404", "Not Found"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("405", "Method Not Allowed"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("406", "Not Acceptable"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("407", "Proxy Authentification Required"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("408", "Request Timeout"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("409", "Conflict"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("410", "Gone"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("411", "Length Required"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("412", "Precondition Failed"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("413", "Payload Too Large"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("414", "URI Too Long"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("415", "Unsupported Media Type"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("416", "Request Range Not Satisfiable"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("417", "Expectation Failed"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("418", "I'm a teapot"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("421", "Misdirected Request"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("422", "Unprocessable Entity"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("423", "Locked"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("424", "Failed Dependency"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("426", "Upgrade Required"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("428", "Precondition Required"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("429", "Too Many Requests"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("431", "Request Header Fields Too Large"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("451", "Unavailable For Legal Reasons"));
    /** Error Responses Server-Side **/
    _httpCodes.insert(std::make_pair<std::string, std::string>("500", "Internal Server Error"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("501", "Not Implemented"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("502", "Bad Gateway"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("503", "Service Unavailable"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("504", "Gateway Timeout"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("505", "HTTP Version Not Supported"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("506", "Variant Also Negotiates"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("507", "Insufficient Storage"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("508", "Loop Detected"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("510", "Not Extended"));
    _httpCodes.insert(std::make_pair<std::string, std::string>("511", "Network Authentication Required"));
}