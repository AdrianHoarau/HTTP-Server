/*
** EPITECH PROJECT, 2021
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** Coord
*/

#include "Coord.hpp"

Coord::Coord(const int ab, const int ord) : x(ab), y(ord)
{

}

Coord& Coord::operator+(const Coord& other)
{
    if (((x + other.x) >= 0 && (x + other.x) <= MAX_LENGTH) && ((y + other.y) >= 0 && (y + other.y) <= MAX_LENGTH)) {
        x += other.x;
        y += other.y;
    }
    return (*this);
}

Coord& Coord::operator+=(const Coord& other)
{
    if (((x + other.x) >= 0 && (x + other.x) <= MAX_LENGTH) && ((y + other.y) >= 0 && (y + other.y) <= MAX_LENGTH)) {
        x += other.x;
        y += other.y;
    }
    return (*this);
}

bool Coord::operator==(const Coord& other) const
{
    return (x == other.x && y == other.y);
}