#ifndef _SHCOM_H_
#define _SHCOM_H_

namespace Shell {
    size_t autocomplete(std::vector<std::string> &Completions, 
            const std::string &Command);
}

#endif
