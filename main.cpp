#include <iostream>
#include <vector>
#include <numeric>

#include "slice.hpp"
#include "ndarray.hpp"

using namespace std;

void assignment_related(){
	array<size_t, 3> shape3 = {3, 3, 3};
	vector<int64_t> allocated_memory3(calc_size<size_t, 3>(shape3));
	auto array3d = create_array<int64_t, 3>(allocated_memory3.data(), shape3);
	array3d(2, 1, 1) = 2;
	auto array2d = array3d[2];
	auto array1d = array2d[1];
	auto array1d2 = array3d[2][1];
}

void slice_related(){
	array<size_t, 2> shape_slice = {10, 10};
	vector<int64_t> allocated_memory(calc_size<size_t, 2>(shape_slice));
	auto array1dslice = create_array<int64_t, 2>(allocated_memory.data(), shape_slice);
	// cout << array1dslice.shape << endl;
	// cout << array1dslice.strides << endl;
	array1dslice(0, 2) = 100;
	auto newarray = array1dslice(range(0, 5, 2), all());
	// cout << newarray.shape << endl;
	// cout << newarray.strides << endl;
}

int main()
{	
	assignment_related();
	slice_related();
    return 0;
}

