#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <unistd.h>
#include "shio.h"
#include "shcom.h"
#include "shexec.h"
#include "shparse.h"
#include "shhist.h"

static const std::string ps1 = "-> ";

int main(void)
{
    Shell::setup_term();
    std::string command;
    
    std::cout << ps1;
    std::flush(std::cout);

    while (1) {
        char c = Shell::getch();

        if (c == '\033') {
            Shell::getch();
            switch (Shell::getch()) {
            case 'A':
                if (!Shell::historybegin()) {
                    command = Shell::prevhistory();
                    std::cout << "\033[2K" << '\r';
                    std::cout << ps1 << command;
                }
                break;
            case 'B':
                if (!Shell::historyend()) {
                    command = Shell::nexthistory();
                    std::cout << "\033[2K" << '\r';
                    std::cout << ps1 << command;
                }
                break;
            case 'C':
            case 'D':
                /* Ignore left and right keys for now */
                break;
            }
        }
        if (c == 4) {
            if (command.empty()) {
                std::cout << std::endl;
                exit(0);
            }
        }
        else if (c == '\t') { 
            std::vector<std::string> completions;
            size_t options = Shell::autocomplete(completions, command);

            if (options == 1) {
                command = completions[0];
                std::cout << '\r';
                std::cout << ps1 << command;
            }
            else if (options) {
                std::cout << "\033[36m";
                std::cout << std::endl;
                for (auto str : completions)
                    std::cout << "-" << str << std::endl;
                std::cout << "\033[0m";
                std::cout << ps1 << command;
            }
        }
        else if (c == '\n') {
            std::cout << '\r';
            std::cout << ps1 << command << std::endl;
            std::cout << ps1;

            /* Try to execute the command */
            std::vector<std::string> splitcommand;
            Shell::parsecommand(splitcommand, command);
            Shell::executecommand(splitcommand);
            Shell::addhistory(command);
            command.clear();
        }
        else if (c == '\b' || c == 127) {
            if (!command.empty()) {
                command.pop_back();
                std::cout << "\b \b";
            }
        }
        else if (std::isprint(c)) {
            command.push_back(c);
            std::cout << c;
        }
        else {
            /* Other things to put here */
        }

        std::flush(std::cout);
    }

    exit(0);
}
