#ifndef _SHCOM_H_
#define _SHCOM_H_

namespace Shell {
    std::size_t autocomplete(std::vector<std::string> &completions, 
            const std::string &command);
}

#endif
