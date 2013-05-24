EXE=bblock
CCFLAGS=-std=c++11 -I./include -lcurses -lpam
CC=g++
DEPXX=g++ -MM
DEPFILE=makefile.dep

# Object files
#SRC=$(wildcard src/*.cpp)
SRC=$(shell find . -type f -name '*.cpp')

OBJS=${SRC:.cpp=.o}
#OBJS=$(SRC:src/%.cpp=obj/%.o)


# First rule is a default rule, executed with only gmake
default: $(EXE)

# gmake name_of_executable program defined in EXE
$(EXE): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(EXE)

# Object files are compiled using ..., dependencies are found
# from DEPFILE file
%.o: %.cpp
	$(CC) -c $(CCFLAGS) $< -o $@


# finds out the file dependencies automatically and adds them to a file
depend:
	@echo "Updating $(DEPFILE)"
	$(DEPXX) > $(DEPFILE)

$(DEPFILE):
	$(DEPXX) $(CCFLAGS) > $(DEPFILE)


# include information from dependency file to this file
-include $(DEPFILE)


# removes all the object files and makefile.dep file
clean:
	rm $(OBJS) $(EXE) $(DEPFILE)

# Other stuff
lines:
	wc -l ${SRC}


