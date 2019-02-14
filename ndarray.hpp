#ifndef NDARRAY_H
#define NDARRAY_H

#include <iostream>
#include <array>
#include <algorithm>
#include <memory>
#include <cstdarg>

#include "slice.hpp"

using namespace std;

template<typename T, size_t num_dimensions> class NdarrayMetadata {

	public:
		size_t total_size;
		size_t offset_to_data_buffer;
		// https://docs.microsoft.com/en-us/cpp/cpp/how-to-create-and-use-shared-ptr-instances?view=vs-2017
		shared_ptr<T> data_buffer;
		array<size_t, num_dimensions> shape;
		array<size_t, num_dimensions> strides;

		NdarrayMetadata(size_t total_size_, size_t offset_to_data_buffer_, shared_ptr<T> data_buffer_,
		 array<size_t, num_dimensions> shape_, array<size_t, num_dimensions> strides_):
		total_size(total_size_),
		offset_to_data_buffer(offset_to_data_buffer_),
		data_buffer(data_buffer_),
		shape(shape_),
		strides(strides_){
			// cout << "-------------------------in "<< "\n";
			// cout << total_size_ << "\n";
			// cout << offset_to_data_buffer_ << "\n";
			// cout << data_buffer_ << "\n";
			// cout << shape_ << "\n";
			// cout << strides_ << "\n";
			// cout << "ending" << "\n";
		}

		NdarrayMetadata():
		total_size(0),
		offset_to_data_buffer(0),
		data_buffer(shared_ptr<T>(nullptr)),
		shape(array<size_t, num_dimensions>()),
		strides(array<size_t, num_dimensions>())
		{}

		T& operator()(size_t dimension_val...){
			auto offset_to_data_buffer=0;
			va_list args;
		    va_start(args, dimension_val);
		 	size_t strideIndex = 0;
		 	while(strideIndex<num_dimensions) {
		 		
		 		offset_to_data_buffer = offset_to_data_buffer + dimension_val*this->strides[strideIndex]; //TEMPORARY TEST

		 		// cout << "dimension_val " << dimension_val << endl;
		 		// cout << "strideIndex " << strideIndex << endl;
		 		// cout << this->strides[strideIndex] << endl;
		 		// cout << "offset_to_data_buffer " << offset_to_data_buffer << endl;

		 		strideIndex++;
		 		dimension_val = va_arg(args, int);
		 	}

		 	va_end(args);

			return this->data_buffer.get()[offset_to_data_buffer];
		}

		NdarrayMetadata<T, num_dimensions> operator()(Slice slice...){
			auto shape = this->shape;
			cout << "shape " << shape << endl;
			auto strides = this->strides;
			va_list args;
		    va_start(args, slice);
		    auto offset_to_data_buffer= this->offset_to_data_buffer + slice.starting_index*strides[0];
		 	size_t dimension_val = 0;
		 	while(dimension_val<num_dimensions) {
		 		shape[dimension_val] = slice.stopping_index-slice.starting_index;
		 		strides[dimension_val] = strides[dimension_val]*slice.step;

		 		// cout << "dimension_val " << dimension_val << endl;
		 		// cout << "shape[dimension_val] " << shape[dimension_val] << endl;
		 		// cout << slice.starting_index << " slice.starting_index" << endl;
		 		// cout << slice.stopping_index << " slice.stopping_index" << endl;

		 		dimension_val++;
		 		slice = va_arg(args, Slice);
		 	}

		 	va_end(args);

		 	//////////////////???CHANGE
		 	// auto total_size = calc_size(shape);
		 	auto total_size = this->total_size;
			return NdarrayMetadata<T, num_dimensions>(total_size, offset_to_data_buffer, 
				shared_ptr<T>(this->data_buffer, this->data_buffer.get()+offset_to_data_buffer), shape, strides);
		}

		NdarrayMetadata<T, num_dimensions-1> operator[](int dimension_val){
			// cout << "in!! " << endl;
			auto total_size = this->strides[0];
			auto offset_to_data_buffer = dimension_val*this->strides[0]; 
			
			array<size_t, num_dimensions-1> shape;
		 	array<size_t, num_dimensions-1> strides;

			for(size_t i=0; i<num_dimensions-1; i++){
	 			shape[i] = this->shape[i+1];
	 			strides[i] = this->strides[i+1];
	 		}

	 		// cout << "dimension_val " << dimension_val << endl;
	 		// cout << "shape " << shape << endl;
	 		// cout << "strides " << strides << endl;
	 		// cout << "offset_to_data_buffer " << offset_to_data_buffer << endl;

			return NdarrayMetadata<T, num_dimensions-1>(total_size, offset_to_data_buffer, 
				shared_ptr<T>(this->data_buffer, this->data_buffer.get()+offset_to_data_buffer), shape, strides);
		}

		// T calc_size(array<T, num_dimensions> a){
		// 	return std::accumulate(a.begin(), a.end(), 1, std::multiplies<T>());
		// }
};


template<typename T, size_t N>
ostream& operator<< (ostream& stream, array<T, N>arg ) {
	stream << '(';
	for (size_t i = 0; i < arg.size() ; i++){
		stream << arg[i];
		if (i < arg.size() - 1){
			stream << ", ";
		}
	}
	stream << ')';
	return stream;
}

template<typename T, size_t num_dimensions>
T calc_size(array<T, num_dimensions> a){
	return std::accumulate(a.begin(), a.end(), 1, std::multiplies<T>());
}

template<typename T, size_t num_dimensions>
array<T, num_dimensions> calc_strides(array<T, num_dimensions> a){
	array<T, num_dimensions> out;
	//initialising last stride to 1
	out.back() = 1;
	for (int64_t i=a.size()-2; i>=0 ; --i){
		out[i] = a[i+1] * out[i+1]; 
	}
	return out;
}

template<typename T>
void _initDeleter(T* pointer){
}

template<typename T>
void _deleteArray(T* pointer){
	delete[] pointer;
}

template<typename T, size_t num_dimensions>
NdarrayMetadata<T, num_dimensions> create_array(T* pointer_to_allocated_memory_, array<size_t, num_dimensions> shape_, function<void(T*)> destructor_=_initDeleter<T>) {
	// cout << "created. \n";
	return NdarrayMetadata<T,num_dimensions>(calc_size(shape_), 0, shared_ptr<T>(pointer_to_allocated_memory_, destructor_),
						shape_, calc_strides(shape_));
}

#endif