/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** pathHandler.cpp
*/

#include "pathHandler.hpp"
#include <filesystem>

pathHandler::pathHandler(const pathType& type)
{
    if (type == pathType::REGULAR_FILE)
        _path = "../config/config.json";
    else
        _path = "./lib/";
}

bool pathHandler::isDirValid() const
{
    return (std::filesystem::is_directory(_path));
}

bool pathHandler::isFileValid() const
{
    return (std::filesystem::is_regular_file(_path));
}

void pathHandler::setPath(const std::string& path)
{
    _path = path;
}

std::string pathHandler::getPath() const
{
    return (_path);
}