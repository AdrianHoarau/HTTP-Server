/*
** EPITECH PROJECT, 2020
** client
** File description:
** SignalHandler
*/

#ifndef SIGNALHANDLER_HPP_
#define SIGNALHANDLER_HPP_

#include <signal.h>
#include <iostream>
#include <atomic>

/** @brief Global variable to check if a CTRL+C has been caught */
extern bool isInterrupt;

/** @class SignalHandler
    * @brief The SignalHandler class allows us to catch the CTRL+C
*/
class SignalHandler {
    public:
        /** @brief Ctor of SignalHandler */
        SignalHandler();
        /** @brief Default copy ctor of SignalHandler */
        SignalHandler(const SignalHandler& other) = default;
        /** @brief Default overloaded '=' operator of SignalHandler */
        SignalHandler& operator=(const SignalHandler& other) = default;
        /** @brief This function returns whether a CTRL+C has been caught or not
            * @return bool True if a signal has been caught, else False
        */
        bool isInterrupted();
        /** @brief Dtor of SignalHandler */
        ~SignalHandler() = default;
    private:
        /** @brief This function is called when a signal CTRL+C is catched
            * @param signum Contains the value of the signal
        */
        static void signal_callback_handler(int signum);
};

#endif /* !SIGNALHANDLER_HPP_ */