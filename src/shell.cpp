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
#include "shglo.h"

using std::cout;
using std::endl;

int main(void)
{
    Shell::setup_term();
    std::string command;
    
    cout << Shell::ps1;
    std::flush(cout);

    while (1) {
        char c = Shell::getch();

        if (c == '\033') {
            Shell::getch();
            switch (Shell::getch()) {
            case 'A':
                if (!Shell::historybegin()) {
                    command = Shell::prevhistory();
                    cout << "\033[2K\r" << Shell::ps1 << command;
                }
                break;
            case 'B':
                if (!Shell::historyend()) {
                    command = Shell::nexthistory();
                    cout << "\033[2K\r" << Shell::ps1 << command;
                }
                break;
            case 'C':
            case 'D':
                /* Ignore left and right keys for now */
                break;
            }
        }
        else if (c == 4) {
            if (command.empty()) {
                cout << '\r' << Shell::ps1 << "exit" << endl;
                std::vector<std::string> splitcommand;
                Shell::tokenize(splitcommand, "exit");
                Shell::executecommand(splitcommand);
            }
        }
        else if (c == '\t') { 
            std::vector<std::string> completions;
            size_t options = Shell::autocomplete(completions, command);

            if (options == 1) {
                command = completions[0];
                cout << '\r' << Shell::ps1 << command;
            }
            else if (options) {
                if (options > Shell::comcutoff) {
                    cout << endl << "Display all " << options;
                    cout << " matches? (y) or (n)" << endl;
    
                    char c;
                    do {
                        c = std::toupper(Shell::getch());
                    } while (c != 'Y' && c != 'N');
                    
                    if (c == 'N') {
                        cout << endl << Shell::ps1 << command;
                        continue;
                    }
                }

                cout << endl;
                for (auto str : completions)
                    cout << "\033[36m" << str << endl;
                cout << "\033[0m" << Shell::ps1 << command;
            }
        }
        else if (c == '\n') {
            cout << '\r' << Shell::ps1 << command << endl;

            /* Try to execute the command */
            std::vector<std::string> splitcommand;
            Shell::tokenize(splitcommand, command);
            Shell::executecommand(splitcommand);
            Shell::addhistory(command);
            command.clear();
            cout << Shell::ps1;
        }
        else if (c == '\b' || c == 127) {
            if (!command.empty()) {
                command.pop_back();
                cout << "\b \b";
            }
        }
        else if (std::isprint(c)) {
            command.push_back(c);
            cout << c;
        }
        else {
            /* Other things to put here */
        }

        std::flush(cout);
    }

    exit(0);
}
