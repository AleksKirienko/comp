CXX=gcc
CFLAGS = -c -Wall 
FLAGS  =  -Wall 
OBJECTS = build/main.o build/lib.o build/lib3.o build/lib4.o build/lib5.o build/cu.o

.PHONY: clean all bin build  bin/prog

all: bin build  bin/prog

bin/prog: $(OBJECTS)
	$(CXX) $(FLAGS) $(OBJECTS) -o bin/prog

build/main.o: src/main.c src/lib.h src/lib3.h src/lib4.h src/lib5.h src/cu.h
	$(CXX) $(CFLAGS) src/main.c -o build/main.o 

build/lib.o: src/lib.c src/lib.h
	$(CXX) $(CFLAGS) src/lib.c -o build/lib.o

build/lib3.o: src/lib3.c src/lib3.h
	$(CXX) $(CFLAGS) src/lib3.c -o build/lib3.o

build/lib4.o: src/lib4.c src/lib4.h
	$(CXX) $(CFLAGS) src/lib4.c -o build/lib4.o

build/lib5.o: src/myReadkey.c src/lib5.h
	$(CXX) $(CFLAGS) src/myReadkey.c -o build/lib5.o

build/cu.o: src/cu.c src/cu.h
	$(CXX) $(CFLAGS) src/cu.c -o build/cu.o

build:
	mkdir  build
bin:
	mkdir  bin 
clean:
	-rm -rf build bin
