CXX=gcc
CFLAGS = -c -Wall -Werror -std=c99
FLAGS  =  -Wall -Werror -std=c99
OBJECTS = build/main.o build/lib.o build/lib3.o build/lib4.o

.PHONY: clean all bin build  bin/prog

all: bin build  bin/prog

bin/prog: $(OBJECTS)
	$(CXX) $(FLAGS) $(OBJECTS) -o bin/prog

build/main.o: src/main.c src/lib.h src/lib3.h
	$(CXX) $(CFLAGS) src/main.c -o build/main.o 

build/lib.o: src/lib.c src/lib.h
	$(CXX) $(CFLAGS) src/lib.c -o build/lib.o

build/lib3.o: src/lib3.c src/lib3.h
	$(CXX) $(CFLAGS) src/lib3.c -o build/lib3.o

build/lib4.o: src/lib4.c src/lib4.h
	$(CXX) $(CFLAGS) src/lib4.c -o build/lib4.o

build:
	mkdir  build
bin:
	mkdir  bin 
clean:
	-rm -rf build bin
