/*
** EPITECH PROJECT, 2022
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** WindowsCmdExec.hpp.h
*/

#ifndef B_YEP_500_NAN_5_1_ZIA_ARTHUR_BERTAUD_WINDOWSCMDEXEC_HPP_
#define B_YEP_500_NAN_5_1_ZIA_ARTHUR_BERTAUD_WINDOWSCMDEXEC_HPP_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iterator>

class WindowsCmdExec {
    public:
        WindowsCmdExec();
        std::string exec(const std::string &cmd);
};


#endif /* !B_YEP_500_NAN_5_1_ZIA_ARTHUR_BERTAUD_WINDOWSCMDEXEC_HPP_ */
