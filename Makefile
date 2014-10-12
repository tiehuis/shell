CXX		 = g++
LD		 = ld
CXXFLAGS = -std=c++11 -Wall -Wextra
LFLAGS   =

DIRSRC   = src
DIRBUILD = build
SRCS	 = $(wildcard $(DIRSRC)/*.cpp)
OBJS	 = $(addprefix $(DIRBUILD)/, $(notdir $(SRCS:.cpp=.o)))

shell: $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o $@

$(DIRBUILD)/%.o: $(DIRSRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
