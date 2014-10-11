#include <cstdio>
#include <cstdlib>
#include <termios.h>
#include <unistd.h>
#include "shio.h"

static struct termios init;

static void destroy_term(void)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &init);
}

void Shell::setup_term(void)
{
    struct termios newt;
    tcgetattr(STDIN_FILENO, &init);
    newt = init;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    std::atexit(destroy_term);
}

int Shell::getch(void)
{
    return std::getchar();
}

bool Shell::kbhit(void)
{
    struct timeval tv;
    fd_set rdfs;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);
    select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &rdfs);
}
