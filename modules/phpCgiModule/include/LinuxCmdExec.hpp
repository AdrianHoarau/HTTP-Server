/*
** EPITECH PROJECT, 2022
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** LinuxCmdExec.hpp.h
*/

#ifndef B_YEP_500_NAN_5_1_ZIA_ARTHUR_BERTAUD_LINUXCMDEXEC_HPP_
#define B_YEP_500_NAN_5_1_ZIA_ARTHUR_BERTAUD_LINUXCMDEXEC_HPP_

#include <fstream>
#include <memory>
#include <filesystem>
#include <cstring>

class LinuxCmdExec {
    public:
        LinuxCmdExec();
        std::string exec(const std::string &cmd);
};


#endif /* !B_YEP_500_NAN_5_1_ZIA_ARTHUR_BERTAUD_LINUXCMDEXEC_HPP_ */
