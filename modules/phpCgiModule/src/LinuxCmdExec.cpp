/*
** EPITECH PROJECT, 2022
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** LinuxCmdExec.cpp.cc
*/

#include "LinuxCmdExec.hpp"

LinuxCmdExec::LinuxCmdExec()
{

}

std::string LinuxCmdExec::exec(const std::string &cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe)
        return std::string("popen() failed!");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}