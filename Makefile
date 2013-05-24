EXE=bblock
CCFLAGS=-std=c++11 -I./include -lcurses -lpam
CC=g++
DEPXX=g++ -MM
DEPFILE=makefile.dep

SRC=$(shell find . -type f -name '*.cpp')
OBJS=${SRC:.cpp=.o}

default: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CCFLAGS) $(OBJS) -o $(EXE)

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $< -o $@

depend:
	@echo "Updating $(DEPFILE)"
	$(DEPXX) > $(DEPFILE)

$(DEPFILE):
	$(DEPXX) $(CCFLAGS) > $(DEPFILE)

-include $(DEPFILE)

clean:
	rm $(OBJS) $(EXE) $(DEPFILE)

lines:
	wc -l ${SRC}
