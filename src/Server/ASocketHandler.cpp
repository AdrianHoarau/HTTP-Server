/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** ASocketHandler
*/

#include "ASocketHandler.hpp"

ASocketHandler::ASocketHandler() : _reqManager(std::make_shared<requestManager>()), _alive(true)
{
}

void ASocketHandler::killSocket()
{
    _alive = false;
}

void ASocketHandler::reload(std::unordered_map<moduleType, std::string>& modulePaths, const std::string& cgiPath, const processingList& processList)
{
    _reqManager->reload(modulePaths, processList, cgiPath);
}