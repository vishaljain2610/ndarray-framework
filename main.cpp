#include <iostream>
#include <vector>
#include <numeric>
#include <assert.h>

#include "slice.hpp"
#include "ndarray.hpp"
#include "arithematic.hpp"
#include "helperfunctions.hpp"
#include "methods.hpp"

using namespace std;

void assignment_related(){
	array<size_t,3> shape3 = {2,4,5};
	
	vector<float_t> allocated_memory3(calc_size<size_t,3>(shape3));
	auto array3d = create_array<float_t,3>(allocated_memory3.data(), shape3);
	
	for (auto element: array3d){
		cout << element << " ";	 
	}
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
void methods_related(){
	array<size_t, 3> shape3 = {2,3,4};
	vector<int> allocated_memory3(calc_size<size_t, 3>(shape3));
	auto array3d = create_array<int, 3>(allocated_memory3.data(), shape3);
	for(size_t i = 0;i<array3d.total_size;i++){	
		array3d.data_buffer.get()[i] = i-5;
	}

	auto array1d = numc::clip(array3d,3,10);

	array<size_t, 3> shape2 = {2,3,4};
	vector<int> allocated_memory2(calc_size<size_t, 3>(shape2));
	auto array2d = create_array<int, 3>(allocated_memory2.data(), shape2);

	for(auto elem : array1d){
		cout << elem << " ";
	}

	cout << " \n -- \n";
	for(auto elem : array3d){
		cout << elem << " ";
	}
}

int main()
{	
	assignment_related();
	methods_related();
	slice_related();
	return 0;
}

