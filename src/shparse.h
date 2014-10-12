#ifndef _SHPARSE_H_
#define _SHPARSE_H_

namespace Shell {
    void tokenize(std::vector<std::string> &parsed, const std::string &command,
            const char delimiter = ' ');
}

#endif
