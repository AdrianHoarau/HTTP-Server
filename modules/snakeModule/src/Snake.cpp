/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** Snake
*/

#include "Snake.hpp"
#include <memory>
#include <iostream>

Snake::Snake(): _snakeCoord(Coord(0, 0)), _eatenApples(0)
{
    _movements.insert(std::make_pair("UP", Coord(0, -1)));
    _movements.insert(std::make_pair("DOWN", Coord(0, 1)));
    _movements.insert(std::make_pair("RIGHT", Coord(1, 0)));
    _movements.insert(std::make_pair("LEFT", Coord(-1, 0)));
    _methods.insert(std::make_pair("GET", &Snake::get));
    _methods.insert(std::make_pair("PUT", &Snake::put));
    _methods.insert(std::make_pair("DELETE", &Snake::remove));
    _methods.insert(std::make_pair("POST", &Snake::post));
    spawnApple();
}

void Snake::processRequest(HTTP::HTTPObject& req)
{
    std::string method = req[HTTP::STARTLINES]["Method"][0];
    upperCase(method);
    for (auto& met : _methods)
        if (met.first == method)
            (this->*(met.second))(req);
}

void Snake::init([[maybe_unused]] const std::string& path)
{
}

moduleType Snake::getModuleType() const
{
    return (moduleType::SNAKE);
}

void Snake::spawnApple()
{
    _appleCoord.x = rand() % MAX_LENGTH;
    _appleCoord.y = rand() % MAX_LENGTH;
}

void Snake::post(HTTP::HTTPObject& req)
{
    //POST
    //404 (Not Found)
    //409 (Conflict)
    if (req[HTTP::STARTLINES]["Target"].size() < 1)
        return;
    if (req[HTTP::STARTLINES]["Target"][1] != "snake")
        return;
    req.setHTTPCode("200");
}

void Snake::remove(HTTP::HTTPObject& req)
{
    //DELETE
    //200 (OK)
    //404 (Not Found), if ID not found or invalid.
    if (req[HTTP::STARTLINES]["Target"].size() < 1)
        return;
    if (req[HTTP::STARTLINES]["Target"][1] != "snake")
        return;
    req.setHTTPCode("200");
}

void Snake::put(HTTP::HTTPObject& req)
{
    //PUT
    //200 (OK)
    //204 (No Content).
    //404 (Not Found), if ID not found or invalid.
    bool valid = false;

    if (req[HTTP::STARTLINES]["Target"].size() < 1)
        return;
    if (req[HTTP::STARTLINES]["Target"][1] != "snake")
        return;
    auto& params = req.getParams();
    if (params.size() == 0) {
        req.setHTTPCode("204");
        return;
    }
    if (params.find("arrow") != params.end()) {
        auto& param = params["arrow"];
        upperCase(param);
        for (auto& move : _movements)
            if (move.first == param) {
                valid = true;
                _snakeCoord += move.second;
            }
        if (_snakeCoord == _appleCoord) {
            _eatenApples += 1;
            spawnApple();
        }
        // std::cout << "x: " + std::to_string(_snakeCoord.x) + ", y: " + std::to_string(_snakeCoord.y) + ", apple_x: " + std::to_string(_appleCoord.x) + ", apple_y: " + std::to_string(_appleCoord.y) << std::endl;
        req.setHTTPCode("200");
    } else
        req.setHTTPCode("404");
}

void Snake::get(HTTP::HTTPObject& req)
{
    //GET
    //200 (OK),
    //404 (Not Found), if ID not found or invalid.
    if (req[HTTP::STARTLINES]["Target"].size() < 2)
        return;
    if (req[HTTP::STARTLINES]["Target"][1] != "snake")
        return;
    std::string startBody("<!DOCTYPE html><head><title>Zia</title></head><body>");
    std::string jumpOfLine("<br>");
    std::string snakeCoordHtml("<center><h1>Snake Position: x: " + std::to_string(_snakeCoord.x) + ", y: " + std::to_string(_snakeCoord.y) +"</h1></center>");
    std::string appleCoordHtml("<center><h1>Apple Position: x: " + std::to_string(_appleCoord.x) + ", y: " + std::to_string(_appleCoord.y) +"</h1></center>");
    std::string nbAppleHtml("<center><h1>Number of eaten apples : " + std::to_string(_eatenApples) +"</h1></center>");
    std::string endBody("</body>");
    std::string body(startBody + snakeCoordHtml + jumpOfLine + appleCoordHtml + jumpOfLine + nbAppleHtml + endBody);

    req.setHTTPCode("200");
    req.setBody(body);
}

Coord Snake::getSnakePos() const
{
    return (_snakeCoord);
}

Coord Snake::getApplePos() const
{
    return (_appleCoord);
}

unsigned int Snake::getEatenApples() const
{
    return (_eatenApples);
}

void Snake::upperCase(std::string& str)
{
    for (auto& c: str) c = toupper(c);
}

#if defined (_WIN32)
    
    extern "C"  __declspec(dllexport)
    void *entryPoint()
    {
        return (new std::shared_ptr<Snake>(new Snake));
    }

#else

    extern "C" std::shared_ptr<IModule> entryPoint()
    {
        return (std::make_shared<Snake>());
    }

#endif