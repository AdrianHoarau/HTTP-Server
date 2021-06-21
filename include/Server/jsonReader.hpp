/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** jsonReader.hpp
*/

#ifndef JSONREADER_HPP_
#define JSONREADER_HPP_

#include <nlohmann/json.hpp>
#include <string>
/** @class jsonReader
    *  @brief The jsonReader allows us to read a json file through its methods
*/
class jsonReader {
    public:
        /** @brief Ctor of jsonReader */
        jsonReader(const std::string& configPath);
        /** @brief Default copy ctor of jsonReader */
        jsonReader(const jsonReader& other) = default;
        /** @brief Default overloaded '=' operator of jsonReader */
        jsonReader& operator=(const jsonReader& other) = default;
        /** @brief This function gets the json file as a nlohmann::json object
            *  @return nlohmann::json Object representing the json file parsed
        */
        nlohmann::json getJsonFile() const;
        /** @brief Load the config file by opening and reading it */
        void loadConfigFile();
        /** @brief Dtor of jsonReader */
        ~jsonReader() = default;
    private:
        /** @brief Exact path to the configFile */
        std::string _configPath;
        /** @brief Object representing the json file parsed */
        nlohmann::json _jsonFile;
};

#endif /* !JSONREADER_HPP_ */
