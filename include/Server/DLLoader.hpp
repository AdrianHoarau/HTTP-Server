/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** DLLoader.hpp
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_
#include <iostream>
#include "Error.hpp"
#include <memory>
#ifdef __linux__
    #include <dlfcn.h>
    #define LIBTYPE void*
    #define OPENLIB(libname) dlopen((libname), RTLD_NOW)
    #define LIBFUNC(lib, fn) dlsym((lib), (fn))
    #define CLOSELIB(handler) dlclose(handler)
#elif defined(_WIN32)
    #include <winsock2.h>
    #include <windows.h>
    #define LIBTYPE HMODULE
    #define OPENLIB(libname) LoadLibraryA(libname)
    #define LIBFUNC(lib, fn) GetProcAddress((lib), (fn))
    #define CLOSELIB(handler) CloseHandle(handler)
#endif

/** @class DLLoader
    *  @brief The DLLoader class allows us to load a shared library
*/
class DLLoader {
public:
    /** @brief Ctor of DLLoader
        *  @param libpath Exact path to the shared library(.so) to load
    */
    DLLoader(const std::string& libpath)
    try : _handler(nullptr)
    {
        _handler = OPENLIB(libpath.c_str());
        #if defined(_WIN32)
            if (!_handler)
                throw ErrorDLLoader("Error: Encounter error while opening lib.");
        #else
            if (!_handler)
                throw ErrorDLLoader(dlerror());
        #endif
    }
    catch (ErrorDLLoader const& err)
    {
        throw err;
    }
    /** @brief This function gets the address where the symbol is loaded into memory, and creates an instance of Template type from it
        *  @param name Exact name of the symbol loaded into memory
        *  @return std::shared_ptr<T> A shared_ptr of the instance created of type T
    */
    template <typename T>
    std::shared_ptr<T> getInstance(const std::string& name) const
    {
        std::shared_ptr<T>(*sample)();
        sample = reinterpret_cast<std::shared_ptr<T>(*)()>(LIBFUNC(_handler, name.c_str()));
        #if defined(_WIN32)
            if (!sample)
                throw ErrorDLLoader("Error: Encounter error while opening lib.");
        #else
            char* error;
            if ((error = dlerror()) != NULL)
                throw ErrorDLLoader(error);
        #endif
        return (sample());
    }
    /** @brief Default copy ctor of DLLoader */
    DLLoader(const DLLoader& other) = default;
    /** @brief Default overloaded '=' operator of DLLoader */
    DLLoader& operator=(const DLLoader& other) = default;
    /** @brief Ctor of DLLoader */
    ~DLLoader()
    {
        int ret = 0;
        ret = CLOSELIB(_handler);
        #if defined(_WIN32)
            if (ret == 0)
                std::cerr << "Error: Encounter error while opening lib." << std::endl;
        #else
            if (ret != 0)
                std::cerr << dlerror() << std::endl;
        #endif
    }
private:
    /** @brief Contains the type of the dynamic library */
    LIBTYPE _handler;
};
#endif /* !DLLOADER_HPP_ */
