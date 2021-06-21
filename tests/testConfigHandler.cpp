/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** testConfigHandler.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "configHandler.hpp"
#include "pathHandler.hpp"
#include "Error.hpp"
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <unistd.h>

Test(testPathSoError, configHandler)
{
    std::string tab[] = {
        "{\n",
        "    \"zia\": {\n",
        "        \"modules\": [\n",
        "            \"libphpCgiModulett\",\n",
        "            \"sslModule\",\n",
        "            \"libsnakeModule\"\n",
        "        ]\n",
        "    }\n",
        "}",
        "\0"
    };
    std::ofstream outfile ("test.txt");
    for (int index = 0; tab[index].length() != 0; index++)
        outfile << tab[index];
    outfile.close();
    try {
        configPaths paths;
        paths.configPath = "test.txt";
        configHandler configHand(paths);
    }
    catch (Error& e) {
        cr_assert(std::strcmp(e.what(), "Error config file: the default config is not correct") == 0);
    }
    sleep(1);
}

Test(TestTagErr, configHandler)
{
    std::string tab[] = {
        "{\n",
        "    \"zia\": {\n",
        "        \"modules\": [\n",
        "            \"Error\",\n",
        "            \"Error\",\n",
        "            \"Error\",\n",
        "            \"Error\"\n",
        "        ]\n",
        "    }\n",
        "}",
        "\0"
    };
    std::ofstream outfile ("testErr.txt");
    for (int index = 0; tab[index].length() != 0; index++)
        outfile << tab[index];
    outfile.close();
    try {
        configPaths paths;
        paths.configPath = "testErr.txt";
        configHandler configHand(paths);
    }
    catch (Error& e) {
        cr_assert(std::strcmp(e.what(), "Error config file: the default config is not correct") == 0);
    }
    sleep(1);
}

Test(TestAllGood, configHandler)
{
    std::filesystem::create_directories("FileSo");
    std::string tab[] = {
        "{\n",
        "    \"zia\": {\n",
        "        \"modules\": [\n",
        "            \"phpCgiModule\",\n",
        "            \"sslModule\",\n",
        "            \"snakeModule\"\n",
        "        ]\n",
        "    }\n",
        "}",
        "\0"
    };
    std::ofstream phpSo ("FileSo/libphpCgiModule.so");
    phpSo.close();
    std::ofstream sslSo ("FileSo/libsslModule.so");
    sslSo.close();
    std::ofstream snakeSo ("FileSo/libsnakeModule.so");
    snakeSo.close();
    std::ofstream outfile ("test.txt");
    std::unordered_map<moduleType, std::string> modulePaths;
    for (int index = 0; tab[index].length() != 0; index++)
        outfile << tab[index];
    outfile.close();
    try {
        configPaths paths;
        paths.configPath = "test.txt";
        paths.dirPath = "FileSo/";
        configHandler configHand(paths);
        modulePaths = configHand.getListModules();
    }
    catch (Error& e) {
    }
    cr_assert_eq(modulePaths[moduleType::PHPCGI], "FileSo/libphpCgiModule.so");
    sleep(1);
}

Test(TestgetModule, configHandler)
{
    int size = 0;
    std::filesystem::create_directories("FileSo");
    std::string tab[] = {
        "{\n",
        "    \"zia\": {\n",
        "        \"modules\": [\n",
        "            \"phpCgiModule\",\n",
        "            \"sslModule\",\n",
        "            \"snakeModule\"\n",
        "        ]\n",
        "    }\n",
        "}",
        "\0"
    };
    std::ofstream phpSo ("FileSo/libphpCgiModule.so");
    phpSo.close();
    std::ofstream sslSo ("FileSo/libsslModule.so");
    sslSo.close();
    std::ofstream snakeSo ("FileSo/libsnakeModule.so");
    snakeSo.close();
    std::ofstream outfile ("test.txt");
    for (int index = 0; tab[index].length() != 0; index++)
        outfile << tab[index];
    outfile.close();
    try {
        configPaths paths;
        paths.configPath = "test.txt";
        paths.dirPath = "FileSo/";
        configHandler configHand(paths);
        auto& modulePaths = configHand.getListModules();
        modulePaths.clear();
        modulePaths = configHand.getListModules();
        size = modulePaths.size();
        cr_assert_eq(size, 0);
    }
    catch (Error& e) {
    }
    sleep(1);
}

Test(TestgetProcess, configHandler)
{
    int size = 0;
    std::filesystem::create_directories("FileSo");
    std::string tab[] = {
        "{\n",
        "    \"zia\": {\n",
        "        \"modules\": [\n",
        "            \"phpCgiModule\",\n",
        "            \"sslModule\",\n",
        "            \"snakeModule\"\n",
        "        ]\n",
        "    }\n",
        "}",
        "\0"
    };
    std::ofstream phpSo ("FileSo/libphpCgiModule.so");
    phpSo.close();
    std::ofstream sslSo ("FileSo/libsslModule.so");
    sslSo.close();
    std::ofstream snakeSo ("FileSo/libsnakeModule.so");
    snakeSo.close();
    std::ofstream outfile ("test.txt");
    for (int index = 0; tab[index].length() != 0; index++)
        outfile << tab[index];
    outfile.close();
    try {
        configPaths paths;
        paths.configPath = "test.txt";
        paths.dirPath = "FileSo/";
        configHandler configHand(paths);
        processingList processList = configHand.getCopyProcessList();
        size = processList.getSize();
        cr_assert_eq(size, 3);
    }
    catch (Error& e) {
    }
    sleep(1);
}