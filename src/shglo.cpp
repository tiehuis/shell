#include "shglo.h"

namespace Shell {
    const std::string ps1        = "\033[33m:\033[32m->\033[0m ";
    const std::size_t comcutoff  = 40;
    const std::size_t maxhistory = 100;
    pid_t pid = 0;
}
