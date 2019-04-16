#include <iostream>
#include <vector>
#include <numeric>
#include <assert.h>

#include "slice.hpp"
#include "ndarray.hpp"
#include "arithematic.hpp"
#include "helperfunctions.hpp"
#include "BinaryOperations.hpp"
#include "LogicFunctions.hpp"
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
	
	array<size_t,1> shape1x = {10};
	array<size_t,1> shape1y = {10};
	// array<size_t,2> shape1xy = {10,2};


	vector<int> allocated_memoryX(calc_size<size_t,1>(shape1x));
	auto x = create_array<int,1>(allocated_memoryX.data(), shape1x);

	// vector<int> allocated_memoryXY(calc_size<size_t,2>(shape1xy));
	// auto x = create_array<int,2>(allocated_memoryX.data(), shape1xy);

	vector<int> allocated_memoryY(calc_size<size_t,1>(shape1y));
	auto y = create_array<int,1>(allocated_memoryY.data(), shape1y);

	for(size_t i =0;i<x.total_size;i++)
		x(i) = 2*(i+1);

	y(0) = 1;
	y(1) = 3;
	y(2) = 2;
	y(3) = 5;
	y(4) = 7;
	y(5) = 8;
	y(6) = 8;
	y(7) = 9;
	y(8) = 10;
	y(9) = 12;

	auto sumYX = numc::sum(numc::multiplie(y,x));
	auto sumXX = numc::sum(numc::multiplie(x,x));

	double m_x = numc::mean(x);
	double m_y = numc::mean(y);

	auto SS_xy = sumYX - x.total_size*m_y*m_x;
	auto SS_xx = sumXX - x.total_size*m_x*m_x;
	
	auto b_1 = SS_xy / SS_xx ;
    auto b_0 = m_y - b_1*m_x ;

		// for(auto elem: x)
		// 	cout << elem << " ";

}

int main()
{	
	// assignment_related();
	methods_related();
	// slice_related();
	return 0;
}

