#ifndef BINARY_H
#define BINARY_H

#include <iostream>
#include <array>
#include <bitset>
#include <algorithm>
#include <memory>
#include <cstdarg>
#include <string.h> 

#include "ndarray.hpp"
#include "slice.hpp"
#include "helperfunctions.hpp"


namespace numc{
    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* bitwise_and(NdarrayMetadata<T, num_dimensions>* Array1,NdarrayMetadata<T, num_dimensions>* Array2, NdarrayMetadata<T, num_dimensions>* output){
        
        std::transform(Array1->begin(), Array1->end(), Array2->begin(),output->begin(), std::bit_and<T>());
        return output;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* bitwise_or(NdarrayMetadata<T, num_dimensions>* Array1,NdarrayMetadata<T, num_dimensions>* Array2, NdarrayMetadata<T, num_dimensions>* output){
        
        std::transform(Array1->begin(), Array1->end(), Array2->begin(),output->begin(), std::bit_or<T>());
        return output;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* bitwise_xor(NdarrayMetadata<T, num_dimensions>* Array1,NdarrayMetadata<T, num_dimensions>* Array2, NdarrayMetadata<T, num_dimensions>* output){
        
        std::transform(Array1->begin(), Array1->end(), Array2->begin(),output->begin(), std::bit_xor<T>());
        return output;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T,num_dimensions>* invert(NdarrayMetadata<T, num_dimensions>* Array,NdarrayMetadata<T, num_dimensions>* output){
        std::transform(Array->begin(), Array->end(), output->begin(), [](T value) noexcept -> T { return ~value; });
        return output;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* left_shift(NdarrayMetadata<T, num_dimensions>* Array1,NdarrayMetadata<T, num_dimensions>* Array2, NdarrayMetadata<T, num_dimensions>* output){
        
        std::transform(Array1->begin(), Array1->end(), Array2->begin(),output->begin(), [](T value1,T value2) noexcept -> T { return value1<<value2; });
        return output;
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions>* right_shift(NdarrayMetadata<T, num_dimensions>* Array1,NdarrayMetadata<T, num_dimensions>* Array2, NdarrayMetadata<T, num_dimensions>* output){
        
        std::transform(Array1->begin(), Array1->end(), Array2->begin(),output->begin(), [](T value1,T value2) noexcept -> T { return value1>>value2; });
        return output;
    }

    template<typename T>
    string binaryRepr(T inValue){
        cout << (std::numeric_limits<T>::digits) << endl;
        return std::bitset<(std::numeric_limits<T>::digits)>(inValue).to_string();
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions-1>* packbits(NdarrayMetadata<T, num_dimensions>* a, size_t axis,NdarrayMetadata<T, num_dimensions-1>* output){

        auto output_iter = output->data_buffer.get();
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
                    output_iter[k + i*prev_axis_stride/axis_shape] += pow(2,8-j-1)*!(input_iter[k + i*prev_axis_stride + j*axis_stride] == 0);
                }
            }
		}
        return output;
    }

}

#endif