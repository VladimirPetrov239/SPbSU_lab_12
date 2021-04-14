.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++11 -Wall -pedantic

all: lab_12

bin:
	mkdir -p bin

lab_12: src/main.cpp bin/matrix.o include/*.h bin
	$(CXX) $(CXXFLAGS) -o $@ -Iinclude $< bin/*

bin/%.o: src/%.cpp include/*.h bin
	$(CXX) $(CXXFLAGS) -c -o $@ -Iinclude $<

clean:
	rm -rf bin lab_12
