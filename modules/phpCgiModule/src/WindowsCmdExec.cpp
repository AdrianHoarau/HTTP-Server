/*
** EPITECH PROJECT, 2022
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** WindowsCmdExec.cpp.cc
*/

#include "WindowsCmdExec.hpp"

WindowsCmdExec::WindowsCmdExec()
{
}

std::string WindowsCmdExec::exec(const std::string &cmd)
{
    std::string fileName = "result.txt";
    std::system((cmd + " > " + fileName).c_str());
    std::ifstream file(fileName);
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}