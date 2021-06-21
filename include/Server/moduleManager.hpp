/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** moduleManager
*/

#ifndef MODULEMANAGER_HPP_
#define MODULEMANAGER_HPP_

#include "IModule.hpp"
#include "DLLoader.hpp"
#include <vector>
#include <unordered_map>

/** @class moduleManager
    *  @brief The moduleManager allows us to create, load, check existance of modules
*/
class moduleManager {
    public:
        /** @brief Ctor of moduleManager */
        moduleManager();
        /** @brief Dtor of moduleManager */
        ~moduleManager() = default;
        /** @brief Copy ctor of moduleManager */
        moduleManager(const moduleManager& other);
        /** @brief Overloaded '=' operator of moduleManager */
        moduleManager& operator=(const moduleManager& other);
        /** @brief This function will check whether the module exists or not
            *  @param type Type of the module
            *  @return bool True if the module exists, else False
        */
        bool doesModuleExist(const moduleType& type);
        /** @brief This function will check whether the loader exists or not
            *  @param type Type of the module of the loader
            *  @return bool True if the loader exists, else False
        */
        bool doesLoaderExist(const moduleType& type);
        /** @brief This function will return the module correponding to the type sended
            *  @param type Type of the module
            *  @return std::shared_ptr<IModule> Shared pointer to the corresponding module
        */
        std::shared_ptr<IModule> &getModule(const moduleType& type);
        /** @brief This function will load _loaders variable thanks to the map received as param
            *  @param modulePaths Map containing the type of the module and on the other hand containing the exact path to its .so
            *  @return std::shared_ptr<IModule> Shared pointer to the corresponding module
        */
        void loadLoaders(std::unordered_map<moduleType, std::string>& modulePaths);
        /** @brief This function will load _modules variable thanks to the loaders */
        void loadModules();
        /** @brief This function will create the module correponding to the type sended and will return it
            *  @param type Type of the module
            *  @return std::shared_ptr<IModule> Shared pointer to the created module
        */
        std::shared_ptr<IModule> getNewModule(const moduleType& type);
        /** @brief This function will remove the loader corresponding to the moduleType received
            *  @param type Type of the module
        */
        void removeLoader(const moduleType& type);
    private:
        /** @brief Map containing the type of the module and on the other hand containing its loader as a shared pointer of DLLoader */
        std::unordered_map<moduleType, std::shared_ptr<DLLoader>> _loaders;
        /** @brief Vector containing modules as shared pointer of IModule */
        std::vector<std::shared_ptr<IModule>> _modules;
};


#endif /* !MODULEMANAGER_HPP_ */
