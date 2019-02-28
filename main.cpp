#include <iostream>
#include <vector>
#include <numeric>
#include <assert.h>

#include "slice.hpp"
#include "ndarray.hpp"

using namespace std;

void assignment_related(){
	array<size_t, 3> shape3 = {3, 3, 3};
	vector<int64_t> allocated_memory3(calc_size<size_t, 3>(shape3));
	auto array3d = create_array<int64_t, 3>(allocated_memory3.data(), shape3);
	array3d(2, 1, 1) = 2;
	for (auto element: array3d){
		if(element == 2){
			cout << "yay" << endl;
		} 
	}
	auto array2d = array3d[2];
	auto array1d = array2d[1];
	auto array1d2 = array3d[2][1];
}

void slice_related(){
	array<size_t, 2> shape_slice = {10, 10};
	vector<int64_t> allocated_memory(calc_size<size_t, 2>(shape_slice));
	auto array1dslice = create_array<int64_t, 2>(allocated_memory.data(), shape_slice);
	array1dslice(0, 2) = 100;
	
	array<size_t, 3> shape3 = {10, 10, 10};
	vector<int64_t> allocated_memory3(calc_size<size_t, 3>(shape3));
	auto array3d = create_array<int64_t, 3>(allocated_memory3.data(), shape3);

	auto slicee = array3d(range(0, 5, 2), ellipsis(), end());
	slicee = array3d(ellipsis(), all(), range(0, 5, 2), end());
	slicee(ellipsis()) = 7;
	// checking iterator
	for (auto element: slicee){
		assert(element == 7);
	}
}

int main()
{	
	assignment_related();
	slice_related();
	return 0;
}

