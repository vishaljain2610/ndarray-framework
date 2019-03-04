#ifndef ARITHEMATIC_H
#define ARITHEMATIC_H

#include <iostream>
#include <array>
#include <algorithm>
#include <memory>
#include <cstdarg>
#include<string.h> 

#include "ndarray.hpp"
#include "slice.hpp"

using namespace std;

template<typename T, size_t num_dimensions> 
NdarrayMetadata<T, num_dimensions> add(NdarrayMetadata<T, num_dimensions> array1,NdarrayMetadata<T, num_dimensions> array2){
    
	array<size_t, num_dimensions> out_shape = array1.shape;
	vector<int64_t> output_allocated_memory(calc_size<size_t, num_dimensions>(out_shape));
	auto output = create_array<int64_t, num_dimensions>(output_allocated_memory.data(), out_shape);    

	auto ite_output = output.data_buffer.get();
	auto ite_array1 = array1.data_buffer.get();
	auto ite_array2 = array2.data_buffer.get();
	
	for(unsigned int i = 0; i< array1.total_size; i++){
		
		ite_output[i] = ite_array1[i] + ite_array2[i];
		cout << ite_output[i] <<  " " << i << endl; 
	}

	return output;
}

template<typename T, size_t num_dimensions> 
NdarrayMetadata<T, num_dimensions> subtract(NdarrayMetadata<T, num_dimensions> array1,NdarrayMetadata<T, num_dimensions> array2){
    
	array<size_t, num_dimensions> out_shape = array1.shape;
	vector<int64_t> output_allocated_memory(calc_size<size_t, num_dimensions>(out_shape));
	auto output = create_array<int64_t, num_dimensions>(output_allocated_memory.data(), out_shape);    

	auto ite_output = output.data_buffer.get();
	auto ite_array1 = array1.data_buffer.get();
	auto ite_array2 = array2.data_buffer.get();
	
	// auto output = array1;
	for(unsigned int i = 0; i< array1.total_size; i++){
		
		ite_output[i] = ite_array1[i] - ite_array2[i];
		cout << ite_output[i] <<  " " << i << endl; 
	}

	return output;
}

template<typename T, size_t num_dimensions> 
NdarrayMetadata<T, num_dimensions> multiplie(NdarrayMetadata<T, num_dimensions> array1,NdarrayMetadata<T, num_dimensions> array2){
    
	array<size_t, num_dimensions> out_shape = array1.shape;
	vector<int64_t> output_allocated_memory(calc_size<size_t, num_dimensions>(out_shape));
	auto output = create_array<int64_t, num_dimensions>(output_allocated_memory.data(), out_shape);    

	auto ite_output = output.data_buffer.get();
	auto ite_array1 = array1.data_buffer.get();
	auto ite_array2 = array2.data_buffer.get();
	
	// auto output = array1;
	for(unsigned int i = 0; i< array1.total_size; i++){
		
		ite_output[i] = ite_array1[i] * ite_array2[i];
		cout << ite_output[i] <<  " " << i << endl; 
	}

	return output;
}


#endif 