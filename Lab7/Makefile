CXX=gcc
CFLAGS = -c -std=c99
FLAGS  =  -std=c99
OBJECTS = build/main.o build/lib.o

.PHONY: clean all bin build  bin/prog

all: bin build  bin/prog

bin/prog: $(OBJECTS)
	$(CXX) $(FLAGS) $(OBJECTS) -o bin/prog

build/main.o: src/main.c src/lib.h
	$(CXX) $(CFLAGS) src/main.c -o build/main.o 

build/lib.o: src/lib.c src/lib.h
	$(CXX) $(CFLAGS) src/lib.c -o build/lib.o

build:
	mkdir  build
bin:
	mkdir  bin 
clean:
	-rm -rf build bin
