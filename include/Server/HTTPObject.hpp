/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud [WSL: Debian]
** File description:
** HTTPObject
*/

#ifndef HTTPOBJECT_HPP_
#define HTTPOBJECT_HPP_

#include <iostream>
#include <map>
#include <vector>
#include <unordered_map>
#include <utility>

// HTTP CODES -> https://developer.mozilla.org/fr/docs/Web/HTTP/Status

/** Success Resonses **/
// 200 OK
// 201 Created
// 202 Accepted
// 203 Non-Authoritative Information
// 204 No Content
// 205 Reset Content
// 206 Partial Content
// 207 Multi-Status
// 208 Multi-Status
// 226 IM Used

/** Redirect Messages **/
// 300 Multiple Choice
// 301 Moved Permanently
// 302 Found
// 303 See Other
// 304 Not Modified
// 305 Use Proxy
// 306 unused
// 307 Temporary Redirect
// 308 Permanent Redirect

/** Error Responses Client-Side **/
// 400 Bad Request
// 401 Unauthorized
// 402 Payment Required
// 403 Forbidden
// 404 Not Found
// 405 Method Not Allowed
// 406 Not Acceptable
// 407 Proxy Authentification Required
// 408 Request Timeout
// 409 Conflict
// 410 Gone
// 411 Length Required
// 412 Precondition Failed
// 413 Payload Too Large
// 414 URI Too Long
// 415 Unsupported Media Type
// 416 Request Range Not Satisfiable
// 417 Expectation Failed
// 418 I'm a teapot
// 421 Misdirected REquest
// 422 Unprocessable Entity
// 423 Locked
// 424 Failed Dependency
// 426 Upgrade Required
// 428 Precondition Required
// 429 Too Many Requests
// 431 Request Header Fields Too Large
// 451 Unavailable For Legal Reasons

/** Error Responses Server-Side **/
// 500 Internal Server Error
// 501 Not Implemented
// 502 Bad Gateway
// 503 Service Unavailable
// 504 Gateway Timeout
// 505 HTTP Version Not Supported
// 506 Variant Also Negotiates
// 507 Insufficient Storage
// 508 Loop Detected
// 510 Not Extended
// 511 Network Authentication Required

namespace HTTP {

