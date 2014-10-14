#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>
#include "shbuiltin.h"

static std::set<std::string> builtins = {
    "exit", "cd"
};

static void sh_exit(void)
{
    exit(0);
}

static void sh_cd(std::vector<std::string> &arguments)
{
    if (arguments.size() <= 1) {
        /* Do nothing */
    }
    else {
        if (chdir(arguments[1].c_str()) == -1)
            std::cerr << "shell: " << arguments[1] << " : no such file or directory";
    }
}

bool Shell::isbuiltin(const std::string &command)
{
    return builtins.find(command) != builtins.end();
}

void Shell::execbuiltin(std::vector<std::string> &command)
{
   if (command[0] == "exit")
       sh_exit();
   else if (command[0] == "cd")
       sh_cd(command);
}
