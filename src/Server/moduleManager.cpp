/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** moduleManager
*/

#include "moduleManager.hpp"

moduleManager::moduleManager()
{
}

moduleManager::moduleManager(const moduleManager& other)
{
    this->_loaders = other._loaders;
}

moduleManager& moduleManager::operator=(const moduleManager& other)
{
    this->_loaders = other._loaders;
    return (*this);
}

void moduleManager::loadLoaders(std::unordered_map<moduleType, std::string>& modulePaths)
{
    if (_loaders.size() != 0) {
        // for (auto load : _loaders) {
        //     if (modulePaths.count(load.first) == 0)
        //         removeLoader(load.first);
        // }
        for (auto load = _loaders.begin(); load != _loaders.end(); load++) {
            if (modulePaths.count(load->first) == 0) {
                removeLoader(load->first);
                load = _loaders.begin();
                if (load == _loaders.end())
                    break;
            }
        }
    }
    for (auto& path : modulePaths) {
        if (_loaders.count(path.first) == 0)
            _loaders.insert(std::make_pair(path.first, std::shared_ptr<DLLoader>{new DLLoader(path.second)}));
    }
}

bool moduleManager::doesModuleExist(const moduleType& type)
{
    for (auto& module : _modules)
        if (module->getModuleType() == type)
            return (true);
    return (false);
}

bool moduleManager::doesLoaderExist(const moduleType& type)
{
    for (auto& load : _loaders) {
        if (load.first == type)
            return (true);
    }
    return (false);
}

std::shared_ptr<IModule> moduleManager::getNewModule(const moduleType& type)
{
    for (auto& load : _loaders) {
        if (load.first == type)
                return (load.second->getInstance<IModule>("entryPoint"));
    }
    return (nullptr);
}

std::shared_ptr<IModule> &moduleManager::getModule(const moduleType& type)
{
    for (auto& module : _modules)
        if (module->getModuleType() == type)
            return (module);
    return (_modules.front());
}

void moduleManager::loadModules()
{
    for (auto module = _modules.begin(); module !=  _modules.end(); module++) {
        if (_loaders.count((*module)->getModuleType()) == 0) {
            _modules.erase(module);
            module--;
        }
    }
    for (auto& load : _loaders) {
        if (doesModuleExist(load.first) == false) {
            _modules.push_back(load.second->getInstance<IModule>("entryPoint"));
        }
    }
}

void moduleManager::removeLoader(const moduleType& type)
{
    if (_loaders.find(type) != _loaders.end()) {
        _loaders.erase(type);
    }
}