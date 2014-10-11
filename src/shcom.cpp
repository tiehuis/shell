#include <set>
#include <string>
#include <vector>
#include <iterator>
#include "shcom.h"

static std::set<std::string> commandset = {
    "exit", "end", "close", "cleanup", "claim", "clup", "bin",
    "kill", "top", "ls", "gcc", "g++"
};

std::size_t Shell::autocomplete(std::vector<std::string> &completions, 
        const std::string &command)
{
    std::size_t found = 0;
    completions.clear();

    for (auto it : commandset) {
        if (it.find(command) == 0) {
            completions.push_back(it);
            ++found;
        }
    }

    return found;
}
