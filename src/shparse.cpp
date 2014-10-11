#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include "shparse.h"

void Shell::parsecommand(std::vector<std::string> &parsed, const std::string &command)
{
    std::istringstream buf(command);
    std::string token;
    while (std::getline(buf, token, ' '))
        parsed.push_back(token);
}
