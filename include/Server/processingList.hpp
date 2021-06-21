/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** processingList
*/

#ifndef PROCESSINGLIST_HPP_
#define PROCESSINGLIST_HPP_

#include "moduleType.hpp"
#include <vector>

/** @class processingList
    *  @brief The processingList lets us aware concerning the order in which the module may be executed
*/
class processingList {
    public:
    /** @brief Ctor of processingList */
    processingList() = default;
    /** @brief This function add a module at the given position to the vector named _list
        *  @param type Type of the module
        *  @param pos Pos expected of the module
    */
    void add(const moduleType& type, const unsigned int pos = 0);
    /** @brief This function remove the module of the vector _list at the given position
        *  @param pos Pos of the module to remove
    */
    void remove(const unsigned int pos = 0);
    /** @brief Empty the _list */
    void clear();
    /** @brief This function returns the front of the vector _list, so the it returns the first module
        * @return moduleType Type of the module 
    */
    moduleType getCurrentType() const;
    /** @brief This function returns the vector _list
        * @return std::vector<moduleType> Vector in the order of all moduleTypes
    */
    std::vector<moduleType>& getList();
    /** @brief This function returns the size of the vector _list
        * @return size_t Unsigned number corresponding to the size of the vector _list
    */
    size_t getSize()const;
    /** @brief Default copy ctor of processingList */
    processingList(const processingList& other) = default;
    /** @brief Default overloaded '=' operator of processingList */
    processingList& operator=(const processingList& other);
    /** @brief Dtor of processingList */
    ~processingList() = default;
private:
    /** @brief Vector in the order of all moduleTypes */
    std::vector<moduleType> _list;
};

#endif /* !PROCESSINGLIST_HPP_ */
