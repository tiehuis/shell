#include <set>
#include <string>
#include <vector>
#include <iterator>
#include "shcom.h"

static std::set<std::string> Commands = {
    "exit", "end", "close", "cleanup", "claim", "clup", "bin",
    "kill", "top", "ls", "gcc", "g++"
};

size_t Shell::autocomplete(std::vector<std::string> &Completions, 
        const std::string &Command)
{
    size_t found = 0;
    Completions.clear();

    for (auto it : Commands) {
        if (it.find(Command) == 0) {
            Completions.push_back(it);
            ++found;
        }
    }

    return found;
}
