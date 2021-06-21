/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** INetwork
*/

#ifndef INETWORK_HPP_
#define INETWORK_HPP_

/** @class INetwork
    *  @brief The INetwork class is an interface that gather common methods between all class considered as Client or Server
*/
class INetwork {
    public:
        /** @brief Dtor of INetwork (virtual cause Interface) */
        virtual ~INetwork() = default;
        /** @brief Start the network functionality */
        virtual void start() = 0;
        /** @brief Stop the network functionality */
        virtual void stop() = 0;
    protected:
    private:
        /** @brief Start connection's network functionality */
        virtual void startAccept() = 0;
};

#endif /* !INETWORK_HPP_ */
