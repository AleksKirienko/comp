CXX=gcc
CFLAGS = -c -Wall 
FLAGS  =  -Wall 
OBJECTS = asm.o

.PHONY: clean all sat

all: sat

sat: $(OBJECTS)
	$(CXX) $(FLAGS) $(OBJECTS) -o sat

asm.o: asm.c
	$(CXX) $(CFLAGS) asm.c -o asm.o

clean:
	-rm -rf
