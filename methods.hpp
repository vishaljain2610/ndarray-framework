#ifndef METHODS_H
#define METHODS_H

#include <iostream>
#include <array>
#include <bitset>
#include <algorithm>
#include <memory>
#include <cstdarg>
#include <string.h> 

#include "ndarray.hpp"
#include "arithematic.hpp"
#include "slice.hpp"
#include "helperfunctions.hpp"

namespace numc
{        //Forward Reference to Functions

    template<typename T> NdarrayMetadata<T,1> arange(T inSize);
    template<typename T> NdarrayMetadata<T,1> arange(T inStart, T inStop, T inStep);

    template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions> clip(NdarrayMetadata<T, num_dimensions> Array,int64_t inMin, int64_t inMax);

    template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions> copy(NdarrayMetadata<T, num_dimensions> Array);

    template<typename T, size_t num_dimensions> T max(NdarrayMetadata<T, num_dimensions> Array);

    //Function Definations

    template<typename T>
    NdarrayMetadata<T,1> arange(T inSize)
    {
        if (inSize < 0)
        {
            string errStr = "ERROR: arange: Size should be greater than zero.";
            cerr << errStr << endl;
            throw std::invalid_argument(errStr);
        }

        array<size_t, 1> shape;
        shape[0] = inSize;
        vector<T> allocated_memory(calc_size<size_t, 1>(shape));
        auto output = create_array<T, 1>(allocated_memory.data(), shape);
        auto output_iter = output.data_buffer.get();

        for(T i = 0;i<inSize;i++) {
            output_iter[i] = i;
            // cout << output_iter[i] << " ";
        }    
        cout << "\n";
        return std::move(output);
    }
   
    template<typename T>
    NdarrayMetadata<T,1> arange(T inStart, T inStop, T inStep)
    {
        if (inStep > 0 && inStop < inStart)
        {
            std::string errStr = "ERROR: arange: stop value must be larger than the start value for positive step.";
            std::cerr << errStr << std::endl;
            throw std::invalid_argument(errStr);
        }

        if (inStep < 0 && inStop > inStart)
        {
            std::string errStr = "ERROR: arange: start value must be larger than the stop value for negative step.";
            std::cerr << errStr << std::endl;
            throw std::invalid_argument(errStr);
        }

        T inSize = std::abs(inStart-inStop)/std::abs(inStep);
        array<size_t, 1> shape;
        shape[0] = inSize;
        vector<T> allocated_memory(calc_size<size_t, 1>(shape));
        auto output = create_array<T, 1>(allocated_memory.data(), shape);
        auto output_iter = output.data_buffer.get();
        T theValue = inStart;

        for(T i = 0;i<inSize;i++) {
            output_iter[i] = theValue;
            theValue+=inStep;
        }    
        return std::move(output);
    }


    template<typename T, size_t num_dimensions> 
    T argmax(NdarrayMetadata<T, num_dimensions> Array){

        auto output = 0;
        auto input_iter = Array.data_buffer.get();
        for(size_t i = 0;i<Array.total_size;i++){
            if(output < input_iter[i])
                output = i;
        }
        return output;
    }

    template<typename T, size_t num_dimensions> 
    T argmin(NdarrayMetadata<T, num_dimensions> Array){

        auto output = 0;
        auto input_iter = Array.data_buffer.get();
        for(size_t i = 0;i<Array.total_size;i++){
            if(output > input_iter[i])
                output = i;
        }
        return output;
    }

    template<typename T,typename Out, size_t num_dimensions> 
    NdarrayMetadata<Out, num_dimensions> astype(NdarrayMetadata<T, num_dimensions> Array ,Out dtype, bool copy){
        auto iter_input = Array.data_buffer.get();    
        array<size_t, num_dimensions> out_shape = Array.shape;
        vector<Out> output_allocated_memory(calc_size<size_t, num_dimensions>(out_shape));
        auto output = create_array<Out, num_dimensions>(output_allocated_memory.data(), out_shape); 
        // auto output = copy(Array);    
        
        auto iter_output = output.data_buffer.get();
        for (size_t i =0; i<Array.total_size;i++){    
                iter_output[i] = static_cast<Out>(iter_input[i]); 
                
        }
        return output;
    }

    

