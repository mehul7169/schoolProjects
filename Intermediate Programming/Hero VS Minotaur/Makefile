# Reference Makefile. You are welcome to use this for your project.
# You may modify it, but make sure that, at a minimum, the following
# targets all build correctly and work:
#   minotaur
#   positiontest
#   mazetest
#   gametest
#   tiletest

CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -std=c++11

# Source files needed only for the driver program
MAIN_SRCS = main.cpp textui.cpp
MAIN_OBJS = $(MAIN_SRCS:%.cpp=build/%.o)

# Source files needed only for the curses driver program
TMAIN_SRCS = tmain.cpp cursesui.cpp
TMAIN_OBJS = $(TMAIN_SRCS:%.cpp=build/%.o)

# Source files containing game classes, needed by both driver programs
# and test programs.
GAME_SRCS = maze.cpp tile.cpp floor.cpp wall.cpp goal.cpp mysterytile.cpp tilefactory.cpp \
	game.cpp \
	entity.cpp entitycontroller.cpp \
	uicontrol.cpp chasehero.cpp astarchasehero.cpp inanimate.cpp \
	mysterycontroller.cpp ecfactory.cpp \
	ui.cpp \
	gamerules.cpp basicgamerules.cpp
OBJS = $(GAME_SRCS:%.cpp=build/%.o)

# Source files needed only for test programs.
TEST_SRCS = tctestpp.cpp scriptedcontrol.cpp \
	positiontest.cpp tiletest.cpp mazetest.cpp gametest.cpp
TEST_OBJS = $(TEST_SRCS:%.cpp=build/%.o)

build/%.o : %.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $*.cpp -o build/$*.o

all : minotaur positiontest tiletest mazetest gametest

minotaur : $(MAIN_OBJS) $(OBJS)
	$(CXX) -o $@ $(MAIN_OBJS) $(OBJS)

# Target for the curses driver program (called "tminotaur".)
#tminotaur : $(TMAIN_OBJS) $(OBJS)
#	$(CXX) -o $@ $(TMAIN_OBJS) $(OBJS) -lncurses


positiontest : build/positiontest.o build/tctestpp.o
	$(CXX) -o $@ build/positiontest.o build/tctestpp.o

TILETEST_OBJS = build/tile.o build/wall.o build/floor.o build/goal.o build/mysterytile.o \
	build/tilefactory.o build/entity.o

tiletest : build/tiletest.o build/tctestpp.o $(TILETEST_OBJS)
	$(CXX) -o $@ build/tiletest.o build/tctestpp.o $(TILETEST_OBJS)

MAZETEST_OBJS = build/maze.o build/tile.o build/wall.o build/floor.o build/goal.o build/mysterytile.o \
	build/tilefactory.o

mazetest : build/mazetest.o build/tctestpp.o $(MAZETEST_OBJS)
	$(CXX) -o $@ build/mazetest.o build/tctestpp.o $(MAZETEST_OBJS)

gametest : build/gametest.o build/tctestpp.o build/scriptedcontrol.o $(OBJS)
	$(CXX) -o $@ build/gametest.o build/tctestpp.o build/scriptedcontrol.o $(OBJS)

clean :
	rm -f minotaur tminotaur positiontest tiletest mazetest gametest
	rm -rf build

# Running the command "make depend" will automatically generate correct
# header dependencies for all .o files
depend :
	($(CXX) $(CXXFLAGS) -MM $(MAIN_SRC) $(TMAIN_SRC) $(GAME_SRCS) $(TEST_SRCS) \
		| perl -ne 'if (/^[a-z]/) { print "build/"; } print') \
		> depend.mak

depend.mak :
	touch $@

include depend.mak
