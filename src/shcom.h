#ifndef _SHCOM_H_
#define _SHCOM_H_

#include <vector>

namespace Shell {
    void gathercommands(void);
    std::size_t autocomplete(std::vector<std::string> &completions, 
            const std::string &command);
}

#endif
