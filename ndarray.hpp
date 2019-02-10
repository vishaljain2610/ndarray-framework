#ifndef NDARRAY_H
#define NDARRAY_H

#include <iostream>
#include <array>
#include <algorithm>
#include <memory>
#include <cstdarg>

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
		strides(strides_)
		{}

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
};


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
	cout << "created. \n";
	return NdarrayMetadata<T,num_dimensions>(calc_size(shape_), 0, shared_ptr<T>(pointer_to_allocated_memory_, destructor_),
						shape_, calc_strides(shape_));
}

#endif