/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** pathHandler.hpp
*/

#ifndef PATHHANDLER_HPP_
#define PATHHANDLER_HPP_

#include <string>
/** @enum pathType
    *  @brief Enum corresponding to the type of the path used
    *  @param REGULAR_FILE It corresponds to the usage of a regular file path
    *  @param DIR It corresponds to the usage of a directory path
*/
enum pathType {
    REGULAR_FILE,
    DIR
};
/** @struct confgiPaths
    *  @brief Container of paths
*/
struct configPaths {
    /** @brief It corresponds to the filepath of the directory containing the shared library */
    std::string dirPath;
    /** @brief It corresponds to the exact filepath to the config file */
    std::string configPath;
};

/** @class pathHandler
    *  @brief The pathHandler allows us to check the validity of either a directory or a filepath
*/
class pathHandler {
    public:
        /** @brief Ctor of pathHandler */
        pathHandler(const pathType& type);
        /** @brief Default copy ctor of pathHandler */
        pathHandler(const pathHandler& other) = default;
        /** @brief Default overloaded '=' operator of pathHandler */
        pathHandler& operator=(const pathHandler& other) = default;
        /** @brief This function will check whether the directory path is valid or not
            *  @return bool True if the path is valid, else False
        */
        bool isDirValid() const;
        /** @brief This function will check whether the filepath is valid or not
            *  @return bool True if the path is valid, else False
        */
        bool isFileValid() const;
        /** @brief This function allow us to set the current used path as a new value
            *  @param path Exact path that must replaced the current one
        */
        void setPath(const std::string& path);
        /** @brief This function returns the current used path
            *  @return std::string Current used path
        */
        std::string getPath() const;
        /** @brief Dtor of pathHandler */
        ~pathHandler() = default;
    private:
        /** @brief Exact file or directory path. */
        std::string _path;
};

#endif /* !PATHHANDLER_HPP_ */
