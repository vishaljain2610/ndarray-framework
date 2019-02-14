#ifndef SLICE_H
#define SLICE_H

#include <iostream>

class All{

};

class Ellipsis{
	
};

class Slice {
public:
	int64_t starting_index;
	int64_t stopping_index;
	int64_t step;

	Slice(int64_t starting_index_, int64_t stopping_index_, int64_t step_):
	starting_index(starting_index_),
	stopping_index(stopping_index_),
	step(step_){

	}

	Slice():
	starting_index(0),
	stopping_index(-1),
	step(1){
		
	}

};

#endif