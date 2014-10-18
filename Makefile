CXX	     = g++
CXXFLAGS = -std=c++11 
#-march=native -O2

LD	     = ld
LIBS	 = 
INCLUDES = 
LFLAGS   = $(INCLUDES) $(LIBS)

TARGET	 = shell
DIRSRC   = src
DIRBUILD = build
SRCS	 = $(wildcard $(DIRSRC)/*.cpp)
OBJS	 = $(addprefix $(DIRBUILD)/, $(notdir $(SRCS:.cpp=.o)))

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LFLAGS)

$(DIRBUILD)/%.o: $(DIRSRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -f $(TARGET)
