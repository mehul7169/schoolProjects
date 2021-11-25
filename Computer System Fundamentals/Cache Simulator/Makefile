#
# Makefile for CSF Assignment 3
#

CSIM_SRCS = csim.cpp Cache.cpp Set.cpp Block.cpp
CSIMFLAGS = -Wall -Wextra -pedantic -std=c++11 -g

%.o : %.cpp
	gcc $(CSIMFLAGS) -c $*.cpp

csim : csim.o Set.o Block.o Cache.o # add in csim make
	gcc -o $@ csim.o Set.o Block.o Cache.o -lstdc++ -lm -g

# Use this target to create a zipfile that you can submit to Gradescope
.PHONY: solution.zip
solution.zip :
	rm -f solution.zip
	zip -9r $@ Makefile *.h *.cpp *.S README.md Makefile

clean :
	rm -f *.o csim depend.mak solution.zip

depend.mak :
	touch $@

depend :
	gcc $(CSIMFLAGS) -M $(CSIM_SRCS) > depend.mak

include depend.mak
