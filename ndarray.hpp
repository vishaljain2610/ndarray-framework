#ifndef NDARRAY_H
#define NDARRAY_H

#include <iostream>
#include <array>
#include <algorithm>
#include <memory>
#include <cstdarg>
#include<string.h> 

#include "slice.hpp"

using namespace std;

template<typename T, size_t num_dimensions> T calc_size(array<T, num_dimensions> a);

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
				
				offset_to_data_buffer = offset_to_data_buffer + dimension_val*this->strides[strideIndex];
				strideIndex++;
				dimension_val = va_arg(args, int);
			}

			va_end(args);

			return this->data_buffer.get()[offset_to_data_buffer];
		}

		template<const char* sliceType>
		NdarrayMetadata<T, num_dimensions> operator()(Slice<sliceType> slice...){
			auto shape = this->shape;
			auto strides = this->strides;
			va_list args, vl_count;
			va_start(args, slice);
			auto sliceCopy = slice;

			auto offset_to_data_buffer = 0;
			auto replace_ellipsis_with_alls = 0;

			size_t count = 0;
			va_copy(vl_count, args);
			while (strcmp(sliceCopy.type, "end")) {
				sliceCopy=va_arg(vl_count,Slice<sliceType>);
				++count;
			}
			va_end(vl_count);

			replace_ellipsis_with_alls = 1;
			if(count<num_dimensions){
				replace_ellipsis_with_alls = num_dimensions-count+1;
			}

			// for first dimension because offset needs to be set here
			if(!strcmp(slice.type, "range")){
				offset_to_data_buffer= this->offset_to_data_buffer + slice.starting_index*strides[0];
				shape[0] = slice.stopping_index-slice.starting_index;
				strides[0] = strides[0]*slice.step;
			} else{
				offset_to_data_buffer = this->offset_to_data_buffer;
			}

			size_t dimension_val = 1;

			if(!strcmp(slice.type, "ellipsis")){
				// because indexing from zero
				dimension_val = replace_ellipsis_with_alls;
			}
	
			while(dimension_val<num_dimensions){
				slice = va_arg(args, Slice<sliceType>);

				if(!strcmp(slice.type, "range")){
						shape[dimension_val] = slice.stopping_index-slice.starting_index;
						strides[dimension_val] = strides[dimension_val]*slice.step;
				}

				if(!strcmp(slice.type, "ellipsis")){
					dimension_val = dimension_val + replace_ellipsis_with_alls;
				}
				if(!strcmp(slice.type, "end")){
					break;
				}
				dimension_val++;
			}


			va_end(args);

			auto total_size = calc_size(shape);
			return NdarrayMetadata<T, num_dimensions>(total_size, offset_to_data_buffer, 
					shared_ptr<T>(this->data_buffer, this->data_buffer.get()+offset_to_data_buffer), shape, strides);
		}

		NdarrayMetadata<T, num_dimensions-1> operator[](int dimension_val){
			
			auto total_size = this->strides[0];
			auto offset_to_data_buffer = dimension_val*this->strides[0]; 
			
			array<size_t, num_dimensions-1> shape;
			array<size_t, num_dimensions-1> strides;

			for(size_t i=0; i<num_dimensions-1; i++){
				shape[i] = this->shape[i+1];
				strides[i] = this->strides[i+1];
			}

			return NdarrayMetadata<T, num_dimensions-1>(total_size, offset_to_data_buffer, 
					shared_ptr<T>(this->data_buffer, this->data_buffer.get()+offset_to_data_buffer), shape, strides);
		}

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

	return NdarrayMetadata<T,num_dimensions>(calc_size(shape_), 0, shared_ptr<T>(pointer_to_allocated_memory_, destructor_),
											shape_, calc_strides(shape_));
}

#endif