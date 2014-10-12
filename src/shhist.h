#ifndef _SHHIST_H_
#define _SHHIST_H_

namespace Shell {
    bool historyend(void);
    bool historybegin(void);
    std::string& nexthistory(void);
    std::string& prevhistory(void);
    void addhistory(std::string &command);
}

#endif
