CC	    = g++
CFLAGS  = -std=c++11 -Wall -Wextra
SRCS    = src/shell.cpp src/shio.cpp src/shcom.cpp
OBJS    = $(SRCS:.cpp=.o)

all: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o shell
