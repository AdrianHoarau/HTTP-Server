/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** configHandler.hpp
*/

#ifndef CONFIGHANDLER_HPP_
#define CONFIGHANDLER_HPP_

#include "pathHandler.hpp"
#include "processingList.hpp"
#include <unordered_map>
#include "moduleType.hpp"
#include "jsonReader.hpp"
#include <string>
#include "Error.hpp"
#include <fstream>
#include <map>
#include <filesystem>

enum ConfigType {
    MODULE
};

class configHandler
{
    private:
        /* class open the configFile */
        std::ifstream _fileErr;
        /* class processingList */
        processingList _processList;
        /* class jsonReader */
        jsonReader _json;
        /** @brief Map containing the type of the module and on the other hand containing the exact path to its .so */
        std::unordered_map<moduleType, std::string> _modulePaths;
        /** @brief struct with the filepath of the directory containing the shared library and the path corresponds to the exact filepath to the config file */
        configPaths _paths;
        /** @brief The path of the certificate */
        std::string _certificatePath;
        /** @brief The path of the directory where the scripts php are */
        std::string _CgiDir;
        /** @brief The map with all the module name we have */
        const std::map<std::string, moduleType> _moduleType {
        {"phpCgiModule", PHPCGI},
        {"sslModule", SSL_MODULE},
        {"snakeModule", SNAKE}
        };
        /** @brief This function will load the modules */
        void load();
        /** @brief This function will add the module path on the _modulePaths and the name of the modue on the _processList
        *   @param line one line of the configfile
        */
        bool addModuleJson(const std::string& name);
        /** @brief This function will check the tag in the configfile
        *   @param line one line of the configfile
        */
        bool checktagModule(std::string& line);
        /** @brief This function will cut the string for have the name of the module
        *   @param line one line of the configfile
        */
        std::string getName(std::string line);
        /** @brief This function will check if the file exist
        *   @param p the path of the file
        */
        bool fileExists(const std::filesystem::path& p);
        /** @brief This function will check the tag of the configfile
        *   @param line one line of the configfile
        */
        bool checkTag(std::string line);
        /** @brief This function will give the position of the n char
        *   @param str the string where the char is
        *   @param findMe the char to found
        *   @param nth the n char to found
        */
        int nthOccurrence(const std::string& str, const std::string& findMe, int nth);
        /** @brief This function will load the modules with a default path*/
        void defaultFile();
        /** @brief This function will check if the file exist and will send false if he exist and true if not
        *   @param line one line of the configfile
        */
        bool fexists(const std::string& filename);
    
    public:
        /** @brief Ctor of configHandler
        *  @param paths struct with the filepath of the directory containing the shared library and the path corresponds to the exact filepath to the config file 
        */
        configHandler(const configPaths& paths);
        /** @brief Default ctor of configHandler */
        configHandler(const configHandler& other) = default;
        /** @brief Default overloaded '=' operator of configHandler */
        configHandler& operator=(const configHandler& other) = default;
        /** @brief This function will reload the modules */
        void reload();
        /** @brief This function will return a copy of the directory path  */
        std::string getCgiPath()const;
        /** @brief This function will return a copy of the certificate path  */
        std::string getCertificatePath()const;
        /** @brief This function will return a copy of the _processList  */
        processingList getCopyProcessList();
        /** @brief This function will return reference of the modulelist */
        std::unordered_map<moduleType, std::string>& getListModules();
        /** @brief Default dtor of configHandler */
        ~configHandler() = default;
};

#endif