CC	    = g++
CFLAGS  = -std=c++11 -Wall -Wextra
SRCS    = src/shell.cpp src/shio.cpp src/shcom.cpp src/shexec.cpp src/shparse.cpp \
		  src/shbuiltin.cpp src/shhist.cpp
OBJS    = $(SRCS:.cpp=.o)

all: $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o shell
