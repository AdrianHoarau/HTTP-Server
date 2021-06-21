/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** configHandler.cpp
*/

#include "configHandler.hpp"
#include <iostream>

configHandler::configHandler(const configPaths& paths) try : _fileErr(), _processList(), _json(paths.configPath), \
_modulePaths(), _paths(), _certificatePath(), _CgiDir()
{
    std::string pathDirclean;
    _fileErr.open(paths.configPath);
    if (!_fileErr) {
        defaultFile();
    }
    if (paths.dirPath.back() != '/') {
        pathDirclean = paths.dirPath + "/";
        _paths.dirPath = pathDirclean;
    } else
        _paths.dirPath = paths.dirPath;  
    _paths.configPath = paths.configPath;
    load();
} catch (Error const& err) {
    throw err;
}

bool configHandler::fileExists(const std::filesystem::path& p)
{
    std::filesystem::file_status s = std::filesystem::file_status{};
    if(std::filesystem::status_known(s) ? std::filesystem::exists(s) : std::filesystem::exists(p))
        return false;
    else
        return true;
}

int configHandler::nthOccurrence(const std::string& str, const std::string& findMe, int nth)
{
    size_t pos = 0;
    int cnt = 0;

    while(cnt != nth) {
        pos++;
        pos = str.find(findMe, pos);
        if (pos == std::string::npos)
            return -5;
        cnt++;
    }
    return pos;
}

bool configHandler::checkTag(std::string line)
{
    std::string tag = line;
    std::string path = line;
    int foundTag = nthOccurrence(line, "\"", 1) + 1;
    int foundTag_s = nthOccurrence(line, "\"", 2) - foundTag;
    int foundPath = nthOccurrence(line, "\"", 3) + 1;
    int foundPath_s = nthOccurrence(line, "\"", 4) - foundPath;
        
    if (foundTag < 0 || foundTag_s < 0 || foundPath < 0 || foundPath_s < 0)
        return false;
    tag = tag.substr((size_t)foundTag, (size_t)foundTag_s);
    path = path.substr((size_t)foundPath, (size_t)foundPath_s);
    if (tag == "SSL Certificate Path") {
        _certificatePath = path;
        return fileExists(_certificatePath);
    } else if (tag == "CGI Dir Path") {
        _CgiDir = path;
        return fileExists(_CgiDir);
    }
    return false;
}

void configHandler::load()
{
    try {
        _json.loadConfigFile();
    } catch (nlohmann::json::exception const& jsonErr) {
        defaultFile();
        return;
    }
    std::string line("");
    std::string name("");
    bool PosModule = false;
    std::ifstream jsonFile(_paths.configPath);
    size_t endModule = std::string::npos;
    bool defaultCheck = false;

    try {
        while (std::getline(jsonFile, line, '\n')) {
            defaultCheck = checkTag(line);
            if (line.find("\"") != std::string::npos) {
                if (PosModule == true) {
                    name = getName(line);
                    defaultCheck = addModuleJson(name);
                }
                if (checktagModule(line) == true)
                    PosModule = true;
            }
            endModule = line.find("]");
            if (PosModule == true && endModule != std::string::npos)
               PosModule = false;
            if (defaultCheck == true)
                break;
        }
        if (defaultCheck == true)
            defaultFile();
    } catch (Error const& err) {
        throw err;
    }
}

std::string configHandler::getCgiPath()const
{
    return _CgiDir;
}

std::string configHandler::getCertificatePath()const
{
    return _certificatePath;
}

processingList configHandler::getCopyProcessList()
{
    return _processList;
}

std::unordered_map<moduleType, std::string>& configHandler::getListModules()
{
    return _modulePaths;
}

std::string configHandler::getName(std::string line)
{
    std::string name = "";
    size_t found = line.find("\"");
    std::size_t foundLast = line.find("\"", found+1);

    foundLast -= found;
    found++;
    foundLast--;
    name = line.substr(found, foundLast);
    return name;
}

bool configHandler::checktagModule(std::string& line)
{
    std::string tag = getName(line);
    size_t pos = line.find("[");
    
    if (tag == "modules" && pos != std::string::npos)
        return true;
    return false;
}

bool configHandler::fexists(const std::string& filename)
{
    std::ifstream ifile(filename);
    return ifile.good();
}

void configHandler::defaultFile()
{
    std::vector <std::string> defaultPaths;
    std::string paths;

    _modulePaths.clear();
    _processList.clear();
    _certificatePath = "";
    _CgiDir = "";
    for (auto it= _moduleType.begin(); it != _moduleType.end(); ++it) {
        paths = "build/lib/lib" + it->first + ".so";
        defaultPaths.push_back(paths);
    }
    for (std::vector<std::string>::iterator it = defaultPaths.begin(); it != defaultPaths.end(); it++) {
        if (fexists(*it) == false) {
            throw ErrorConfigDefault();
            return;
        }
    }
    for (auto it= _moduleType.begin(); it != _moduleType.end(); ++it) {
        paths = "build/lib/lib" + it->first + ".so";
        _modulePaths.insert({it->second, paths});
        _processList.add(it->second);
    }
    _certificatePath = "config/SSL/mycert.pem";
    _CgiDir = "config/PHP/";
}

bool configHandler::addModuleJson(const std::string& name)
{
    std::string path = _paths.dirPath + "lib" + name + ".so";
    if (_moduleType.find(name) == _moduleType.end())
        return true;
    std::ifstream infile(path);
    if (infile.good() == false)
        return true;
    _modulePaths.insert({_moduleType.find(name)->second, path});
    _processList.add(_moduleType.find(name)->second);
    return false;
}

void configHandler::reload()
{   
    _modulePaths.clear();
    _processList.clear();
    try {
        load();
    } catch (Error const& err) {
        throw err;
    }
}