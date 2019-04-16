test: main.o
	g++ -o test main.o
	
main.o: main.cpp ndarray.hpp slice.hpp methods.hpp helperfunctions.hpp nditer.hpp BinaryOperations.hpp arithematic.hpp
	g++ -std=c++11 -pedantic -Wall -g -c main.cpp
clean:
	rm test main.o