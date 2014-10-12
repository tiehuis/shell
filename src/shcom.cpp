#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <iterator>
#include <cstring>
#include <cerrno>
#include <dirent.h>
#include "shcom.h"

static std::set<std::string> commandset = {
    "cd", "exit"
};

static void gathercommands(void)
{
    /* Full vector with possible matches from /usr/bin */
    DIR *com = opendir("/usr/bin/");
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
