CXX=gcc
CFLAGS = -c -Wall -std=c99
FLAGS  =  -Wall -std=c99
OBJECTS = build/asm.o

.PHONY: clean all bin build  bin/prog

all: bin build  bin/prog

bin/prog: $(OBJECTS)
	$(CXX) $(FLAGS) $(OBJECTS) -o bin/prog

build/asm.o: src/asm.c
	$(CXX) $(CFLAGS) src/asm.c -o build/asm.o

build:
	mkdir  build
bin:
	mkdir  bin

clean:
	-rm -rf build bin