    /** @enum reqElem
     *  @brief Enum corresponding to the type of element that can be found in an HTTP Req or Res
     *  @param STARTLINES Correspond to the first part of the req/res (contains the Version, Target and Method)
     *  @param HEADERS Correspond to the second part of the req/res (contains various informations)
     *  @param BODY Correspond to the third part of the req/res (is optionnal and may contain)
    */
    enum reqElem {STARTLINES, HEADERS, BODY};
    /** @enum HTTPType
     *  @brief Enum corresponding to the type of HTTP demand, can be a Req (Request) or Res (Response)
    */
    enum HTTPType {REQ, RES};
    using reqType = std::unordered_map<std::string, std::vector<std::string>>;
    using paramsMap = std::unordered_map<std::string, std::string>;
    /** @class HTTPObject
     *  @brief The HTTPObject class is a class that will parse the raw request received in argument of the ctor
    */
    class HTTPObject {
        public:
            /** @brief Ctor of HTTPObject
             *  @param request The raw Request 
             *  @param key (Default=HTTPType::REQ) The HTTPType of the object (will not) 
             */
            HTTPObject(const std::string& request, const HTTP::HTTPType& type=HTTPType::REQ);
            /** @brief Default ctor of HTTPObject */
            HTTPObject()=default;
            /** @brief Default dtor of HTTPObject */
            ~HTTPObject()=default;
            /** @brief Default copy ctor of HTTPObject */
            HTTPObject(const HTTPObject& other)=default;
            /** @brief Default overloaded '=' operator of HTTPObject */
            HTTPObject& operator=(const HTTPObject& other)=default;
            /** @brief Overloaded '=' operator of HTTPObject that will give access to the class'
             *         unordered_map to easily add new keys (the use of the class' methods is advised)
             *  @param elem The type of reqElem (STARTLINE, HEADERS, BODY)
             */
            HTTP::reqType& operator[](const HTTP::reqElem& elem);
        public:
            /** @brief This function will decode the request received from the client before parsing it
             *  @param request std::string The request as a std::string
             *  @return std::string Will return the decoded request as a std::string
             */
            std::string decodeRequest(const std::string& request);
            /** @brief This function will check if the given key exists in the given reqType
             *  @param elem The type of reqElem (STARTLINE, HEADERS, BODY)
             *  @param key The key to verify
             *  @return True or False is the key already exist
             */
            bool isKey(const reqElem& elem, const std::string& key);
            /** @brief This function will delete the content related to a key in the reqType
             *  @param elem The type of reqElem (STARTLINE, HEADERS, BODY)
             *  @param key The key to verify
             *  @param pos (Default = npos) The pos of the element in the vector
             *  @return Void
             */
            void deleteElemContent(const reqElem& elem, const std::string& key, std::size_t pos = std::string::npos);
            /** @brief This function will modify the content related to a key in the reqType
             *  @param elem The type of reqElem (STARTLINE, HEADERS, BODY) 
             *  @param key The key which content will be modified
             *  @param newVal The new value which will replace the current one
             *  @param pos (Default=std::string::npos) The pos of the element in the vector
             *  @return Void
             */
            void modifyElemContent(const reqElem& elem, const std::string& key, const std::string& newVal, std::size_t pos = 0);
            /** @brief This function will concat all the content related to a key in a string 
             *  @param elem The type of reqElem (STARTLINE, HEADERS, BODY) 
             *  @param key The key which content will be get
             *  @param displayMode (Default=false) A bool to allow display mode (add a '\n' between each elem)
             *  @return std::string Concatenation of the elements in a std::string
             */
            std::string getElemConcatContent(const reqElem& elem, const std::string& key, bool displayMode = false);
            /** @brief This function will create a string with the REQ/RES content 
             *  @return std::string Concatenation of all the elements of the REQ/RES in a std::string
             */
            std::string toString(void);
            /** @brief This function will check the content of the REQ/RES ('Content-Length' if body and 'Host')
             *  @return int 0 if everything is OK and throw an error if not
             */
            int checkContent(void);
            /** @brief This function will create a std::vector from a std::string that will be splited from a delim char
             *  @param str The string that will be separated
             *  @param delim The character that will be used to create separations between words
             *  @return std::vector All the separated strings in an std::vector
             */
            std::vector<std::string> strToStringVector(const std::string& str, const std::string& delim);
            /** @brief This function will create a RES out of a REQ
             *  @param httpCode The code of the HTTP Responses to send (Check the doc to see all implemented HTTP codes)
             *  @param body (Optionnal) The body of the res (if needed)
             *  @return HTTPObject Will return the object itself so that it can be chained with another method
             */
            HTTP::HTTPObject& createResponse(void);
            /** @brief This function will fill the _params map in the class with the params in the strParams
             *  @param defaultBody (Default = true) bool Depending on the value will create a html template body with the http code. Set it to false if you want to use yout own body. 
             *  @return Void
             */
            void createParamsMap(const std::string& strParams);
            /** @brief This function will get the params from the _params map.
             *         THIS FUNCTION MUST BE USED IN A TRY/CATCH. IT WILL THROW AN ERROR IF THE PARAM DOES NOT EXIST
             *  @param strParams std::string containing the params from the HTTP REQ
             *  @return std::string The value corresponding to the given param.
             */
            HTTP::paramsMap& getParams();
            /** @brief THIS WILL BE RELOCATED 
             * This function will create a map with all the HTTP Codes and their description.
             * Can be used as: _map.getDesc("200") -> "OK"
            */
            void createHTTPCodesMap(void);
            /** @brief THIS WILL MAYBE BE RELOCATED 
             * This function will get the description of the given HTTP Code.
             * @param code std::string corresponding to the code you want the description of. 
             * Can be used as: _map.getDesc("200") -> "OK"
            */
            const std::string getCodeDesc(const std::string& code);
            /** @brief This function will set the HTTPObject HTTP code to the one given in argument.
             *  @param code std::string corresponding to the code.
            */
            void setHTTPCode(const std::string& newCode);
            /** @brief This function will set the HTTPObject body to the one given in argument.
             *  @param code std::string corresponding to the body.
            */
            void setBody(const std::string& newBody);
            /** @brief This function will get the _httpCode variable */
            const std::string& getHTTPCode(void) const;
            /** @brief This function will get the HTTPObject body content.
            */
            std::string& getBody(void);
        private:
            /** @brief This function will clear all keys and their content in all the unordered_maps (STARTLINE, HEADERS, BODY)
             *  @return Void
             */
            void clear(void);
            /** @brief This function will parse the raw Request to fill the unordered_map with the Request content
             *  @return Void
             */
            void parseRequest(const std::string& request);
            /** @brief This function will parse the raw Request to fill the STARTLINE unordered_map with the Request's startline content.
             *          It will also check for any params and will ???
             *  @return Void
             */
            void parseStartLine(const std::string& request);
            /** @brief This function will parse the raw Request to fill the HEADERS unordered_map with the Request's header content
             *  @return Void
             */
            void parseHeaders(const std::string& request);
            /** @brief This function will parse the raw Request to fill the BODY unordered_map with the Request's body content
             *  @return Void
             */
            void parseBody(const std::string& request);
            /** @brief This function will parse the raw Target (from the request's STARTLINE) and will push in the corresponding
             *         std::vector all the part of the target. Example: '/test/main' -> 'test' and 'main' will be pushed
             *         in the std::vector of the "Target" key. (Note that the first element will be the raw target)
             *         This function will also determine if the target contains parameters, and will additionnaly parse
             *         the parameters and add them in the _params map in the class;
             *  @return Void
             */
            void parseTarget(std::string& target);
        private:
            /** @brief The type of the object (REQ or RES) */
            HTTP::HTTPType _type;
            /** @brief A reqType that will contain all the request's StartLine elements "Method", "Version" and "Target"
             *         for a REQ and "Version", "Code" and "Description" for a RES.
             *         Can be accessed like: obj[STARTLINE]["Method"][0] -> "POST"
             */
            HTTP::reqType _startLine;
            /** @brief A reqType that will contain all the request's headers elements ("Host" is mandatory)
              *        All others are optionnal except for "Content-Length" when there is a body.
              *        Can be accessed like: obj[HEADERS]["Content-Length"][0] -> "46"
             */
            HTTP::reqType _headers;
            /** @brief A std::vector of std::string that will contain all the headers elements in order so that
              *        when the request will be reconstitute, all elements will be in order.
             */
            std::vector<std::string> _headersOrderList;
            /** @brief A reqType that will contain all the request's body elements in the key "Body".
             *         Will be empty if no body is found. Can be accessed like: obj[BODY]["Body"][0] -> "{"name":"Marshall"}"
             */
            HTTP::reqType _body;
            /** @brief A map that will contain all the parameters and their values (use with the getParam function)
             *         Can be used like: _obj.getParam("Age") -> "13"
             */
            HTTP::paramsMap _params;
            /** @brief THIS WILL BE RELOCATED */
            HTTP::paramsMap _httpCodes;
            std::string _httpCode;
            std::string _bodyContent;
    };
}


#endif /* !HTTPOBJECT_HPP_ */
