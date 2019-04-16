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
    T prod(NdarrayMetadata<T, num_dimensions> a){
        size_t output = 0;
        auto input_iter = a.data_buffer.get();
        for(size_t i = 0;i<a.total_size;i++){
            output *= input_iter[i];
        }
        return output;
    }
	
	template<typename T, size_t num_dimensions> 
    T mean(NdarrayMetadata<T, num_dimensions> a){
		
        size_t output = 0;
        for(size_t i = 0;i<a.total_size;i++){
            output += a(i);
        }
        output = (output)/a.total_size;
        return output;
    }


	template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions-1> sum(NdarrayMetadata<T, num_dimensions> a, size_t axis){
        	array<size_t,num_dimensions-1> output_shape = removeArrayElement(a.shape,axis);
			vector<T> allocated_memory3(calc_size<size_t,num_dimensions-1>(output_shape));
			auto output = NdarrayMetadata<T,num_dimensions-1>(allocated_memory3.data(), output_shape);

        auto output_iter = output.data_buffer.get();
        std::fill(output.begin(), output.end(), 0);
        auto input_iter = a.data_buffer.get();
        size_t axis_stride= a.strides[axis];
        size_t axis_shape = a.shape[axis];
        
        size_t prev_axis_stride = a.strides[axis-1];
        size_t prev_axis_prod = 1;
        
        for(size_t i=0;i<axis;i++)
            prev_axis_prod*=a.shape[i];

        for(size_t i = 0;i<prev_axis_prod;i++){
            for(size_t j = 0;j<axis_shape;j++) {
                for(size_t k = 0;k<axis_stride;k++) {
                    output_iter[k + i*prev_axis_stride/axis_shape] += input_iter[k + i*prev_axis_stride + j*axis_stride];
                }
            }
        }
        cout << endl;
        return output;

    }

	template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions-1> prod(NdarrayMetadata<T, num_dimensions> a, size_t axis){
        array<T,num_dimensions-1> output_shape = removeArrayElement(a.shape,axis);
        auto output = create_array<T,num_dimensions-1>(output_shape);

        auto output_iter = output.data_buffer.get();
        std::fill(output.begin(), output.end(), 0);
        auto input_iter = a.data_buffer.get();
        size_t axis_stride= a.strides[axis];
        size_t axis_shape = a.shape[axis];
        
        size_t prev_axis_stride = a.strides[axis-1];
        size_t prev_axis_prod = 1;
        
        for(size_t i=0;i<axis;i++)
            prev_axis_prod*=a.shape[i];

        for(size_t i = 0;i<prev_axis_prod;i++){
            for(size_t j = 0;j<axis_shape;j++) {
                for(size_t k = 0;k<axis_stride;k++) {
                    output_iter[k + i*prev_axis_stride/axis_shape] *= input_iter[k + i*prev_axis_stride + j*axis_stride];
                }
            }
        }
        cout << endl;
        return output;

    }

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
		array<size_t,num_dimensions> shapearray = array1.shape;
		auto output = NdarrayMetadata<T, num_dimensions>(shapearray);
		for(size_t i = 0; i< array1.total_size; i++){
			cout << array1(i) * array2(i) << " ";
			output(i) = array1(i) * array2(i);
		}
		return (output);
	}


    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions> cumprod(NdarrayMetadata<T, num_dimensions> a){
        array<size_t,num_dimensions> output_shape = a.shape;
        vector<int64_t> allocated_memory3(calc_size<size_t,num_dimensions>(output_shape));
        auto output = create_array<int64_t,num_dimensions>(allocated_memory3.data(), output_shape);

        auto input_iter = a.data_buffer.get(); 
        auto cumprod = input_iter[0];   
        auto output_iter = output.data_buffer.get();
        for(size_t i = 0;i<a.total_size;i++){
                cumprod *= input_iter[i];
                // cout << cumprod << " ";
                output_iter[i] = cumprod;
        }

        return output;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions> cumsum(NdarrayMetadata<T, num_dimensions> a){
        array<size_t,num_dimensions> output_shape = a.shape;
        vector<int64_t> allocated_memory3(calc_size<size_t,num_dimensions>(output_shape));
        auto output = create_array<int64_t,num_dimensions>(allocated_memory3.data(), output_shape);

        auto input_iter = a.data_buffer.get(); 
        auto cumsum = input_iter[0];   
        auto output_iter = output.data_buffer.get();
        for(size_t i = 0;i<a.total_size;i++){
                cumsum += input_iter[i];
                // cout << cumsum << " ";
                output_iter[i] = cumsum;
        }

        return output;
    }

	template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions> negative(NdarrayMetadata<T, num_dimensions> a){
        auto output = create_array<T,num_dimensions>(a.shape);

        auto input_iter = a.data_buffer.get(); 
        auto output_iter = output.data_buffer.get();
        for(size_t i = 0;i<a.total_size;i++){
                output_iter[i] = -1*input_iter[i];;
        }

        return output;
    }

	template<typename T, size_t num_dimensions> 
    NdarrayMetadata<double, num_dimensions> reciprocal(NdarrayMetadata<T, num_dimensions> a){
        auto output = create_array<double,num_dimensions>(a.shape);

        auto input_iter = a.data_buffer.get(); 
        auto output_iter = output.data_buffer.get();
        for(size_t i = 0;i<a.total_size;i++){
                output_iter[i] = 1.0/(1.0*input_iter[i]);
        }

        return output;
    }

	template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, 1> ediff1d(NdarrayMetadata<T, num_dimensions> a){
		
		array<size_t,1> shape;
		shape[0] = a.total_size-1;
        auto output = create_array<T,num_dimensions>(shape);

        auto input_iter = a.data_buffer.get(); 
        auto output_iter = output.data_buffer.get();
        for(size_t i = 0;i<a.total_size;i++){
                output_iter[i] = input_iter[i+1]-input_iter[i];
        }

        return output;
    }


	template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions> absolute(NdarrayMetadata<T, num_dimensions> Array){

        auto output = copy(Array);
        std::transform(Array.begin(), Array.end(), output.begin(), [](T inValue) -> T {return std::abs(inValue); });

        return output;
    }

	template<typename T, size_t num_dimensions>
    NdarrayMetadata<double, num_dimensions> sin(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = create_array<double,num_dimensions>(Array.shape);
        for(size_t i =0 ; i < output.total_size;i++)
			output.data_buffer.get()[i] = std::sin(static_cast<double>(Array.data_buffer.get()[i]));
		
		for(auto elem : output)
			cout << elem << " ";
        return (output);
    }
	
	template<typename T, size_t num_dimensions>
    NdarrayMetadata<double, num_dimensions> cos(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = create_array<double,num_dimensions>(Array.shape);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::cos(static_cast<double>(inValue)); });

        return std::move(output);
    }
	
	template<typename T, size_t num_dimensions>
    NdarrayMetadata<double, num_dimensions> tan(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = create_array<double,num_dimensions>(Array.shape);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::cos(static_cast<double>(inValue)); });

        return std::move(output);
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arcsin(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::asin(static_cast<double>(inValue)); });

        return std::move(output);
    }
	
    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arccos(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::acos(static_cast<double>(inValue)); });

        return std::move(output);
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arctan(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::atan(static_cast<double>(inValue)); });

        return std::move(output);
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arccosh(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::acosh(static_cast<double>(inValue)); });

        return std::move(output);
    }   

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arcsinh(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::asinh(static_cast<double>(inValue)); });
        return std::move(output);
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arctanh(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::atanh(static_cast<double>(inValue)); });
        return std::move(output);
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arctan2(NdarrayMetadata<T, num_dimensions> ArrayY, NdarrayMetadata<T, num_dimensions> ArrayX)
    {
        if (ArrayY.shape() != ArrayX.shape())
        {
            throw UnequalShapeError();
        }
        auto output = copy(ArrayY);
        std::fill(output.begin(), output.end(), 0);
        std::transform(ArrayY.begin(), ArrayY.end(), ArrayX.begin(), output.begin(),
            [](T Y,T X)  noexcept -> double { return std::atan2(static_cast<double>(Y), static_cast<double>(X)); });
        return std::move(output);
    }

}

#endif 