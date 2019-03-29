#ifndef NDARRAY_H
#define NDARRAY_H

#include <iostream>
#include <array>
#include <algorithm>
#include <memory>
#include <cstdarg>
#include<string.h> 

#include "slice.hpp"
#include "nditer.hpp"
#include "exceptions.hpp"

using namespace std;

template<typename T, size_t num_dimensions> T calc_size(array<T, num_dimensions> a);

template<typename T, size_t num_dimensions> array<T, num_dimensions> calc_strides(array<T, num_dimensions> a);

template<typename T> void _initDeleter(T* pointer);

template<typename T> void _deleteArray(T* pointer);

template<typename T, size_t num_dimensions> class NdarrayMetadata {

	public:

		// for iterator
		typedef NdIter<T, num_dimensions> iterator;

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
			cout<<"\n" << "-------------------------in "<< "\n";
			cout << total_size_ << "\n";
			cout << offset_to_data_buffer_ << "\n";
			cout << data_buffer_ << "\n";
			cout << shape_ << "\n";
			cout << strides_ << "\n";
			cout << "----------------ending" << "\n";
		}

		NdarrayMetadata(array<size_t, num_dimensions> shape_):
		total_size(0),
		offset_to_data_buffer(0),
		shape(shape_),
		strides(array<size_t, num_dimensions>()){
			vector<T> allocated_memory3(calc_size<size_t, num_dimensions>(shape_));
			auto destructor_=_initDeleter<T>;
			auto pointer_to_allocated_memory_ = allocated_memory3.data();
			
			this->strides = calc_strides(shape_);
			this->total_size = calc_size(shape_);
			data_buffer =  shared_ptr<T>(pointer_to_allocated_memory_, destructor_);
			
			cout << "-------------------------in "<< "\n";
			cout << total_size << "\n";
			cout << offset_to_data_buffer << "\n";
			cout << data_buffer << "\n";
			cout << shape << "\n";
			cout << strides << "\n";
			cout << "----------------ending" << "\n";
		}



		NdarrayMetadata():
		total_size(0),
		offset_to_data_buffer(0),
		data_buffer(shared_ptr<T>(nullptr)),
		shape(array<size_t, num_dimensions>()),
		strides(array<size_t, num_dimensions>())
		{}

		T& operator ()(size_t dimension_val...){
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
			// cout << this->data_buffer; 
			return this->data_buffer.get()[offset_to_data_buffer];
		}

		NdarrayMetadata<T, num_dimensions> operator()(Slice<ellipsisStr> slice){
			return NdarrayMetadata<T,num_dimensions>(*this);
		}

		template<const char* sliceType>
		NdarrayMetadata<T, num_dimensions> operator()(Slice<sliceType> slice...){
			auto shape = this->shape;
			cout << "shape " << shape << endl;
			auto strides = this->strides;
			va_list args;
		    va_start(args, slice);
		    auto offset_to_data_buffer = 0;

		    // for first dimension because offset needs to be set here
		    if(!strcmp(slice.type, "range")){
		    	cout << "range" << endl;
		    	offset_to_data_buffer= this->offset_to_data_buffer + slice.starting_index*strides[0];
	    		shape[0] = slice.stopping_index-slice.starting_index;
	 			strides[0] = strides[0]*slice.step;
	    	}
		    if(!strcmp(slice.type, "all")){
		    	cout << "all" << endl;
		    	offset_to_data_buffer = this->offset_to_data_buffer;
		    }
		
		    size_t dimension_val = 1;
		    while(dimension_val<num_dimensions){
		    	slice = va_arg(args, Slice<sliceType>);

		    	if(!strcmp(slice.type, "range")){
			    	cout << "range" << endl;
			    	shape[dimension_val] = slice.stopping_index-slice.starting_index;
			 		strides[dimension_val] = strides[dimension_val]*slice.step;
		    	}
			    // if(!strcmp(slice.type, "all")){
			    // 	cout << "all" << endl;
			    	
			    // }
			    // slice = va_arg(args, Slice<sliceType>);
			    dimension_val++;
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

		iterator begin(){
			return iterator(&data_buffer.get()[0], shape, strides);
		}

		iterator end(){
			// cout << "THIS IS THE END" << shape[0]*removeZeros(strides)[0] << endl;
			// cout << "removeZeros" << removeZeros(strides)[0] << endl;
			// cout << "shape[0]*" << shape[0] << endl;
			return iterator(&data_buffer.get()[shape[0]*removeZeros(strides)[0]], shape, strides);
		}

		iterator begin() const {
			return iterator(&data_buffer.get()[0], shape, strides);
		}

		iterator end() const {
			// cout << "THIS IS THE END" << shape[0]*removeZeros(strides)[0] << endl;
			return iterator(&data_buffer.get()[shape[0]*removeZeros(strides)[0]], shape, strides);
		}

		NdarrayMetadata<T, num_dimensions>& operator=(T& other){
			fill(this->begin(), this->end(), other);
			return *this;
		}

		NdarrayMetadata<T, num_dimensions>& operator=(const T& other){
			fill(this->begin(), this->end(), other);
			return *this;
		}

		template<size_t M>
		NdarrayMetadata<T, M> broadcastTo(const array<size_t, M> newshape) const {
			cout << "in ndarray broadcastTo " << "\n";
			array<size_t, M> newstrides;
			std::fill(newstrides.begin(), newstrides.end(), 0);
		 	cout << "newstrides: " << newstrides << endl;
			auto extra_dimensions = newshape.size() - shape.size();
			for (int64_t i=shape.size()-1; i>=0; --i){
				if (newshape[i+extra_dimensions] == shape[i]){
					newstrides[i+extra_dimensions] = strides[i];
				} else if (shape[i] != 1){
					throw ValueError();
				}
			}
			cout << "newstrides: " << newstrides << endl;
			cout << "newshape: " << newshape << endl;
			return NdarrayMetadata<T, M>(calc_size(newshape), this->offset_to_data_buffer, this->data_buffer, newshape, newstrides);
		}




	// Methods 
    bool all(){
			// bool output = std::all_of(begin(),end(), [](T elem) {return (elem == 0 || elem == false); });
			auto iter = data_buffer.get();
			for(size_t i =0;i<total_size;i++){
				cout << iter[i] << " ";
				if(!iter[i])
					return false;
			}
			return true;
    }

    bool any(){
			auto iter = data_buffer.get();
			for(size_t i =0;i<total_size;i++){
				cout << iter[i]+1 << " ";
				if((iter[i]+1))
					return true;
			}
			return false;
    }

    T argmax(){

        auto output = 0;
        auto input_iter = this->data_buffer.get();
        for(size_t i = 0;i<this->total_size;i++){
            if(output < input_iter[i])
                output = i;
        }

        return output;
    }
		
    T argmin(){

        auto output = 0;
        auto input_iter = this->data_buffer.get();
        for(size_t i = 0;i<this->total_size;i++){
            if(output > input_iter[i])
                output = i;
        }

        return output;
    }

		NdarrayMetadata<T, num_dimensions> byteswap(){
        auto iter_input = this->data_buffer.get();    
        
        auto output = NdarrayMetadata<T, num_dimensions>(this->shape);    
        auto iter_output = output.data_buffer.get();
        
        for (size_t i =0; i<this->total_size;i++){
            iter_output[i] = __builtin_bswap64 (iter_input[i]);
        }
        return output;
    }

		NdarrayMetadata<T, num_dimensions> clip(int64_t min,int64_t max){    

        auto output = NdarrayMetadata<T, num_dimensions>(this->shape);
				auto iter_output = output.data_buffer.get();

        for(size_t i=0;i<this->total_size;i++){
            if(iter_output[i] < min)
                iter_output[i] = min;
            if(iter_output[i] > max)
                iter_output[i] = max;
        }   
        return output;
    }

		bool contains(int64_t value){

			for(size_t i =0;i< this->total_size;i++){
				if(this->data_buffer.get()[i] == value)
						return true;
			}
			return false;
		}

		NdarrayMetadata<T, num_dimensions> cumprod(){
			
        auto output = NdarrayMetadata<T, num_dimensions>(this->shape);
				
				auto out_iter = output.data_buffer.get();
				out_iter[0] = this->data_buffer.get()[0];
				for(size_t i = 0;i<this->total_size;i++)
					out_iter[i] = out_iter[i-1]*this->data_buffer.get()[i];
				
				return output;
		}

		NdarrayMetadata<T, num_dimensions> cumsum(){
			
        auto output = NdarrayMetadata<T, num_dimensions>(this->shape);
				
				auto out_iter = output.data_buffer.get();
				out_iter[0] = this->data_buffer.get()[0];
				for(size_t i = 0;i<this->total_size;i++)
					out_iter[i] = out_iter[i-1]+this->data_buffer.get()[i];
				
				return output;
		}
		
		void dumb(string filename){

		}

		bool isempty() const {
				return (this->total_size == 0);
		}


		void fill_array(T inFillValue) {
				std::fill(this->begin(), this->end(), inFillValue);
		}

		T item() const
		{
				if (this->total_size == 1)
				{
						return this->data_buffer.get()[0];
				}
				else
				{
						throw SizeError();
				}
		}

		void itemset(array<size_t, num_dimensions> indices,T input){
				
				auto offset_to_data_buffer = 0;
				size_t strideIndex = 0;
				while(strideIndex<num_dimensions) {
					offset_to_data_buffer = offset_to_data_buffer + indices[strideIndex]*this->strides[strideIndex];
					strideIndex++;
				}
				cout << offset_to_data_buffer << endl;
				this->data_buffer.get()[offset_to_data_buffer] = input;
		}

		T max(){
        T output = 0;
        auto input_iter = this->data_buffer.get();
        for(size_t i = 0;i<this->total_size;i++){
            if(output < input_iter[i])
                output = input_iter[i];
        }
				return output;
		}

		T min(){
        T output = 0;
        auto input_iter = this->data_buffer.get();
        for(size_t i = 0;i<this->total_size;i++){
            if(output > input_iter[i])
                output = input_iter[i];
        }
				return output;
		}

		double mean(){

        double output = static_cast<double>(std::accumulate(this->begin(), this->end(), 0.0));;
				return output/static_cast<double>(this->total_size);
		}

		double median(){

				auto list = NdarrayMetadata<T, num_dimensions>(this->shape);
        std::nth_element(this->begin(), this->begin()+ (this->total_size)/2, this->end());

				return list.data_buffer.get()[(this->total_size)/2];
		}

		size_t nbytes() {
			return static_cast<size_t>(sizeof(T) * this->total_size);
		}

		NdarrayMetadata<T, 1> nonzero(){
			static_assert(std::numeric_limits<T>::is_integer, "ERROR: &Operator: can only use with integer types.");

			array<size_t, 1> shape = { this->total_size };
			auto output = NdarrayMetadata<T,1>(shape);
			
			for(size_t i =0,j=0;i<this->total_size;i++){
				if(this->data_buffer.get()[i] != static_cast<T>(0))
					output.data_buffer.get()[j++] = i;
			}
			return output;
		}

		void ones(){
			this->fill_array(1);
		}

		void partition(size_t k){
			if(k > this->total_size){
				throw ArrayOutOfBounds();
			}
			std::nth_element(this->begin(), this->begin() + k, this->end());
			return;
		}

		NdarrayMetadata<T, num_dimensions> prod(){
			
        auto output = NdarrayMetadata<T, num_dimensions>(this->shape);
				
				auto out = this->data_buffer.get()[0];
				for(size_t i = 0;i<this->total_size;i++)
					out*=this->data_buffer.get()[i];
				
				output.data_buffer.get()[0] = out;
				return output;
		}

		NdarrayMetadata<T, num_dimensions> ptp(){
			
        auto output = NdarrayMetadata<T, num_dimensions>(this->shape);
				
				const std::pair<const T*, const T*> result = std::minmax_element(this->begin(), this->end());

				output.data_buffer.get()[0] = *result.second - *result.first;
				return output;
		}

		void put (size_t index,T input){
			this->data_buffer.get()[index] = input;
		}

		void put (NdarrayMetadata<size_t,1> index,T input){
			for(auto elem : index)
				this->put(this->data_buffer.get()[elem],input);	
		}

		void put (NdarrayMetadata<size_t,1> index,NdarrayMetadata<size_t,1> input){

			if (index.total_size != input.total_size)
        throw UnequalSizeError();
      auto index_iter = index.data_buffer.get();
			for(auto i = 0;i<input.total_size;i++)
					this->put(this->data_buffer.get()[index_iter[i]], input.data_buffer.get()[i]);
		}

		template<size_t new_num_dimensions>
		NdarrayMetadata<T, new_num_dimensions> reshape(array<size_t ,new_num_dimensions> NewShape){
			auto new_dim = calc_size(NewShape);
			if(this->total_size != new_dim)
					throw UnequalSizeError();
			
			cout << "Reshape \n";
			auto output = NdarrayMetadata<T, new_num_dimensions>(NewShape);
			 
			auto output_iter = output.data_buffer.get();
			auto this_iter = this->data_buffer.get();
			for(size_t i =0;i<output.total_size;i++){
				output_iter[i] = this_iter[i];
			}

			return output;
		}

		template<size_t new_num_dimensions>
		void resize(array<size_t ,new_num_dimensions> NewShape){
			auto new_dim = calc_size(NewShape);
			if(this->total_size != new_dim)
					throw UnequalSizeError();
			
		}

		NdarrayMetadata<T, 1> ravel(){
			array<size_t, 1> shape = {this->total_size};
			auto output = NdarrayMetadata(shape);
			auto iter_input = this->data_buffer.get();
			auto iter_output = output.data_buffer.get();

			for (size_t i=0;i<this->total_size;i++)
					iter_output[i] = iter_input[i] ;

			return output;
		}

		template <size_t M>
		array<size_t,M> searchsorted(array<T,M> Elems, string Side = "left"){
			if(num_dimensions != 1)
				throw DimensionError();
			array<size_t,M> indices;
			cout << Elems << endl;
			auto iter = this->data_buffer.get();
			size_t j=0;
			std::transform(Side.begin(), Side.end(), Side.begin(), ::tolower);
			for(size_t i =0;i< this->total_size;i++)
			{
					if(iter[i] >= Elems[j]){
						if(Side == "left")
							indices[j] = i;
						else if(Side == "right")
							indices[j] = i+1;
						else 
							throw invalid_argument("Invalid Side");
						j++;
					}
			}
			if(j<M){
				for(size_t i =j;i<M;i++)
					indices[j] = this->total_size+1;
			}
			return indices;
		}

		// template<typename TOut>
		// NdarrayMetadata<TOut,num_dimensions> astype(typename TOut) {
		// 	auto returnArray =  NdarrayMetadata<TOut,num_dimensions>(this->shape);
		// 	for(size_t i =0;i<this->total_size;i++)
		// 		returnArray.data_buffer.get()[i] =  static_cast<TOut>(this->data_buffer.get()[i])
		// 	return std::move(returnArray);

		// }	

		NdarrayMetadata<T,num_dimensions>& operator&=(NdarrayMetadata<T,num_dimensions> input){
			static_assert(std::numeric_limits<T>::is_integer, "ERROR: &Operator: can only use with integer types.");

			if(this->shape != input.shape){
				throw UnequalShapeError();
			}

			std::transform(begin(), end(), input.begin(),begin(), std::bit_and<T>());
			return *this;
		}

		NdarrayMetadata<T,num_dimensions>& operator&=(T input){
			static_assert(std::numeric_limits<T>::is_integer, "ERROR: &Operator: can only use with integer types.");

			std::for_each(begin(), end(), [=](T& value) noexcept -> T { return value &= input; });
			return *this;
		}

		NdarrayMetadata<T,num_dimensions>& operator&(T input){
			return (*this &= input);
		}

		NdarrayMetadata<T,num_dimensions>& operator&(NdarrayMetadata<T,num_dimensions> input){
			return (*this &= input);
		}



		NdarrayMetadata<T,num_dimensions>& operator|=(NdarrayMetadata<T,num_dimensions> input){
			static_assert(std::numeric_limits<T>::is_integer, "ERROR: | Operator: can only use with integer types.");

			if(this->shape != input.shape){
				throw UnequalShapeError();
			}

			std::transform(begin(), end(), input.begin(),begin(), std::bit_or<T>());
			return *this;
		}

		NdarrayMetadata<T,num_dimensions>& operator|=(T input){
			static_assert(std::numeric_limits<T>::is_integer, "ERROR: | Operator: can only use with integer types.");

			std::for_each(begin(), end(), [=](T& value) noexcept -> T { return value |= input; });
			return *this;
		}

		NdarrayMetadata<T,num_dimensions>& operator|(T input){
			return (*this |= input);
		}

		NdarrayMetadata<T,num_dimensions>& operator|(NdarrayMetadata<T,num_dimensions> input){
			return (*this |= input);
		}



		NdarrayMetadata<T,num_dimensions>& operator^=(NdarrayMetadata<T,num_dimensions> input){
			static_assert(std::numeric_limits<T>::is_integer, "ERROR: ^ Operator: can only use with integer types.");

			if(this->shape != input.shape){
				throw UnequalShapeError();
			}

			std::transform(begin(), end(), input.begin(),begin(), std::bit_xor<T>());
			return *this;
		}

		NdarrayMetadata<T,num_dimensions>& operator^=(T input){
			static_assert(std::numeric_limits<T>::is_integer, "ERROR: ^ Operator: can only use with integer types.");

			std::for_each(begin(), end(), [=](T& value) noexcept -> T { return value ^= input; });
			return *this;
		}

		NdarrayMetadata<T,num_dimensions>& operator^(T input){
			return (*this ^= input);
		}

		NdarrayMetadata<T,num_dimensions>& operator^(NdarrayMetadata<T,num_dimensions> input){
			return (*this ^= input);
		}


		NdarrayMetadata<T,num_dimensions>& operator~(){
			static_assert(std::numeric_limits<T>::is_integer, "ERROR: ~ Operator: can only use with integer types.");
			std::transform(begin(), end(), begin(), [](T value) noexcept -> T { return ~value; });
			return *this;
		}



		NdarrayMetadata<T,num_dimensions> operator<(T inValue) {
			
			auto returnArray =  NdarrayMetadata<T,num_dimensions>(this->shape);
			std::transform(begin(), end(), returnArray.begin(),
					[inValue](T value) noexcept -> T { return value < inValue; });
			return std::move(returnArray);
		}

		NdarrayMetadata<T,num_dimensions> operator<=(T inValue) {
			
			auto returnArray =  NdarrayMetadata<T,num_dimensions>(this->shape);
			std::transform(begin(), end(), returnArray.begin(),
					[inValue](T value) noexcept -> T { return value <= inValue; });
			return std::move(returnArray);
		}

		NdarrayMetadata<T,num_dimensions>& operator<(NdarrayMetadata<T,num_dimensions> input){

			if(this->shape != input.shape){
				throw UnequalShapeError();
			}

			std::transform(begin(), end(), input.begin(),begin(), std::less<T>());
			return *this;
		}

		NdarrayMetadata<T,num_dimensions>& operator<=(NdarrayMetadata<T,num_dimensions> input){

			if(this->shape != input.shape){
				throw UnequalShapeError();
			}

			std::transform(begin(), end(), input.begin(),begin(), std::less_equal<T>());
			return *this;
		}



		NdarrayMetadata<T,num_dimensions> operator>(T inValue) {
			
			auto returnArray =  NdarrayMetadata<T,num_dimensions>(this->shape);
			std::transform(begin(), end(), returnArray.begin(),
					[inValue](T value) noexcept -> T { return value > inValue; });
			return std::move(returnArray);
		}

		NdarrayMetadata<T,num_dimensions> operator>=(T inValue) {
			
			auto returnArray =  NdarrayMetadata<T,num_dimensions>(this->shape);
			std::transform(begin(), end(), returnArray.begin(),
					[inValue](T value) noexcept -> T { return value >= inValue; });
			return std::move(returnArray);
		}

		NdarrayMetadata<T,num_dimensions>& operator>(NdarrayMetadata<T,num_dimensions> input){

			if(this->shape != input.shape){
				throw UnequalShapeError();
			}

			std::transform(begin(), end(), input.begin(),begin(), std::greater<T>());
			return *this;
		}

		NdarrayMetadata<T,num_dimensions>& operator>=(NdarrayMetadata<T,num_dimensions> input){

			if(this->shape != input.shape){
				throw UnequalShapeError();
			}

			std::transform(begin(), end(), input.begin(),begin(), std::greater_equal<T>());
			return *this;
		}
};


template<typename T, size_t N>
ostream& operator << (ostream& stream, array<T, N>arg ) {
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

// template<typename T, size_t N>
// void printArr (NdarrayMetadata<T, N> arg ) {
// 	cout << '[';
// 	auto stride = arg.strides;
// 	for(size_t dim = 0; dim < N; dim++){
// 		cout << dim << endl;
// 		cout << '[';
// 		// for (size_t i = dim; i < arg.total_size; i+stride[dim]){
// 		cout  << arg(dim);
// 		// 	cout  << ", ";
// 		// }
// 		cout  << " ]";
// 	}
// 	cout  << ']';
// }

// template<typename T, size_t N>
// ostream& operator<< (ostream& stream, NdarrayMetadata<T, N> arg ) {
// 	stream << '[';
// 	auto stride = arg.strides;
// 	for(size_t dim = 0; dim < N; dim++){
// 		cout << dim << endl;
// 		stream << '[';
// 		for (size_t i = dim; i < arg.total_size; i+stride[dim]){
// 			stream << arg[i];
// 			stream << ", ";
// 		}
// 		stream << " ]";
// 	}
// 	stream << ']';
// 	return stream;
// }

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
NdarrayMetadata<T, num_dimensions> create_array(T* pointer_to_allocated_memory_, array<size_t, num_dimensions> shape_) {
	auto destructor_=_initDeleter<T>;
	cout << "created. \n";
	return NdarrayMetadata<T,num_dimensions>(calc_size(shape_), 0, shared_ptr<T>(pointer_to_allocated_memory_, destructor_),
						shape_, calc_strides(shape_));
}


template<typename T, size_t num_dimensions>
NdarrayMetadata<T, num_dimensions> create_array(array<size_t, num_dimensions> shape_) {
	
	vector<T> allocated_memory(calc_size<size_t, num_dimensions>(shape_));
	auto destructor_=_initDeleter<T>;
	auto pointer_to_allocated_memory_ = allocated_memory.data();
	return NdarrayMetadata<T,num_dimensions>(calc_size(shape_), 0, shared_ptr<T>(pointer_to_allocated_memory_, destructor_),shape_, calc_strides(shape_));
}


#endif