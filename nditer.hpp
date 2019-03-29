#ifndef NDITER_H
#define NDITER_H

#include <vector>

using namespace std;

// https://www.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html

template<typename T, size_t N,typename = typename enable_if<is_integral<T>::value, T>::type>
vector<T> removeZeros(array<T, N>& arg) {
	//cout << "in removeZeros" << endl;
	vector<T> out;
  for (auto e: arg){
  	if (e != 0){
  		out.push_back(e);
  	}
  }
  return out;
}

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
		//cout << "in NdIter constructor" << endl;
		//cout << "iterator position! " << pos << endl;
	}

	bool operator==(NdIter<T, num_dimensions>& iter){
		//cout << "in operator==" << endl;
		return (pos == iter.pos);
	}


	bool operator!=(NdIter<T, num_dimensions>& iter){
		//cout << "in operator!=" << endl;
		//cout << "pos: " << pos << endl;
		//cout << "iter.pos: " << iter.pos << endl;
		return (pos != iter.pos);
	}

	T& operator*(){
		//cout << "in operator*" << endl;
		return *pos;
	}

	// for prefix
	NdIter<T, num_dimensions> & operator++(){
		//cout << "in operator++ prefix" << endl;
		++index;
		size_t size = index;
		size_t inc = 0;
		//cout << "index" << index << endl;
		//cout << "inc: " << inc << endl;
		//cout << "shape: " << shape << endl;
		//cout<< "size: " << size << endl;
		//cout << "strides: " << strides << endl;
		//cout << "shape.size(): " << shape.size() << endl;
		for (int64_t i=shape.size()-1; i>= 0; --i){
			auto n = size%(shape[i]);
			inc += (n*strides[i]);
			size = size/shape[i];
			//cout<< "n: " << n << endl;
			//cout<< "inc: " << inc << endl;
			//cout<< "size: " << size << endl;
		}
		if (size > 0){
			inc = shape[0]*removeZeros(strides)[0];
		}
		//cout<< "pos " << inc << endl;
		pos = data_buffer + inc;
		//cout<< "final pos " << pos << endl;
		//cout<< "final data_buffer: " << data_buffer << endl;
		//cout<< "final inc: " << inc << endl;
		return *this;
	}

	// for postfix
	NdIter<T, num_dimensions> & operator++(int){
		//cout << "in operator++ postfix" << endl;
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
			inc = shape[0]*removeZeros(strides)[0];
		}
		pos = data_buffer + inc;
		return clone;
	}

	T* operator->(){
		//cout << "in operator->" << endl;
		return pos;
	}

};

#endif