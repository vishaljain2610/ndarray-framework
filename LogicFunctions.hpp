#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <array>
#include <bitset>
#include <algorithm>
#include <memory>
#include <cstdarg>
#include <string.h> 

#include "ndarray.hpp"
#include "slice.hpp"

namespace numc{
    template<typename T, size_t num_dimensions> 
    bool all(NdarrayMetadata<T, num_dimensions> Array){
        return Array.all();
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions-1> all(NdarrayMetadata<T, num_dimensions> Array, size_t axis){
        return Array.all(axis);
    }


    template<typename T, size_t num_dimensions> 
    bool any(NdarrayMetadata<T, num_dimensions> Array){
        return Array.any();
    }
    
    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions-1> any(NdarrayMetadata<T, num_dimensions> Array, size_t axis){
        return Array.any(axis);
    }

    template<typename T, size_t num_dimensions> 
    bool allclose(NdarrayMetadata<T, num_dimensions> Array1,NdarrayMetadata<T, num_dimensions> Array2, long long Tolerance){

        if(Array1.shape != Array2.shape )
            throw UnequalShapeError();
        else{
            size_t len = Array1.total_size;

            T* Array1_iter = Array1.data_buffer.get(); 
            T* Array2_iter = Array2.data_buffer.get(); 

            for(size_t i =0; i<len;i++){
                if(std::abs(Array1_iter[i] - Array2_iter[i]) > Tolerance)
                    {
                        return false;
                    }
            }
        }
        return true;
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> logical_and(NdarrayMetadata<T, num_dimensions> Array1, NdarrayMetadata<T, num_dimensions> Array2)
    {
        if (Array1.shape != Array2.shape)
        {
            throw UnequalShapeError();
        }

        auto output = create_array<T,num_dimensions>(Array1.shape);
        std::transform(Array1.begin(), Array1.end(), Array2.begin(), output.begin(),
            [](T inValue1, T inValue2) noexcept -> bool { return (inValue1 != 0) && (inValue2 != 0); });

        return (output);
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> logical_or(NdarrayMetadata<T, num_dimensions> Array1, NdarrayMetadata<T, num_dimensions> Array2)
    {
        if (Array1.shape != Array2.shape)
        {
            throw UnequalShapeError();
        }

        auto output = create_array<T,num_dimensions>(Array1.shape);
        std::transform(Array1.begin(), Array1.end(), Array2.begin(), output.begin(),
            [](T inValue1, T inValue2) noexcept -> bool { return (inValue1 != 0) || (inValue2 != 0); });

        return std::move(output);
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> logical_xor(NdarrayMetadata<T, num_dimensions> Array1, NdarrayMetadata<T, num_dimensions> Array2)
    {
        if (Array1.shape != Array2.shape)
        {
            throw UnequalShapeError();
        }

        auto output = create_array<T,num_dimensions>(Array1.shape);
        std::transform(Array1.begin(), Array1.end(), Array2.begin(), output.begin(),
            [](T inValue1, T inValue2) noexcept -> bool { return (inValue1 != 0) != (inValue2 != 0); });

        return std::move(output);
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> logical_not(NdarrayMetadata<T, num_dimensions> Array)
    {

	    vector<T> allocated_memory2(calc_size<size_t,num_dimensions>(Array.shape));
	    NdarrayMetadata<T, num_dimensions> output = create_array<T,num_dimensions>(allocated_memory2,Array.shape);
     
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue) noexcept -> bool { return inValue == 0; });

        return std::move(output);
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T,num_dimensions> less_equal(NdarrayMetadata<T,num_dimensions> Array1,NdarrayMetadata<T,num_dimensions> Array2){
        if(Array1.shape != Array2.shape){
            throw UnequalShapeError();
        }

        auto output = create_array<T,num_dimensions>(Array1.shape);

        std::transform(Array1.begin(), Array1.end(), Array2.begin(),output.begin(), std::less_equal<T>());
        return output;
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T,num_dimensions> greater_equal(NdarrayMetadata<T,num_dimensions> Array1,NdarrayMetadata<T,num_dimensions> Array2){
        if(Array1.shape != Array2.shape){
            throw UnequalShapeError();
        }

        auto output = create_array<T,num_dimensions>(Array1.shape);

        std::transform(Array1.begin(), Array1.end(), Array2.begin(),output.begin(), std::greater_equal<T>());
        return output;
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T,num_dimensions> less(NdarrayMetadata<T,num_dimensions> Array1,NdarrayMetadata<T,num_dimensions> Array2){
        if(Array1.shape != Array2.shape){
            throw UnequalShapeError();
        }

        auto output = create_array<T,num_dimensions>(Array1.shape);

        std::transform(Array1.begin(), Array1.end(), Array2.begin(),output.begin(), std::less<T>());
        return output;
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T,num_dimensions> greater(NdarrayMetadata<T,num_dimensions> Array1,NdarrayMetadata<T,num_dimensions> Array2){
        if(Array1.shape != Array2.shape){
            throw UnequalShapeError();
        }

        auto output = create_array<T,num_dimensions>(Array1.shape);

        std::transform(Array1.begin(), Array1.end(), Array2.begin(),output.begin(), std::greater<T>());
        return output;
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T,num_dimensions> equal(NdarrayMetadata<T,num_dimensions> Array1,NdarrayMetadata<T,num_dimensions> Array2){
        if(Array1.shape != Array2.shape){
            throw UnequalShapeError();
        }

        auto output = create_array<T,num_dimensions>(Array1.shape);
        auto oiter = output.data_buffer.get();

        auto Array1_iter = Array1.data_buffer.get();
        auto Array2_iter = Array2.data_buffer.get();
        for(size_t i=0;i<Array1.total_size;i++){
            oiter[i] = (Array1_iter[i] == Array2_iter[i]); 
        }
        return output;
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T,num_dimensions> not_equal(NdarrayMetadata<T,num_dimensions> Array1,NdarrayMetadata<T,num_dimensions> Array2){
        if(Array1.shape != Array2.shape){
            throw UnequalShapeError();
        }

        auto output = create_array<T,num_dimensions>(Array1.shape);
        auto oiter = output.data_buffer.get();

        auto Array1_iter = Array1.data_buffer.get();
        auto Array2_iter = Array2.data_buffer.get();
        for(size_t i=0;i<Array1.total_size;i++){
            oiter[i] = (Array1_iter[i] != Array2_iter[i]); 
        }
        return output;
    }

    template<typename T, size_t num_dimensions>
    NdarrayMetadata<bool, num_dimensions> array_equal(NdarrayMetadata<T, num_dimensions> Array1, NdarrayMetadata<T, num_dimensions> Array2)
    {
        if (Array1.shape != Array2.shape)
        {
            return false;
        }

        auto output = create_array<bool, num_dimensions>(Array1.shape);

        for(size_t i =0;i<Array1.total_size;i++)
            output.data_buffer.get()[i] = (Array1.data_buffer.get()[i] == Array2.data_buffer.get()[i]);
        
        return output;

    }
}

#endif