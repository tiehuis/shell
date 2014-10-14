#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include "shhist.h"
#include "shglo.h"

/* Keep an empty string in history */
static std::vector<std::string> history = { "" };

static std::size_t index = 0;

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
    return history[++index];
}

std::string& Shell::prevhistory(void)
{
    return history[--index];
}

void Shell::addhistory(std::string &command)
{
    if (index != history.size() - 1)
        history.erase(history.begin() + index);

    if (history.size() > Shell::maxhistory)
        history.erase(history.begin());

    history.pop_back();
    history.push_back(command);
    history.push_back("");
    index = history.size() - 1;
}
