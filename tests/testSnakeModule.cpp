/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** testSnakeModule
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Snake.hpp"
#include "HTTPObject.hpp"

Test(testGetModuleType, Snake)
{
    std::string request("PUT /snake HTTP/1.1\nHost: localhost:8080\nUser-Agent: curl/7.65.3\nAccept: */*\nContent-Length: 10\nContent-Type: application/x-www-form-urlencoded\n\narrow=DOWN");
    HTTP::HTTPObject req(request);
    Snake snk;

    cr_assert_eq(moduleType::SNAKE, snk.getModuleType());
}

Test(testSimplePut, Snake)
{
    std::string request("PUT /snake HTTP/1.1\nHost: localhost:8080\nUser-Agent: curl/7.65.3\nAccept: */*\nContent-Length: 10\nContent-Type: application/x-www-form-urlencoded\n\narrow=DOWN");
    HTTP::HTTPObject req(request);
    Snake snk;

    snk.processRequest(req);
    cr_assert_eq(snk.getSnakePos(), Coord(0, 1));
}


Test(testAllPutTogether, Snake)
{
    std::string requestD("PUT /snake HTTP/1.1\nHost: localhost:8080\nUser-Agent: curl/7.65.3\nAccept: */*\nContent-Length: 10\nContent-Type: application/x-www-form-urlencoded\n\narrow=DOWN");
    std::string requestR("PUT /snake HTTP/1.1\nHost: localhost:8080\nUser-Agent: curl/7.65.3\nAccept: */*\nContent-Length: 11\nContent-Type: application/x-www-form-urlencoded\n\narrow=RIGHT");
    std::string requestL("PUT /snake HTTP/1.1\nHost: localhost:8080\nUser-Agent: curl/7.65.3\nAccept: */*\nContent-Length: 10\nContent-Type: application/x-www-form-urlencoded\n\narrow=LEFT");
    std::string requestU("PUT /snake HTTP/1.1\nHost: localhost:8080\nUser-Agent: curl/7.65.3\nAccept: */*\nContent-Length: 8\nContent-Type: application/x-www-form-urlencoded\n\narrow=UP");
    HTTP::HTTPObject reqD(requestD);
    HTTP::HTTPObject reqR(requestR);
    HTTP::HTTPObject reqL(requestL);
    HTTP::HTTPObject reqU(requestU);
    Snake snk;

    snk.processRequest(reqD);
    snk.processRequest(reqR);
    snk.processRequest(reqL);
    snk.processRequest(reqU);
    cr_assert_eq(snk.getSnakePos(), Coord(0, 0));
}

Test(testSnakeAlgo, Snake)
{
    std::string requestD("PUT /snake HTTP/1.1\nHost: localhost:8080\nUser-Agent: curl/7.65.3\nAccept: */*\nContent-Length: 10\nContent-Type: application/x-www-form-urlencoded\n\narrow=DOWN");
    std::string requestR("PUT /snake HTTP/1.1\nHost: localhost:8080\nUser-Agent: curl/7.65.3\nAccept: */*\nContent-Length: 11\nContent-Type: application/x-www-form-urlencoded\n\narrow=RIGHT");
    std::string requestL("PUT /snake HTTP/1.1\nHost: localhost:8080\nUser-Agent: curl/7.65.3\nAccept: */*\nContent-Length: 10\nContent-Type: application/x-www-form-urlencoded\n\narrow=LEFT");
    std::string requestU("PUT /snake HTTP/1.1\nHost: localhost:8080\nUser-Agent: curl/7.65.3\nAccept: */*\nContent-Length: 8\nContent-Type: application/x-www-form-urlencoded\n\narrow=UP");
    HTTP::HTTPObject reqD(requestD);
    HTTP::HTTPObject reqR(requestR);
    HTTP::HTTPObject reqL(requestL);
    HTTP::HTTPObject reqU(requestU);
    Snake snk;
    Coord applePos = snk.getApplePos();
    unsigned int result = 1;

    while (applePos.x != snk.getSnakePos().x)
        snk.processRequest(reqR);
    while (applePos.y != snk.getSnakePos().y)
        snk.processRequest(reqD);
    cr_assert_eq(snk.getEatenApples(), result);
}