/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** phpCgiModule.cpp
*/

#include "phpCgiModule.hpp"
#include <algorithm>
#include <deque>

phpCgiModule::phpCgiModule() : _path()
{
    _methods.insert(std::make_pair("helloWorld", &phpCgiModule::helloWorld));
    _methods.insert(std::make_pair("webName", &phpCgiModule::webName));
    _methods.insert(std::make_pair("calendar", &phpCgiModule::calendar));
}

void phpCgiModule::helloWorld(HTTP::HTTPObject& req)
{
    std::string pathScript = "php-cgi -f " + _path + "HelloWorld.php";

    std::string output = exec(pathScript);
    setExecBody(output, req);
}

void phpCgiModule::fillArg(const std::string& arg, HTTP::HTTPObject& req, bool& take, std::vector <std::string>& names)
{
    auto params =  req.getParams();

    for (auto it = params.begin(); it != params.end(); ++it) {
        if (arg == it->first) {
            if (take == true)
                names.push_back(it->second);
            if (it->second == "webName")
                take = true;
        } 
    }
    
}

void phpCgiModule::calendar(HTTP::HTTPObject& req)
{
    std::string pathScript = "php-cgi -f " + _path + "calendarioSessao.php";

    std::string output = exec(pathScript);
    setExecBody(output, req);
}

void phpCgiModule::webName(HTTP::HTTPObject& req)
{
    std::string pathScript = "php-cgi -f " + _path + "WebName.php ";
    std::vector <std::string> names;
    std::string firstName = "prenom=";
    std::string lastName = "nom=";
    auto params =  req.getParams();
    bool take = false;
    int i = 0;
    std::vector<std::string> sortMap;

    for (auto it = params.begin(); it != params.end(); ++it)
        sortMap.push_back(it->first);
    std::sort(sortMap.begin(), sortMap.end());
    for (std::vector<std::string>::iterator it_s = sortMap.begin(); it_s != sortMap.end(); ++it_s)
        fillArg(*it_s, req, take, names);
    for (std::vector<std::string>::iterator it = names.begin(); it != names.end(); it++) {
        if (i == 0)
            firstName += (*it);
        else if (i == 1)
            lastName += (*it);
        i++;
    }
    pathScript += firstName + " " + lastName;
    std::string output = exec(pathScript);
    setExecBody(output, req);
}

void phpCgiModule::setExecBody(const std::string& output, HTTP::HTTPObject& req)
{
    int check = std::strcmp(output.c_str(), "No input file specified.\n");
    
    if (check == 0)
        req.setHTTPCode("404");
    else
        req.setBody(output);
}

void phpCgiModule::processRequest(HTTP::HTTPObject& req)
{
    auto params =  req.getParams();
    bool err = false;

    for (auto it = params.begin(); it != params.end(); ++it) {
        for (auto& met : _methods) {
            if (met.first == it->second) {
                (this->*(met.second))(req);
                err = true;
            }
        }
    }
    if (err == false)
        req.setHTTPCode("400");
    /*std::string phpFile = req[HTTP::BODY]["Body"][0];
    std::ofstream tmpFile ("tmp.php");

    tmpFile << phpFile;
    tmpFile.close();
    std::string output = exec("php-cgi tmp.php");
    std::cout << "output =" << output <<std::endl;
    std::remove("tmp.php");
    req.setBody(output);*/
}

void phpCgiModule::init(const std::string& path) 
{ 
    _path = path;
}

std::string phpCgiModule::exec(const std::string& cmd) 
{
    #if defined (_WIN32)
        return (_windowsExec.exec(cmd));
    #else
        return (_linuxExec.exec(cmd));
    #endif

}

moduleType phpCgiModule::getModuleType() const
{
    return (moduleType::PHPCGI);
}

#if defined (_WIN32)
    
    extern "C"  __declspec(dllexport)
    void *entryPoint()
    {
        return (new std::shared_ptr<phpCgiModule>(new phpCgiModule));
    }

#else

    extern "C" std::shared_ptr<IModule> entryPoint()
    {
        return (std::make_shared<phpCgiModule>());
    }

#endif