    template<typename T, size_t num_dimensions> 
    double average(NdarrayMetadata<T, num_dimensions> Array){

        double output =  static_cast<double>(std::accumulate(Array.begin(), Array.end(), 0.0));
        output /= Array.total_size;
        return output;
    }

    
    template<typename T,size_t num_dimensions>
    vector<T> bincount(NdarrayMetadata<T, num_dimensions> inArray, size_t inMinLength)
    {
        // only works with integer input types
        static_assert(std::numeric_limits<T>::is_integer, "ERROR: bincount: can only use with integer types.");

        int64_t maxValue = max(inArray);
        cout << maxValue;
        if (maxValue < 0)
        {
            return std::move(vector<T>());
        }

        if (maxValue + 1 > std::numeric_limits<T>::max())
        {
            std::string errStr = "Error : array values too large, will result in gigantic array that will take up alot of memory...";
            std::cerr << errStr << std::endl;
            throw std::invalid_argument(errStr);
        }

        const size_t outArraySize = std::max(static_cast<size_t>(maxValue + 1), inMinLength);
        
        vector<T> output_vector(outArraySize);
        auto clippedArray = numc::clip(inArray, 0, maxValue);
        
        cout << endl;
        for (auto value : clippedArray)
        {
            ++output_vector[value];
            // cout << value << "-";
        }
        cout << endl;
        return output_vector;
    }
    
    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* byteswap(NdarrayMetadata<T, num_dimensions>* a){
        auto iter_input = a->data_buffer.get();    
        
        for (size_t i =0; i<a->total_size;i++){
            iter_input[i] = __builtin_bswap64 (iter_input[i]);
        }
        return a;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* clip(NdarrayMetadata<T, num_dimensions>* Array ,int64_t min,int64_t max){    
        auto iter_output = Array->data_buffer.get();

        for(size_t i=0;i<Array->total_size;i++){
            if(iter_output[i] < min)
                iter_output[i] = min;
            if(iter_output[i] > max)
                iter_output[i] = max;
        }   
        return Array;
    }

    


    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions> copy(NdarrayMetadata<T, num_dimensions> a){

        auto iter_input = a->data_buffer.get();   
        
        array<size_t, num_dimensions> out_shape = a.shape;
        vector<T> output_allocated_memory(calc_size<size_t, num_dimensions>(out_shape));
        auto output = create_array<T, num_dimensions>(output_allocated_memory.data(), out_shape);    
        
        auto iter_output = output.data_buffer.get();
        for(size_t i = 0;i<a.total_size;i++){
            iter_output[i] = iter_input[i];
        }
        return output;
    }


    template<typename T> 
    NdarrayMetadata<T , 2> eye(size_t N){
        
        array<size_t, 2> out_shape;
        out_shape.fill(N);
        vector<int64_t> output_allocated_memory(calc_size<size_t, 2>(out_shape));
        auto output = create_array<int64_t, 2>(output_allocated_memory.data(), out_shape);    
        
        for (size_t i=0;i<N;i++)
            output(i,i) = 1;

        return output;

    }
    
    template<typename T> 
    NdarrayMetadata<T , 2> eye(size_t N, size_t M){
        
        array<size_t, 2> out_shape;
        out_shape[0] = N;
        out_shape[1] = M;
        vector<int64_t> output_allocated_memory(calc_size<size_t, 2>(out_shape));
        auto output = create_array<int64_t, 2>(output_allocated_memory.data(), out_shape);    
        
        size_t len = (N>M)?N:M;
        for (size_t i=0;i<len;i++)
            output(i,i) = 1;
        
        return output;

    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T , 1>* flatten(NdarrayMetadata<T, num_dimensions>* a,NdarrayMetadata<T, 1>* output){
        
        auto iter_input = a->data_buffer.get();
        auto iter_output = output->data_buffer.get();

        for (size_t i=0;i<a->total_size;i++)
            iter_output[i] = iter_input[i] ;

        return output;

    }

    template<typename T, size_t num_dimensions> 
    void fill(NdarrayMetadata<T, num_dimensions>* a ,int64_t val){
        
        auto iter_input = a->data_buffer.get();

        for (size_t i=0;i<a->total_size;i++)
            iter_input[i] = val;
    }
  
    bool is_big_endian(void)
    {
            union {
                    uint32_t i;
                    char c[4];
            } bint = {0x01020304};

            return bint.c[0] == 1; 
    }

    template<typename T, size_t num_dimensions> 
    T item(NdarrayMetadata<T, num_dimensions>* a, array<T, num_dimensions> location){
        T output;
        size_t strides = 0;
        size_t offset = 0;
        size_t t = 0;
        while(strides < num_dimensions){
            offset += location[t]*a->strides[strides];
            strides++;
            t++;
        }
        return a->data_buffer.get()[offset];
    }

    template<typename T, size_t num_dimensions> 
    T max(NdarrayMetadata<T, num_dimensions>* a){

        auto input_iter = a->data_buffer.get();
        T output = input_iter[0];
        for(size_t i = 1;i<a.total_size;i++){
            if(output < input_iter[i])
                output = input_iter[i];
        }
        return output;
    }

    template<typename T, size_t num_dimensions> 
    T min(NdarrayMetadata<T, num_dimensions> a){

        auto input_iter = a->data_buffer.get();
        T output = input_iter[0];
        for(size_t i = 1;i<a.total_size;i++){
            if(output > input_iter[i])
                output = input_iter[i];
        }
        return output;
    }


    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* newbyteorder(NdarrayMetadata<T, num_dimensions>* a){
        return byteswap(a);
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions>* round(NdarrayMetadata<T, num_dimensions>* Array,NdarrayMetadata<T, num_dimensions>* output, size_t decimals){

        auto input_iter = Array->data_buffer.get();    
        auto output_iter = output->data_buffer.get();
        for(size_t i = 0;i<Array->total_size;i++){
                output_iter[i] = std::round(input_iter[i]);
        }
        return output;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T , 1> ravel(NdarrayMetadata<T, num_dimensions>* a,NdarrayMetadata<T , 1>* output){
        
        auto iter_input = a->data_buffer.get();
        auto iter_output = output->data_buffer.get();

        for (size_t i=0;i<a->total_size;i++)
            iter_output[i] = iter_input[i] ;

        return output;

    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions-1>* squeeze(NdarrayMetadata<T, num_dimensions-1>* output,NdarrayMetadata<T, num_dimensions>* a, size_t axis){
        
        if(a.shape[axis] != 1)
        {
            throw "ValueError: cannot select an axis to squeeze out which has size not equal to one";
        } else {
            

            
        for(size_t i = 0;i<output->total_size;i++){
            output->data_buffer.get()[i] = a->data_buffer.get()[i];
        }

            return output;
        }
    }



    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> zeros(array<size_t, num_dimensions> shape_) {
        
        auto output = NdarrayMetadata<T,num_dimensions>(shape_);
        fill(output,0);
        return output;
    }

    
    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> ones(array<size_t, num_dimensions> shape_) {
        
        auto output = NdarrayMetadata<T,num_dimensions>(shape_);
        fill(output,1);
        return output;
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> full(array<size_t, num_dimensions> shape_, T val) {
        
        auto output = NdarrayMetadata<T,num_dimensions>(shape_);
        fill(output,val);
        return output;
    }

}
#endif