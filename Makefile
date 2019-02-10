test: main.o
	g++ -o test main.o
	./test
main.o: main.cpp ndarray.hpp
	g++ -std=c++11 -pedantic -Wall -g -c main.cpp
clean:
	rm test main.o