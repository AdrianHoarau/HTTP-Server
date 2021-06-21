/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** ASocketHandler
*/

#ifndef ASOCKETHANDLER_HPP_
#define ASOCKETHANDLER_HPP_

#define BUFFER_SIZE (4096)

#include "requestManager.hpp"
#include "ISocketHandler.hpp"
/** @class ASocketHandler
    *  @brief The ASocketHandler class is an abstract class that gather common variables between ISocketHandlers, it also writes the reload function from the ISocketHandler
*/
class ASocketHandler : public ISocketHandler {
    public:
        /** @brief Ctor of ASocketHandler */
        ASocketHandler();
        /** @brief This function will reload the modules and the processing list used by the appropriate ISocketHandler
            *  @param modulePaths Map containing the type of the module and on the other hand containing the exact path to its .so
            *  @param cgiPath Exact path to the dir where CGI scripts are stocked
            *  @param processList Class processingList
        */
        void reload(std::unordered_map<moduleType, std::string>& modulePaths, const std::string& cgiPath, const processingList& processList);
        /** @brief Default copy ctor of ASocketHandler */
        ASocketHandler(const ASocketHandler& other) = default;
        /** @brief Default overloaded '=' operator of ASocketHandler */
        ASocketHandler& operator=(const ASocketHandler& other) = default;
        /** @brief Dtor of ASocketHandler (virtual cause Abstract) */
        virtual ~ASocketHandler() = default;
        /** @brief This function notifies the socket that it is destroyed from the server */
        void killSocket();
    protected:
        /** @brief String to send */
        std::string _message;
        /** @brief requestManager class */
        std::shared_ptr<requestManager> _reqManager;
        /** @brief Buffer that will be filled each time someone writes on our socket. BUFFER_SIZE corresponds to the size that the buffer will have allocated */
        char _data[BUFFER_SIZE];
        /** @brief Bool to know whether the socket has been destroyed by the server or not */
        bool _alive;
    private:
};


#endif /* !ASOCKETHANDLER_HPP_ */
