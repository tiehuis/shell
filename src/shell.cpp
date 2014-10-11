#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <unistd.h>
#include "shcom.h"
#include "shio.h"

static const std::string ps1 = "-> ";

int main(void)
{
    Shell::setup_term();
    std::vector<std::string> Completions;
    std::string Command;
    
    std::cout << ps1;
    std::flush(std::cout);

    while (1) {
        if (Shell::kbhit()) {
            char c = Shell::getch();

            if (c == '\t') { 
                Completions.clear();
                size_t options = Shell::autocomplete(Completions, Command);

                if (options == 1) {
                    Command = Completions[0];
                    std::cout << '\r';
                    std::cout << ps1 << Command;
                }
                else if (options) {
                    std::cout << std::endl;
                    for (auto str : Completions)
                        std::cout << "-" << str << std::endl;
                    std::cout << ps1 << Command;
                }

            }
            else if (c == '\n') {
                std::cout << '\r';
                std::cout << ps1 << Command << std::endl;
                std::cout << ps1;
                Command.clear();
            }
            else if (c == '\b' || c == 127) {
                if (!Command.empty()) {
                    Command.pop_back();
                    std::cout << "\b \b";
                }
            }
            else if (std::isprint(c)) {
                Command.push_back(c);
                std::cout << c;
            }
            else {
                /* Other things to put here */
            }

            std::flush(std::cout);
        }
    }

    exit(0);
}
