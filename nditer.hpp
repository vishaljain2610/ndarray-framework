#ifndef NDITER_H
#define NDITER_H

#include <vector>

using namespace std;

// https://www.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html

// define the iterator
 
template <typename T, size_t num_dimensions>
class NdIter {

private:
	T* data_buffer; // the container itself, to give the iterator access to the container
	T* pos; // something that indicates where the iterator is pointing
	size_t index; 
	array<size_t, num_dimensions> shape;
	array<size_t, num_dimensions> strides;

public: 

	NdIter(T* data_buffer_, array<size_t, num_dimensions> shape_, array<size_t, num_dimensions> strides_):
		data_buffer(data_buffer_), pos(&data_buffer_[0]), index(0), shape(shape_), strides(strides_){
	}

	bool operator==(NdIter<T, num_dimensions>& iter){
		return (pos == iter.pos);
	}

	bool operator!=(NdIter<T, num_dimensions>& iter){
		return (pos != iter.pos);
	}

	T& operator*(){
		return *pos;
	}

	// for prefix
	NdIter<T, num_dimensions> & operator++(){
		++index;
		size_t size = index;
		size_t inc = 0;
		for (int64_t i=shape.size()-1; i>= 0; --i){
			auto n = size%(shape[i]);
			inc += (n*strides[i]);
			size = size/shape[i];
		}
		if (size > 0){
			inc = shape[0]*strides[0];
		}
		pos = data_buffer + inc;
		return *this;
	}

	// for postfix
	NdIter<T, num_dimensions> & operator++(int){
		NdIter<T, num_dimensions> clone(*this);
		++index;
		size_t size = index;
		size_t inc = 0;
		for (int64_t i=shape.size()-1; i>= 0; --i){
			auto n = size%(shape[i]);
			inc += (n*strides[i]);
			size = size/shape[i];
		}
		if (size > 0){
			inc = shape[0]*strides[0];
		}
		pos = data_buffer + inc;
		return clone;
	}

	T* operator->(){
		return pos;
	}

};

#endif