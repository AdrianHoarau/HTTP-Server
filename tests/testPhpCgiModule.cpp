/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** testPhpCgiModule.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "phpCgiModule.hpp"
#include "Error.hpp"
#include "HTTPObject.hpp"
#include <iostream>

Test(testPhpScript, phpCgiModule)
{

    std::string request("GET /phpcgi?param1=helloWorld&param2=2&param3=3 HTTP/1.1\nHost: 127.0.0.1:8080\nUser-Agent: curl/7.59.0\nAccept: */*\nContent-Length: 1\nContent-Type: application/x-www-form-urlencoded\n\n ");
    HTTP::HTTPObject req(request);
    phpCgiModule php;
    
    php.init("../../../config/PHP/");
    php.processRequest(req);
    cr_assert_eq(req.getBody(), "<html>\n <head>\n  <title>Test PHP</title>\n </head>\n <body>\n Hello World! </body>\n</html>");
}

Test(testPhpErrorNotFound, phpCgiModule)
{

    std::string request("GET /phpcgi?param1=helloWorld&param2=2&param3=3 HTTP/1.1\nHost: 127.0.0.1:8080\nUser-Agent: curl/7.59.0\nAccept: */*\nContent-Length: 1\nContent-Type: application/x-www-form-urlencoded\n\n ");
    HTTP::HTTPObject req(request);
    phpCgiModule php;
    
    php.init("../Error/");
    php.processRequest(req);
    cr_assert_eq(req.getHTTPCode(), "404");
}

Test(testPhpErrorReq, phpCgiModule)
{
    std::string request("GET /phpcgi?param1=Error&param2=2&param3=3 HTTP/1.1\nHost: 127.0.0.1:8080\nUser-Agent: curl/7.59.0\nAccept: */*\nContent-Length: 1\nContent-Type: application/x-www-form-urlencoded\n\n ");
    HTTP::HTTPObject req(request);
    phpCgiModule php;
    
    php.init("../../../config/PHP/");
    php.processRequest(req);
    cr_assert_eq(req.getHTTPCode(), "400");
}