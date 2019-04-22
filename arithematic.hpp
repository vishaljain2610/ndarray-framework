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

namespace numc {

	template<typename T, size_t num_dimensions>
	T calc_size(array<T, num_dimensions> a){
		return std::accumulate(a.begin(), a.end(), 1, std::multiplies<T>());
	}
    template<typename T, size_t num_dimensions> 
    T sum(NdarrayMetadata<T, num_dimensions> a){

        size_t output = 0;
        for(size_t i = 0;i<a.total_size;i++){
            output += a(i);
        }
        return output;
    }

	template<typename T, size_t num_dimensions> 
    T prod(NdarrayMetadata<T, num_dimensions>* a){
        T output = 1;
        auto input_iter = a->data_buffer.get();
        for(size_t i = 0;i<a->total_size;i++){
            output *= input_iter[i];
        }
        return output;
    }
	
	template<typename T, size_t num_dimensions> 
    T mean(NdarrayMetadata<T, num_dimensions>* a){
        return a->mean();
    }


	template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions-1>* sum(NdarrayMetadata<T, num_dimensions>* a,NdarrayMetadata<T, num_dimensions-1>* re, size_t axis){
        cout << "In sum..";
        auto output_iter = re->data_buffer.get();
        auto input_iter = a->data_buffer.get();
        size_t axis_stride= a->strides[axis];
        size_t axis_shape = a->shape[axis];
        cout << "Axis that is getting reduced is " << axis_shape <<endl  ;
        
        size_t prev_axis_stride = a->strides[axis-1];
        size_t prev_axis_prod = 1;
        
        for(size_t i=0;i<axis;i++)
            prev_axis_prod*=a->shape[i];

        for(size_t i = 0;i<prev_axis_prod;i++){
            for(size_t j = 0;j<axis_shape;j++) {
                for(size_t k = 0;k<axis_stride;k++) {
                    output_iter[k + i*prev_axis_stride/axis_shape] += input_iter[k + i*prev_axis_stride + j*axis_stride];
                }
            }
        }
        
        return re;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions-1>* mean(NdarrayMetadata<T, num_dimensions>* a,NdarrayMetadata<T, num_dimensions-1>* re, size_t axis){
        auto output_iter = re->data_buffer.get();
        auto input_iter = a->data_buffer.get();
        size_t axis_stride= a->strides[axis];
        size_t axis_shape = a->shape[axis];
        
        size_t prev_axis_stride = a->strides[axis-1];
        size_t prev_axis_prod = 1;
        
        for(size_t i=0;i<axis;i++)
            prev_axis_prod*=a->shape[i];

        for(size_t i = 0;i<prev_axis_prod;i++){
            for(size_t j = 0;j<axis_shape;j++) {
                for(size_t k = 0;k<axis_stride;k++) {
                    output_iter[k + i*prev_axis_stride/axis_shape] += input_iter[k + i*prev_axis_stride + j*axis_stride];
                }
            }
        }

        for(size_t index=0;index<re->total_size;index++)
            output_iter[index] /= axis_shape;
        
        return re;
    }

	template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions-1>* prod(NdarrayMetadata<T, num_dimensions>* a,NdarrayMetadata<T, num_dimensions-1>* re, size_t axis){
        auto output_iter = re->data_buffer.get();
        auto input_iter = a->data_buffer.get();
        size_t axis_stride= a->strides[axis];
        size_t axis_shape = a->shape[axis];
        
        size_t prev_axis_stride = a->strides[axis-1];
        size_t prev_axis_prod = 1;
        
        for(size_t i=0;i<axis;i++)
            prev_axis_prod*=a->shape[i];

        for(size_t i = 0;i<prev_axis_prod;i++){
            for(size_t j = 0;j<axis_shape;j++) {
                for(size_t k = 0;k<axis_stride;k++) {
                    output_iter[k + i*prev_axis_stride/axis_shape] *= input_iter[k + i*prev_axis_stride + j*axis_stride];
                }
            }
        }
        
        return re;

    }

	template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions>* add(NdarrayMetadata<T, num_dimensions>* array1,NdarrayMetadata<T, num_dimensions>* array2, NdarrayMetadata<T, num_dimensions>* output){
		for(size_t i = 0; i< array1->total_size; i++){
			output->data_buffer.get()[i] = array1->data_buffer.get()[i] + array2->data_buffer.get()[i];
		} 
		return output;
	}

	template<size_t num_dimensions> NdarrayMetadata<double, num_dimensions>* subtract(NdarrayMetadata<double, num_dimensions>* array, double value, NdarrayMetadata<double, num_dimensions>* output){
	
		for(size_t i = 0; i< array->total_size; i++){
			output->data_buffer.get()[i] = array->data_buffer.get()[i] - value;
			cout << output->data_buffer.get()[i] << " " << array->data_buffer.get()[i] << " \n";
		}

        
		cout << endl;
		return output;
	}

	template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions>* square(NdarrayMetadata<T, num_dimensions>* array, NdarrayMetadata<T, num_dimensions>* output){
        
        cout << "In Element-wise Square \n ";
		for(size_t i = 0; i< array->total_size; i++){
			output->data_buffer.get()[i] = array->data_buffer.get()[i] * array->data_buffer.get()[i];
		}

		return output;
	}

	template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions>* multiply(NdarrayMetadata<T, num_dimensions>* array1,NdarrayMetadata<T, num_dimensions>* array2, NdarrayMetadata<T, num_dimensions>* output){
        cout << "In Element-wise Multiplication \n";
		for(size_t i = 0; i< array1->total_size; i++){
			output->data_buffer.get()[i] = array1->data_buffer.get()[i] * array2->data_buffer.get()[i];
		} 
		return output;
	}


    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* cumprod(NdarrayMetadata<T, num_dimensions>* a,NdarrayMetadata<T, num_dimensions>* output){

        auto input_iter = a->data_buffer.get(); 
        auto cumprod = input_iter[0];   
        auto output_iter = output->data_buffer.get();
        for(size_t i = 0;i<a->total_size;i++){
                cumprod *= input_iter[i];
                output_iter[i] = cumprod;
        }

        return output;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* cumsum(NdarrayMetadata<T, num_dimensions>* a,NdarrayMetadata<T, num_dimensions>* output){

        auto input_iter = a->data_buffer.get(); 
        T cumsum = input_iter[0];   
        auto output_iter = output->data_buffer.get();
        for(size_t i = 0;i<a->total_size;i++){
                cumsum += input_iter[i];
                output_iter[i] = cumsum;
        }

        return output;
    }

	
    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* negative(NdarrayMetadata<T, num_dimensions>* a,NdarrayMetadata<T, num_dimensions>* output){

        auto input_iter = a->data_buffer.get(); 
          
        auto output_iter = output->data_buffer.get();
        for(size_t i = 0;i<a->total_size;i++){
                output_iter[i] = -1*input_iter[i] ;
        }

        return output;
    }

	template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* reciprocal(NdarrayMetadata<T, num_dimensions>* a,NdarrayMetadata<double, num_dimensions>* output){

        auto input_iter = a->data_buffer.get(); 
          
        auto output_iter = output->data_buffer.get();
        for(size_t i = 0;i<a->total_size;i++){
            output_iter[i] = 1.0/(1.0*input_iter[i]) ;
        }

        return output;
    }

	template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, 1> ediff1d(NdarrayMetadata<T, num_dimensions>* a,NdarrayMetadata<T, 1>* output){
		

        auto input_iter = a->data_buffer.get(); 
        auto output_iter = output->data_buffer.get();
        for(size_t i = 0;i<a->total_size;i++){
                output_iter[i] = input_iter[i+1]-input_iter[i];
        }
        return output;
    }


	template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* absolute(NdarrayMetadata<T, num_dimensions>* Array,NdarrayMetadata<T, num_dimensions>* output){

        std::transform(Array->begin(), Array->end(), output->begin(), [](T inValue) -> T {return std::abs(inValue); });

        return output;
    }

	template<typename T, size_t num_dimensions>
    NdarrayMetadata<double, num_dimensions>* sin(NdarrayMetadata<T, num_dimensions>* Array,NdarrayMetadata<double, num_dimensions>* output)
    {
        
        for(size_t i =0 ; i < output.total_size;i++)
			output->data_buffer.get()[i] = std::sin(static_cast<double>(Array->data_buffer.get()[i]));
		
		for(auto elem : output)
			cout << elem << " ";
        return output;
    }
	
	template<typename T, size_t num_dimensions>
    NdarrayMetadata<double, num_dimensions>* cos(NdarrayMetadata<T, num_dimensions>* Array,NdarrayMetadata<double, num_dimensions>* output)
    {
        
        for(size_t i =0 ; i < output.total_size;i++)
			output->data_buffer.get()[i] = std::cos(static_cast<double>(Array->data_buffer.get()[i]));
		
		for(auto elem : output)
			cout << elem << " ";
        return output;
    }
	
	template<typename T, size_t num_dimensions>
    NdarrayMetadata<double, num_dimensions>* tan(NdarrayMetadata<T, num_dimensions>* Array,NdarrayMetadata<double, num_dimensions>* output)
    {
        
        for(size_t i =0 ; i < output.total_size;i++)
			output->data_buffer.get()[i] = std::tan(static_cast<double>(Array->data_buffer.get()[i]));
		
		for(auto elem : output)
			cout << elem << " ";
        return output;
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<double, num_dimensions>* arcsin(NdarrayMetadata<T, num_dimensions>* Array,NdarrayMetadata<double, num_dimensions>* output)
    {
        
        for(size_t i =0 ; i < output.total_size;i++)
			output->data_buffer.get()[i] = std::asin(static_cast<double>(Array->data_buffer.get()[i]));
		
		for(auto elem : output)
			cout << elem << " ";
        return output;
    }
	
    template<typename T, size_t num_dimensions>
    NdarrayMetadata<double, num_dimensions>* arccos(NdarrayMetadata<T, num_dimensions>* Array,NdarrayMetadata<double, num_dimensions>* output)
    {
        
        for(size_t i =0 ; i < output.total_size;i++)
			output->data_buffer.get()[i] = std::acos(static_cast<double>(Array->data_buffer.get()[i]));
		
		for(auto elem : output)
			cout << elem << " ";
        return output;
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<double, num_dimensions>* arctan(NdarrayMetadata<T, num_dimensions>* Array,NdarrayMetadata<double, num_dimensions>* output)
    {
        
        for(size_t i =0 ; i < output.total_size;i++)
			output->data_buffer.get()[i] = std::atan(static_cast<double>(Array->data_buffer.get()[i]));
		
		for(auto elem : output)
			cout << elem << " ";
        return output;
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<double, num_dimensions>* acosh(NdarrayMetadata<T, num_dimensions>* Array,NdarrayMetadata<double, num_dimensions>* output)
    {
        
        for(size_t i =0 ; i < output.total_size;i++)
			output->data_buffer.get()[i] = std::acosh(static_cast<double>(Array->data_buffer.get()[i]));
		
		for(auto elem : output)
			cout << elem << " ";
        return output;
    }   

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<double, num_dimensions>* asinh(NdarrayMetadata<T, num_dimensions>* Array,NdarrayMetadata<double, num_dimensions>* output)
    {
        
        for(size_t i =0 ; i < output.total_size;i++)
			output->data_buffer.get()[i] = std::asinh(static_cast<double>(Array->data_buffer.get()[i]));
		
		for(auto elem : output)
			cout << elem << " ";
        return output;
    }

template<typename T, size_t num_dimensions>
    NdarrayMetadata<double, num_dimensions>* atanh(NdarrayMetadata<T, num_dimensions>* Array,NdarrayMetadata<double, num_dimensions>* output)
    {
        
        for(size_t i =0 ; i < output.total_size;i++)
			output->data_buffer.get()[i] = std::atanh(static_cast<double>(Array->data_buffer.get()[i]));
		
		for(auto elem : output)
			cout << elem << " ";
        return output;
    }
    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arctan2(NdarrayMetadata<T, num_dimensions>* ArrayY, NdarrayMetadata<T, num_dimensions>* ArrayX,NdarrayMetadata<T, num_dimensions>*  output)
    {
        if (ArrayY.shape() != ArrayX.shape())
        {
            throw UnequalShapeError();
        }
        std::transform(ArrayY->begin(), ArrayY->end(), ArrayX->begin(), output->begin(),
            [](T Y,T X)  noexcept -> double { return std::atan2(static_cast<double>(Y), static_cast<double>(X)); });
        return std::move(output);
    }

}

#endif 