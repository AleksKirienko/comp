CXX=gcc
CFLAGS = -c -Wall -std=c99
FLAGS  =  -Wall -std=c99
OBJECTS = asm.o

.PHONY: clean all 

all: asm.o prog

prog: $(OBJECTS)
	$(CXX) $(FLAGS) $(OBJECTS) -o prog

asm.o: asm.c
	$(CXX) $(CFLAGS) asm.c -o asm.o


clean:
	-rm asm.o
