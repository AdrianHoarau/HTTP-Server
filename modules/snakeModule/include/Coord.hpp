/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** Coord
*/

#ifndef COORD_HPP_
#define COORD_HPP_

#define MAX_LENGTH 10


/** @class Coord
  * @brief The Coord class allows us to stock an abscissa and an ordinate, we can also make some calcs with them, thanks to the overloaded operators
*/
class Coord {
    public:
        /** @brief Default ctor of Coord */
        Coord() = default;
        /** @brief Ctor of Coord 
            * @param ab Value of the abscissa
            * @param ord Value of the ordinate
        */
        Coord(const int ab, const int ord);
        /** @brief Default copy ctor of Coord */
        Coord(const Coord& other) = default;
        /** @brief Overloaded '+' operator of Coord */
        Coord& operator+(const Coord& other);
        /** @brief Overloaded '+=' operator of Coord */
        Coord& operator+=(const Coord& other);
        /** @brief Overloaded '==' operator of Coord */
        bool operator==(const Coord& other) const;
        /** @brief Default overloaded '=' operator of Coord */
        Coord& operator=(const Coord& other) = default;
        /** @brief Dtor of Coord */
        ~Coord() = default;
        /** @brief Abscissa */
        int x;
        /** @brief Ordinate */
        int y;
};

#endif /* !COORD_HPP_ */
