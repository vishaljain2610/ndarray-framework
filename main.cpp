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
	
	vector<int> allocated_memory3(calc_size<size_t,3>(shape3));
	auto array3d = create_array<int,3>(allocated_memory3.data(), shape3);
	
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
	
	array<size_t,1> shape1x = {6};

	vector<double> allocated_memoryX(calc_size<size_t,1>(shape1x));
	auto x = create_array<double,1>(allocated_memoryX.data(), shape1x);

	vector<double> allocated_memoryY(calc_size<size_t,1>(shape1x));
	auto y = create_array<double,1>(allocated_memoryY.data(), shape1x);
	
	vector<double> allocated_memoryYX(calc_size<size_t,1>(shape1x));
	auto YX = create_array<double,1>(allocated_memoryYX.data(), shape1x);
	
	vector<double> allocated_memoryXX(calc_size<size_t,1>(shape1x));
	auto XX = create_array<double,1>(allocated_memoryXX.data(), shape1x);

	array<double,10> filler= {1, 3, 2, 5, 7, 8, 8, 9, 10, 12}; 
	
	array<double,6> fillerY= {99, 65, 79, 75, 87, 81};
	array<double,6> fillerX= {43, 21, 25, 42, 57, 59}; 
	for(size_t i =0;i<x.total_size;i++) {
		y(i) = fillerY[i];
		x(i) = fillerX[i];
	}
 
	auto m_x = x.mean();
	auto m_y = y.mean();	
	numc::multiply(&y,&x,&YX);
	numc::square(&x,&XX);
	double SS_xx = x.var();
	double SS_yx = YX.sum() - (x.total_size*m_y*m_x);

	auto b_1 = SS_yx / SS_xx ;
    auto b_0 = m_y - b_1*m_x ;	

	cout << "Equation of best fitting line\n";
	cout << "y = " << b_0 << " + " << b_1 << "x\n";


	cout<< "\n\n\n\nAxis Testing\n";
	array<size_t,2> shape4 = {3,3};
	
	vector<int> allocated_memory(calc_size<size_t,2>(shape4));
	auto array3_1d = create_array<int,2>(allocated_memory.data(), shape4);
	auto re = create_array<int,1>(removeArrayElement(shape4,1));
	
	array3_1d(0,0) = 5;array3_1d(0,1) = 4;array3_1d(0,2) = 3;
	array3_1d(1,0) = 4;array3_1d(1,1) = 3;array3_1d(1,2) = 2;
	array3_1d(2,0) = 3;array3_1d(2,1) = 2;array3_1d(2,2) = 1;

	numc::sum(&array3_1d,&re,0);
	for(auto elem : re)
		cout << elem << " ";
	cout <<"\n\n";

}


int main()
{	
	methods_related();
	return 0;
}



