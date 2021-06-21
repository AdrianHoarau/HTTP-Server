/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** Snake
*/

#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include "IModule.hpp"
#include "Coord.hpp"

/** @class sslModule
    * @brief The class Snake allows us to play the Snake through commands received in processRequest as a HTTPObject
*/
class Snake : public IModule {
    public:
        /** @brief Ctor of sslModule */
        Snake();
        /** @brief This function will be called each time a request is received
            *  @param req HTTPObject class filled with request's information
        */
        void processRequest(HTTP::HTTPObject& req);
        /** @brief This function will be called for each module after its creation
            *  @param path Needed path for the right operation of the module (optional)
        */
        void init(const std::string& path);
        /** @brief This function returns the position of the Snake
            * @return Coord Position on X and Y
        */
        Coord getSnakePos() const;
        /** @brief This function returns the position of the Apple
            * @return Coord Position on X and Y
        */
        Coord getApplePos() const;
        /** @brief This function returns the amound of eaten apples
            * @return unsigned int Total amount of eaten apples
        */
        unsigned int getEatenApples() const;
        /** @brief This function will return the moduleType of the current instance of IModule
            *  @return moduleType Type of module
        */
        moduleType getModuleType() const;
        /** @brief This function will put the whole string in upper case
            *  @return String to update
        */
        void upperCase(std::string& str);
        /** @brief Default copy ctor of Snake */
        Snake(const Snake& other) = default;
        /** @brief Default overloaded '=' operator of Snake */
        Snake& operator=(const Snake& other) = default;
        /** @brief Dtor of Snake */
        ~Snake() = default;
    protected:
    private:
        /** @brief Replace the old apple's position by a new one */
        void spawnApple();
        /** @brief This function is called when the request is of type POST, it will execute POST actions
            * @param req HTTPObject class filled with request's information
        */
        void post(HTTP::HTTPObject& req);
        /** @brief This function is called when the request is of type DELETE, it will execute DELETE actions
            * @param req HTTPObject class filled with request's information
        */
        void remove(HTTP::HTTPObject& req);
        /** @brief This function is called when the request is of type PUT, it will execute PUT actions
            * @param req HTTPObject class filled with request's information
        */
        void put(HTTP::HTTPObject& req);
        /** @brief This function is called when the request is of type GET, it will execute GET actions
            * @param req HTTPObject class filled with request's information
        */
        void get(HTTP::HTTPObject& req);
        /** @brief Snake position on X and Y */
        Coord _snakeCoord;
        /** @brief Apple position on X and Y */
        Coord _appleCoord;
        /** @brief Total amount of the eaten apples */
        unsigned int _eatenApples;
        /** @brief Map with string containing the direction: "UP", "RIGHT", "LEFT", "DOWN". This string will be matched with the corresponding movement through the Coord class */
        std::unordered_map<std::string, Coord> _movements;
        /** @brief Map with string containing the methods: "GET", "POST", "DELETE", "PUT". This string will be matched with the corresponding method through the functions pointers */
        std::unordered_map<std::string, void (Snake::*)(HTTP::HTTPObject& req)> _methods;
};

#endif /* !SNAKE_HPP_ */
