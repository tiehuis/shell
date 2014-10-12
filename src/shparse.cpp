#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include "shparse.h"

void Shell::tokenize(std::vector<std::string> &parsed, const std::string &command,
        const char delimiter)
{
    std::istringstream buf(command);
    std::string token;
    while (std::getline(buf, token, delimiter))
        parsed.push_back(token);
}
