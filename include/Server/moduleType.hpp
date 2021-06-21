/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** moduleType
*/

#ifndef MODULETYPE_HPP_
#define MODULETYPE_HPP_

/** @enum moduleType
    *  @brief Enum corresponding to the type of the module
    *  @param PHPCGI It corresponds to the PHPCGI module 
    *  @param SSL_MODULE It corresponds to the SSL module 
    *  @param SNAKE It corresponds to the Snake module 
    *  @param NONE Used when there is no moduleType associated
*/
enum moduleType {
    PHPCGI,
    SSL_MODULE,
    SNAKE,
    NONE
};

#endif /* !MODULETYPE_HPP_ */
