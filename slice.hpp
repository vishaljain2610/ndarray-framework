#ifndef SLICE_H
#define SLICE_H

#include <iostream>

char rangeStr[] = "range";
char allStr[] = "all";

template<const char* typeStr> 
class Slice{
public:
	int64_t starting_index;
	int64_t stopping_index;
	int64_t step;
	const char* type;

	Slice(int64_t starting_index_, int64_t stopping_index_, int64_t step_):
	starting_index(starting_index_),
	stopping_index(stopping_index_),
	step(step_),
	type(typeStr){

	}

	Slice():
	type(typeStr){

	}

	// Slice():
	// starting_index(0),
	// stopping_index(-1),
	// step(1){
		
	// }

};


Slice<rangeStr> range(int64_t starting_index_, int64_t stopping_index_, int64_t step_){
	
	return Slice<rangeStr>(starting_index_, stopping_index_, step_);
}

Slice<allStr> all(){
	return Slice<allStr>();
}

#endif