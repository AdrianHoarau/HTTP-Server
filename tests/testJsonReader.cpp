/*
** EPITECH PROJECT, 2020
** B-YEP-500-NAN-5-1-zia-arthur.bertaud
** File description:
** testJsonReader.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "jsonReader.hpp"
#include "Error.hpp"
#include <iostream>
#include <unistd.h>

class OSRedirector {
    private:
        std::ostringstream _oss;
        std::streambuf *_backup;
        std::ostream& _c;

    public:
        OSRedirector(std::ostream& c) : _c(c) {
            _backup = _c.rdbuf();
            _c.rdbuf(_oss.rdbuf());
        }

        ~OSRedirector() {
            _c.rdbuf(_backup);
        }

        const std::string getContent() {
            _oss << std::flush;
            return _oss.str();
        }
};

Test(testPathError, jsonReader)
{
    try {
        jsonReader jReader("unexistantfile");
    }
    catch (Error& e) {
        cr_assert(std::strcmp(e.what(), "Error: The given path isn't valid.") == 0);
    }
}

Test(testJsonError, jsonReader)
{
    std::string tab[] = {
        "{\n",
        "    \"zia\": {\n",
        "        \"modules\": [\n",
        "            \"PHP CGI\",\n",
        "            \"SSL/TSL\",\n",
        "            \"Snake\",\n",
        "            \"File Server\"\n",
        "        ]\n",
        "    }\n",
        "\0"
    };
    std::ofstream outfile ("test.txt");
    for (int index = 0; tab[index].length() != 0; index++)
        outfile << tab[index];
    outfile.close();
    try {
        jsonReader jReader("test.txt");
    } catch (nlohmann::json::exception const& jsonErr) {
        cr_assert(std::strcmp(jsonErr.what(), "[json.exception.parse_error.101] parse error at 146: syntax error - unexpected end of input; expected \'}\'") == 0);
    }
    sleep(1);
}

Test(testJsonOutput, jsonReader)
{
    std::string tab[] = {
        "{\n",
        "    \"zia\": {\n",
        "        \"modules\": [\n",
        "            \"PHP CGI\",\n",
        "            \"SSL/TSL\",\n",
        "            \"Snake\",\n",
        "            \"File Server\"\n",
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
        OSRedirector oss(std::cout);
        jsonReader jReader("test.txt");
        std::cout << jReader.getJsonFile();
       
        cr_assert_eq(oss.getContent(), "{\"zia\":{\"modules\":[\"PHP CGI\",\"SSL/TSL\",\"Snake\",\"File Server\"]}}");
    } catch (nlohmann::json::exception const& jsonErr) {
    }
    sleep(1);
}