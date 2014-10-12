#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <set>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <dirent.h>
#include "shparse.h"
#include "shcom.h"

static std::set<std::string> commandset = {
    "cd", "exit"
};

static void gathercommands(void)
{
    char *s = std::getenv("PATH");
    if (!s) return;

    std::string path_env(s);
    std::vector<std::string> path_vec;
    Shell::tokenize(path_vec, path_env, ':');

    for (auto component : path_vec) {
        DIR *com = opendir(component.c_str());
        if (!com) {
            std::cerr << strerror(errno) << std::endl;
        }
        else {
            struct dirent *buf;
            while ((buf = readdir(com)))
                commandset.insert(std::string(buf->d_name));
            closedir(com);
        }
    }
}

std::size_t Shell::autocomplete(std::vector<std::string> &completions, 
        const std::string &command)
{
    /* Attempt to gather commands if we haven't. Should periodically update */
    if (commandset.size() == 2)
        gathercommands();

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
