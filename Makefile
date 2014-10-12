CXX		 = g++
LD		 = ld
CXXFLAGS = -std=c++11 -Wall -Wextra
LFLAGS   =

TARGET	 = shell
DIRSRC   = src
DIRBUILD = build
SRCS	 = $(wildcard $(DIRSRC)/*.cpp)
OBJS	 = $(addprefix $(DIRBUILD)/, $(notdir $(SRCS:.cpp=.o)))

$(TARGET): $(OBJS)
	$(CXX) $(LFLAGS) $(OBJS) -o $@

$(DIRBUILD)/%.o: $(DIRSRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(DIRBUILD)/$(OBJS)
	@rm -f $(TARGET)
