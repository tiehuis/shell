#include <vector>
#include <string>
#include "shhist.h"

/* Keep an empty string in history */
static std::vector<std::string> history = { "" };

/* Using an iterator here would be better */
static std::size_t index = 0;

/* Check bounds properly for all cases */
bool Shell::historyend(void)
{
    return index == history.size() - 1;
}

bool Shell::historybegin(void)
{
    return index == 0;
}

std::string& Shell::nexthistory(void)
{
    return history[index++];
}

std::string& Shell::prevhistory(void)
{
    return history[index--];
}

/* Alter so that we remove any history item we used */
void Shell::addhistory(std::string &command)
{
    history.pop_back();
    history.push_back(command);
    history.push_back("");
    index = history.size() - 2;
}
