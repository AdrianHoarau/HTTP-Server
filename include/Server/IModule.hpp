/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** IModule
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_

#include "moduleType.hpp"
#include "HTTPObject.hpp"
/** @class IModule
    *  @brief The IModule class is an interface that gather common methods between all class considered as modules
*/
class IModule {
    public:
        /** @brief Dtor of IModule (virtual cause Interface) */
        virtual ~IModule() = default;
        /** @brief This function will be called each time a request is received
            *  @param req HTTPObject class filled with request's information
        */
        virtual void processRequest(HTTP::HTTPObject& req) = 0;
        /** @brief This function will be called for each module after its creation
            *  @param path Needed path for the right operation of the module (optional)
        */
        virtual void init(const std::string& path) = 0;
        /** @brief This function will return the moduleType of the current instance of IModule
            *  @return moduleType Type of module
        */
        virtual moduleType getModuleType() const = 0;
};

#endif /* !IMODULE_HPP_ */
