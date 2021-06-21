/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud [WSL: Debian]
** File description:
** testHTTPObject
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "processingList.hpp"
#include "HTTPObject.hpp"
#include "Error.hpp"

Test(validRequestToString, HTTPObject)
{
    std::string req = "POST / HTTP/1.1\n\
Host: 127.0.0.1:8084\n\
User-Agent: curl/7.64.0\n\
Accept: */*\n\
Content-Type: application/json\n\
Content-Length: 36\n\n\
{\"name\": \"New item\", \"year\": \"2009\"}";
    HTTP::HTTPObject _obj(req);

    cr_assert_eq(_obj.toString(), req);
}

Test(validRequestChangeContentSize, HTTPObject)
{
    std::string req1 = "POST / HTTP/1.1\n\
Host: 127.0.0.1:8084\n\
User-Agent: curl/7.64.0\n\
Accept: */*\n\
Content-Type: application/json\n\
Content-Length: 36\n\n\
{\"name\": \"New item\", \"year\": \"2009\"}";

    std::string req2 = "POST / HTTP/1.1\n\
Host: 127.0.0.1:8084\n\
User-Agent: curl/7.64.0\n\
Accept: */*\n\
Content-Type: application/json\n\
Content-Length: 666\n\n\
{\"name\": \"New item\", \"year\": \"2009\"}";

    HTTP::HTTPObject _obj(req1);
    _obj.modifyElemContent(HTTP::HEADERS, "Content-Length", "666");
    cr_assert_eq(_obj.toString(), req2);
}

Test(validRequestChangeHost, HTTPObject)
{
    std::string req1 = "POST / HTTP/1.1\n\
Host: 127.0.0.1:8084\n\
User-Agent: curl/7.64.0\n\
Accept: */*\n\
Content-Type: application/json\n\
Content-Length: 36\n\n\
{\"name\": \"New item\", \"year\": \"2009\"}";

    HTTP::HTTPObject _obj(req1);
    _obj.modifyElemContent(HTTP::HEADERS, "Host", "OUI");
    cr_assert_eq(_obj.toString(), req1);
}

Test(validRequestDeleteContentLength, HTTPObject)
{
    std::string req1 = "POST / HTTP/1.1\n\
Host: 127.0.0.1:8084\n\
User-Agent: curl/7.64.0\n\
Accept: */*\n\
Content-Type: application/json\n\
Content-Length: 36\n\n\
{\"name\": \"New item\", \"year\": \"2009\"}";

    HTTP::HTTPObject _obj(req1);
    _obj.deleteElemContent(HTTP::HEADERS, "Content-Length");
    cr_assert_eq(_obj.toString(), req1);
}

Test(validRequestDeleteUnknown, HTTPObject)
{
    std::string req1 = "POST / HTTP/1.1\n\
Host: 127.0.0.1:8084\n\
User-Agent: curl/7.64.0\n\
Accept: */*\n\
Content-Type: application/json\n\
Content-Length: 36\n\n\
{\"name\": \"New item\", \"year\": \"2009\"}";

    HTTP::HTTPObject _obj(req1);
    _obj.deleteElemContent(HTTP::HEADERS, "UNKNOWN");
    cr_assert_eq(_obj.toString(), req1);
}

Test(validRequestDeleteAtErrorPos, HTTPObject)
{
    std::string req1 = "POST / HTTP/1.1\n\
Host: 127.0.0.1:8084\n\
User-Agent: curl/7.64.0\n\
Accept: */*\n\
Content-Type: application/json\n\
Content-Length: 36\n\n\
{\"name\": \"New item\", \"year\": \"2009\"}";

    HTTP::HTTPObject _obj(req1);
    _obj.deleteElemContent(HTTP::HEADERS, "Host", 170);
    cr_assert_eq(_obj.toString(), req1);
}

Test(invalidRequestContentSize, HTTPObject)
{
    std::string req = "GET / HTTP/1.1\n\
Host: 127.0.0.1:8084\n\
User-Agent: curl/7.64.0\n\
Accept: */*\n\
Content-Type: application/json\n\
Content-Length: 30\n\n\
{\"name\": \"New item\", \"year\": \"2009\"}";
    try {
        HTTP::HTTPObject _obj(req);
    } catch (Error& e) {
        cr_assert(std::strcmp(e.what(), "Error: The content-length is not valid.") == 0);
    }
}

Test(invalidRequestNoHost, HTTPObject)
{
    std::string req = "GET / HTTP/1.1\n\
User-Agent: curl/7.64.0\n\
Accept: */*\n\
Content-Type: application/json\n\
Content-Length: 30\n\n\
{\"name\": \"New item\", \"year\": \"2009\"}";
    try {
        HTTP::HTTPObject _obj(req);
    } catch (Error& e) {
        cr_assert(std::strcmp(e.what(), "Error: No host was specified in the request headers") == 0);
    }
}

Test(emptyRequest, HTTPObject)
{
    std::string req;

    try {
        HTTP::HTTPObject _obj(req);
    } catch (Error& e) {
        cr_assert(std::strcmp(e.what(), "Error: Request is empty.") == 0);
    }
}

Test(requestWithNoStartLine, HTTPObject)
{
    std::string req = "Host: 127.0.0.1:8084\n\
User-Agent: curl/7.64.0\n\
Accept: */*\n\
Content-Type: application/json\n\
Content-Length: 30\n\n\
{\"name\": \"New item\", \"year\": \"2009\"}";

    try {
        HTTP::HTTPObject _obj(req);
    } catch (Error& e) {
        cr_assert(std::strcmp(e.what(), "Error: Unknown HTTP Method") == 0);
    }
}