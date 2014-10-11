#include <vector>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "shbuiltin.h"
#include "shexec.h"

int Shell::executecommand(std::vector<std::string> &commands)
{
    if (commands.size() == 0) {
        return 0;
    }
    else if (Shell::isbuiltin(commands[0])) {
        Shell::execbuiltin(commands);
    }
    else {
        pid_t pid = fork();

        /* Convert to c-style strings for exevp */
        std::vector<char*> argv(commands.size() + 1);
        for (std::size_t i = 0; i != commands.size(); ++i)
            argv[i] = &commands[i][0];

        if (pid == 0) {
            if (execvp(argv[0], argv.data()) == -1) {
                std::cerr << "\033[31m";
                std::cerr << "Could not execute command: " << commands[0] << std::endl;
                std::cerr << "\033[0m";
                _exit(1);
            }
        }
        else if (pid > 0) {
            int exitstat;
            waitpid(pid, &exitstat, 0);

            /* Don't deal with specific errors for now */
            if (WIFEXITED(exitstat))
                return 0;
            else
                return 1;
        }
        else {
            std::cerr << "Failed to fork: " << commands[0];
        }
    }

    return 0;
}
