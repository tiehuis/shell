#ifndef _SHBUILTIN_H_
#define _SHBUILTIN_H_

namespace Shell {
    bool isbuiltin(const std::string &command);
    void execbuiltin(std::vector<std::string> &command);
}

#endif
