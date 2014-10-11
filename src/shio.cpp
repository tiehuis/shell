#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "shio.h"

static pid_t shell_pid;
static struct termios init;

static void signal_handler(int signo)
{
    if (signo == SIGINT) {
        std::cout << "^C" << std::endl << "-> ";
        if (getpid() != shell_pid)
            raise(SIGTERM);
    }
}

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

    shell_pid = getpid();
    signal(SIGINT, signal_handler);
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
