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
#include "slice.hpp"
#include "helperfunctions.hpp"


// template<typename T, size_t num_dimensions> 
// void print(NdarrayMetadata<T, num_dimensions> a){
//     auto shape = a.shape;
    
//     cout << a.strides << endl << a.shape << endl;
//     for (size_t i =0;i<num_dimensions-1;i++){
//         cout << "[";
//     }
//     auto iter = a.data_buffer.get();
//     size_t limit = 0;
//     size_t axis = shape.size()-1;
//     while(axis > limit){
        
//         size_t element_offset= a.strides[axis];
//         size_t add_count = shape[axis];
//         for(size_t i = 0;i<add_count-1;i++ ){
//             cout << "[" << " ";    
//             for(size_t j = 0;j<add_count;j++){
//                cout << iter[j + i*element_offset] << " ";
//             }
//             cout << "]";  
//         }
//         axis--;
//     }
//     for (size_t i =0;i<num_dimensions-1;i++)
//         {cout << "]";}
// }



// template<typename T, size_t num_dimensions> 
// void print(NdarrayMetadata<T, num_dimensions> a){
//     auto shape = a.shape;
    
//     cout << a.strides << endl << a.shape << endl;
//     for (size_t i =0;i<num_dimensions-1;i++){
//         cout << "[";
//     }

//     auto iter = a.data_buffer.get();
//     size_t limit = 0;
//     size_t j = 0;
//     size_t axis = shape.size()-1;
//     for(;j<a.total_size;j++){
//         size_t prev_axis = axis-1;
//         while(prev_axis > limit){
//             // size_t element_offset= a.strides[axis];
//             size_t curr_shape = shape[axis];
//             // for(size_t i = 0;i<add_count-1;i++ ){
//             cout << "[" << " ";    
//             //     for(size_t j = 0;j<add_count;j++){
//             //     }
//             // }

//             for(size_t i = 0;i<curr_shape;i++){
//                 cout << iter[j] << " ";
//             }
//             cout << "]";  
            
//             axis--;
//         }
//     }
    
//     for (size_t i =0;i<num_dimensions-1;i++)
//         {cout << "]";}
// }

// template<typename T, size_t num_dimensions> 
// NdarrayMetadata<T, num_dimensions-1> sum(NdarrayMetadata<T, num_dimensions> a, size_t axis){
//     array<size_t,num_dimensions-1> output_shape = removeArrayElement(a.shape,axis);
// 	vector<int64_t> allocated_memory3(calc_size<size_t,num_dimensions-1>(output_shape));
// 	auto output = create_array<int64_t,num_dimensions-1>(allocated_memory3.data(), output_shape);

//     auto output_iter = output.data_buffer.get();
//     fill(output,0);
//     auto input_iter = a.data_buffer.get();
//     size_t element_offset= a.strides[axis];
//     size_t add_count = a.shape[axis];
//     cout << add_count << " " << element_offset << endl;
        
//     if(axis == 0){
//         for(size_t i = 0;i<add_count;i++ ){
//             for(size_t j = 0;j<element_offset;j++){
//                 cout << input_iter[j + i*element_offset] << " ";
//                 output_iter[j] += input_iter[j + i*element_offset];	    
//             }
//         }
//     } else {
//         size_t iter = a.shape[axis-1];
//         // for(size_t i =0;i<iter;i++){
//         //     for(size_t j = 0;j<add_count;j++ ){
//         //         for(size_t k = (0 + element_offset*i);k<element_offset;k++){
//         //             output_iter[k] += input_iter[k + j*element_offset];
//         //             cout << input_iter[k + j*element_offset] << " ";

//         //         }
//         //     }
//         // }
//         for(size_t i = 0;i<a.total_size;i++){

//             output_iter[i] = input_iter[]
//         }
//     }
//     cout << "----" << endl;
//     for(size_t i = 0;i<output.total_size;i++){
// 		cout <<output.data_buffer.get()[i] << " ";
// 	}
//     return output;

// }


// template<typename T, size_t num_dimensions> 
// NdarrayMetadata<T, num_dimensions-1> all(NdarrayMetadata<T, num_dimensions> a, size_t axis){
//     const size_t out_dimensions = (num_dimensions-1);
//     array<size_t,out_dimensions> output_shape = removeArrayElement(a.shape, axis);
// 	vector<int64_t> allocated_memory3(calc_size<size_t,out_dimensions>(output_shape));
// 	auto output = create_array<int64_t,out_dimensions>(allocated_memory3.data(), output_shape);

//     auto output_iter = output.data_buffer.get();
//     auto input_iter = a.data_buffer.get();
    
//     cout << endl;
//     fill(output ,-1);
//     size_t element_offset= a.strides[axis];
//     size_t add_count = a.shape[axis];
//     for(size_t i = 0;i<add_count;i++ ){
//         for(size_t j = 0;j<element_offset;j++){
//             if( output_iter[j] == 0 || input_iter[j + i*element_offset] == 0)
//                 output_iter[j] = false;
//             else    
//                 output_iter[j] = true;
//             // cout << j + i*element_offset << " ";
//         }
//         // cout << endl;
//     }
//     // for (size_t i =0; i<output.total_size;i++){
//     //     cout << output_iter[i] << " ";
//     // }
//     return output;

// }
namespace numc
{    //Forward Reference to Functions

    template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions> abs(NdarrayMetadata<T, num_dimensions> Array);

    template<typename T, size_t num_dimensions> bool all(NdarrayMetadata<T, num_dimensions> Array);

    template<typename T, size_t num_dimensions> bool allclose(NdarrayMetadata<T, num_dimensions> inArray1,NdarrayMetadata<T, num_dimensions> inArray2, long long Tolerance);

    template<typename T, size_t num_dimensions> bool any(NdarrayMetadata<T, num_dimensions> Array);

    template<typename T> NdarrayMetadata<T,1> arange(T inSize);
    template<typename T> NdarrayMetadata<T,1> arange(T inStart, T inStop, T inStep);

    template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions> arcsinh(NdarrayMetadata<T, num_dimensions> Array);

    template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions> arcsin(NdarrayMetadata<T, num_dimensions> Array);
    
    template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions> arccosh(NdarrayMetadata<T, num_dimensions> Array);
    
    template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions> arccos(NdarrayMetadata<T, num_dimensions> Array);

    template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions> arctanh(NdarrayMetadata<T, num_dimensions> Array);
    
    template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions> arctan(NdarrayMetadata<T, num_dimensions> Array);

    template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions> arctan2(NdarrayMetadata<T, num_dimensions> ArrayY, NdarrayMetadata<T, num_dimensions> ArrayX);


    // template<typename T, size_t num_dimensions> void clip(NdarrayMetadata<T, num_dimensions> Array,size_t inMin, size_t inMax);
    template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions> clip(NdarrayMetadata<T, num_dimensions> Array,int64_t inMin, int64_t inMax);

    template<typename T, size_t num_dimensions> NdarrayMetadata<T, num_dimensions> copy(NdarrayMetadata<T, num_dimensions> Array);

    template<typename T, size_t num_dimensions> T max(NdarrayMetadata<T, num_dimensions> Array);

//Function Definations


    //============================================================================
        // Method Description:
        ///						Calculate the absolute value element-wise.
        ///
        ///                     NumPy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.absolute.html
        ///
        /// @param
        ///				Array
        /// @return
        ///				NdarrayMetadata
        ///
    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions> abs(NdarrayMetadata<T, num_dimensions> Array){

        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(), [](T inValue) -> T {return std::abs(inValue); });

        return output;
    }

    //============================================================================
            // Method Description:
            ///						Returns True if all elements evaluate to True or non zero
            ///
            ///                     Numpy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.ndarray.all.html
            ///
            /// @param
            ///				inAxis (Optional, default NONE)
            /// @return
            ///				NdArray
            ///
    template<typename T, size_t num_dimensions> 
    bool all(NdarrayMetadata<T, num_dimensions> Array){
        return Array.all();
    }

    //============================================================================
        // Method Description:
        ///						Returns True if two arrays are element-wise equal within a tolerance.
        ///						Tolerance must be a positive number
        ///
        ///                     NumPy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.allclose.html
        ///
        /// @param				inArray1
        /// @param				inArray2
        /// @param				Tolerance
        /// @return
        ///				bool
        ///
    template<typename T, size_t num_dimensions> 
    bool allclose(NdarrayMetadata<T, num_dimensions> inArray1,NdarrayMetadata<T, num_dimensions> inArray2, long long Tolerance){

        if(inArray1.shape != inArray2.shape )
            throw UnequalShapeError();
        else{
            size_t len = inArray1.total_size;

            T* inArray1_iter = inArray1.data_buffer.get(); 
            T* inArray2_iter = inArray2.data_buffer.get(); 

            for(size_t i =0; i<len;i++){
                if(std::abs(inArray1_iter[i] - inArray2_iter[i]) > Tolerance)
                    {
                        return false;
                    }
            }
        }
        return true;
    }

    //============================================================================
        // Method Description:
        ///						Test whether any array element evaluates to True.
        ///
        ///                     NumPy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.any.html
        ///
        /// @param				Array
        /// @param				inAxis (Optional, default NONE)
        /// @return
        ///				NdArray
        ///
    template<typename T, size_t num_dimensions> 
    bool any(NdarrayMetadata<T, num_dimensions> Array){

        bool output = false;
        for(auto element : Array){
            if(element != 0 || element != false)
                output = true;
        }
        return output;
    }

    //============================================================================
        // Method Description:
        ///						Return evenly spaced values within a given interval.
        ///
        ///						Values are generated within the half - open interval[start, stop)
        ///						(in other words, the interval including start but excluding stop).
        ///						For integer arguments the function is equivalent to the Python built - in
        ///						range function, but returns an ndarray rather than a list.
        ///
        ///						When using a non - integer step, such as 0.1, the results will often
        ///						not be consistent.It is better to use linspace for these cases.
        ///
        ///                     NumPy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.arange.html
        ///
        /// @param				inSisze
        /// @return
        ///				NdArray
        ///
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
    //============================================================================
        // Method Description:
        ///						Return evenly spaced values within a given interval.
        ///
        ///						Values are generated within the half - open interval[start, stop)
        ///						(in other words, the interval including start but excluding stop).
        ///						For integer arguments the function is equivalent to the Python built - in
        ///						range function, but returns an ndarray rather than a list.
        ///
        ///						When using a non - integer step, such as 0.1, the results will often
        ///						not be consistent.It is better to use linspace for these cases.
        ///
        ///                     NumPy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.arange.html
        ///
        /// @param				inStart
        /// @param				inStop
        /// @param				inStep: (Optional, defaults to 1)
        /// @return
        ///				NdArray
        ///
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

    //============================================================================
        // Method Description:
        ///						Trigonometric inverse cosine, element-wise.
        ///
        ///                     NumPy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.arccos.html
        ///
        /// @param
        ///				Array
        /// @return
        ///				NdArray
        ///
    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arccos(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::acos(static_cast<double>(inValue)); });

        return std::move(output);
    }

    //============================================================================
        // Method Description:
        ///						Trigonometric inverse hyperbolic cosine, element-wise.
        ///
        ///                     NumPy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.arccosh.html
        ///
        /// @param
        ///				Array
        /// @return
        ///				NdArray
        ///
    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arccosh(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::acosh(static_cast<double>(inValue)); });

        return std::move(output);
    }

    //============================================================================
        // Method Description:
        ///						Trigonometric inverse sine, element-wise.
        ///
        ///                     NumPy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.arcsin.html
        ///
        /// @param
        ///				Array
        /// @return
        ///				NdArray
        ///
    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arcsin(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::asin(static_cast<double>(inValue)); });

        return std::move(output);
    }

    //============================================================================
        // Method Description:
        ///						Trigonometric inverse hyperbolic sine, element-wise.
        ///
        ///                     NumPy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.arcsinh.html
        ///
        /// @param
        ///				Array
        /// @return
        ///				NdArray
        ///
    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arcsinh(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::asinh(static_cast<double>(inValue)); });
        return std::move(output);
    }

    //============================================================================
        // Method Description:
        ///						Trigonometric inverse tane, element-wise.
        ///
        ///                     NumPy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.arctan.html
        ///
        /// @param
        ///				Array
        /// @return
        ///				NdArray
        ///
    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arctan(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::atan(static_cast<double>(inValue)); });

        return std::move(output);
    }

    //============================================================================
        // Method Description:
        ///						Trigonometric inverse hyperbolic tane, element-wise.
        ///
        ///                     NumPy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.arctanh.html
        ///
        /// @param
        ///				Array
        /// @return
        ///				NdArray
        ///
    template<typename T, size_t num_dimensions>
    NdarrayMetadata<T, num_dimensions> arctanh(NdarrayMetadata<T, num_dimensions> Array)
    {
        
        auto output = copy(Array);
        std::fill(output.begin(), output.end(), 0);
        std::transform(Array.begin(), Array.end(), output.begin(),
            [](T inValue)  noexcept -> double { return std::atanh(static_cast<double>(inValue)); });
        return std::move(output);
    }

    //============================================================================
        // Method Description:
        ///						Trigonometric inverse tane, element-wise.
        ///
        ///                     NumPy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.arccosh.html
        ///
        /// @param
        ///				Array
        /// @return
        ///				NdArray
        ///
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

    //============================================================================
        // Method Description:
        ///						Return indices of the maximum values along the given axis.
        ///						Only the first index is returned.
        ///
        ///                     Numpy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.ndarray.argmax.html
        ///
        /// @param
        /// @return
        ///				T Index
        ///
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

    //============================================================================
        // Method Description:
        ///						Return indices of the minimum values along the given axis.
        ///						Only the first index is returned.
        ///
        ///                     Numpy Reference: https://www.numpy.org/devdocs/reference/generated/numpy.ndarray.argmin.html
        ///
        /// @param
        /// @return
        ///				T Index
        ///
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
    bool array_equal(NdarrayMetadata<T, num_dimensions> Array1, NdarrayMetadata<T, num_dimensions> Array2)
    {
        if (Array1.shape != Array2.shape)
        {
            return false;
        }

        return std::equal(Array1.begin(), Array1.end(), Array2.begin());
    }

    template<typename T, size_t num_dimensions>
    bool array_equiv(NdarrayMetadata<T, num_dimensions> Array1, NdarrayMetadata<T, num_dimensions> Array2)
    {
        if (Array1.shape != Array2.shape)
        {
            return false;
        }

        return std::equal(Array1.begin(), Array1.end(), Array2.begin());
    }

    template<typename T, size_t num_dimensions> 
    double average(NdarrayMetadata<T, num_dimensions> Array){

        double output =  static_cast<double>(std::accumulate(Array.begin(), Array.end(), 0.0));
        output /= Array.total_size;
        return output;
    }

    // template<typename T, size_t num_dimensions>
    // double average(NdarrayMetadata<T, num_dimensions> Array1, NdarrayMetadata<T, num_dimensions> weights)
    // {
    //     if (Array1.shape != weights.shape)
    //     {
    //         throw UnequalShapeError();
    //     }

        
    //     std::fill(output.begin(), output.end(), 0);
    //     std::transform(inArray.cbegin(), inArray.cend(), inWeights.cbegin(), weightedArray.begin(), std::multiplies<double>());

    // }

    template<typename T>
    string binaryRepr(T inValue)
    {
        cout << (std::numeric_limits<T>::digits) << endl;
        return std::bitset<(std::numeric_limits<T>::digits)>(inValue).to_string();
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
    NdarrayMetadata<T, num_dimensions> byteswap(NdarrayMetadata<T, num_dimensions> a){
        auto iter_input = a.data_buffer.get();    
        
        array<size_t, num_dimensions> out_shape = a.shape;
        vector<T> output_allocated_memory(calc_size<size_t, num_dimensions>(out_shape));
        auto output = create_array<T, num_dimensions>(output_allocated_memory.data(), out_shape);    
        
        auto iter_output = output.data_buffer.get();
        
        for (size_t i =0; i<a.total_size;i++){
            iter_output[i] = __builtin_bswap64 (iter_input[i]);
            cout << iter_output[i] << " ";
        }
        return output;
    }

    // template<typename T, size_t num_dimensions> 
    // void clip(NdarrayMetadata<T, num_dimensions> a ,int64_t min,int64_t max){
        
    //     auto iter_input = a.data_buffer.get();

    //     for(size_t i=0;i<a.total_size;i++){
    //         if(iter_input[i] < min)
    //             iter_input[i] = min;
    //         if(iter_input[i] > max)
    //             iter_input[i] = max;
    //     }
    // }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions> clip(NdarrayMetadata<T, num_dimensions> Array ,int64_t min,int64_t max){    
	    auto output = copy(Array);
        auto iter_output = output.data_buffer.get();

        for(size_t i=0;i<Array.total_size;i++){
            if(iter_output[i] < min)
                iter_output[i] = min;
            if(iter_output[i] > max)
                iter_output[i] = max;
        }   
        return output;
    }


    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions> copy(NdarrayMetadata<T, num_dimensions> a){

        auto iter_input = a.data_buffer.get();   
        
        array<size_t, num_dimensions> out_shape = a.shape;
        vector<T> output_allocated_memory(calc_size<size_t, num_dimensions>(out_shape));
        auto output = create_array<T, num_dimensions>(output_allocated_memory.data(), out_shape);    
        
        auto iter_output = output.data_buffer.get();
        for(size_t i = 0;i<a.total_size;i++){
            iter_output[i] = iter_input[i];
        }
        return output;
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
    NdarrayMetadata<T , 1> flatten(NdarrayMetadata<T, num_dimensions> a){
        
        array<size_t, 1> out_shape = a.total_size;
        vector<int64_t> output_allocated_memory(calc_size<size_t, 1>(out_shape));
        auto output = create_array<int64_t, 1>(output_allocated_memory.data(), out_shape);    
        auto iter_input = a.data_buffer.get();
        auto iter_output = output.data_buffer.get();

        for (size_t i=0;i<a.total_size;i++)
            iter_output[i] = iter_input[i] ;

        return output;

    }

    template<typename T, size_t num_dimensions> 
    void fill(NdarrayMetadata<T, num_dimensions> a ,int64_t val){
        
        auto iter_input = a.data_buffer.get();

        for (size_t i=0;i<a.total_size;i++)
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
    T item(NdarrayMetadata<T, num_dimensions> a, array<T, num_dimensions> location){
        T output;
        size_t strides = 0;
        size_t offset = 0;
        size_t t = 0;
        while(strides < num_dimensions){
            offset += location[t]*a.strides[strides];
            strides++;
            t++;
        }
        return a.data_buffer.get()[offset];
    }

    template<typename T, size_t num_dimensions> 
    T max(NdarrayMetadata<T, num_dimensions> a){

        int64_t output = 0;
        auto input_iter = a.data_buffer.get();
        for(size_t i = 0;i<a.total_size;i++){
            if(output < input_iter[i])
                output = input_iter[i];
        }
        return output;
    }

    template<typename T, size_t num_dimensions> 
    T min(NdarrayMetadata<T, num_dimensions> a){

        auto output = 0;
        auto input_iter = a.data_buffer.get();
        for(size_t i = 0;i<a.total_size;i++){
            if(output > input_iter[i])
                output = input_iter[i];
        }
        return output;
    }

    template<typename T, size_t num_dimensions> 
    T mean(NdarrayMetadata<T, num_dimensions> a){
        auto output = (float)sum(a)/a.total_size;
        return output;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions> newbyteorder(NdarrayMetadata<T, num_dimensions> a){
        return byteswap(a);
    }


    // template<typename T, size_t num_dimensions> 
    // void put(NdarrayMetadata<T, num_dimensions> a, array<T, limit> ind, array<T, limit> val, string mode){
    //     auto input_iter = a.data_buffer.get();
    //     size_t i = 0;
    //     size_t ind_size = ind.size();
    //     size_t val_size = val.size();
        
    //     if(val_size == ind_size){
    //         if(mode == "wrap")
    //         {
    //             for(;i<val_size;i++){
    //                 input_iter[ind[i]] = val[i%limit];
    //             }
    //         } else if( mode == "clip") {
    //             for(;i<val_size;i++){
    //                 if(ind[i]> limit)
    //                     input_iter[limit-1] = val[i];
    //                 else
    //                     input_iter[ind[i]] = val[i];
    //             }
    //         }
    //     } else {
    //         cout << "Size of index array and value array is uneuqal";
    //         return;
    //     }
    // }


    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions> round(NdarrayMetadata<T, num_dimensions> Array, size_t decimals){
        // array<size_t,num_dimensions> output_shape = a.shape;
        // vector<int64_t> allocated_memory3(calc_size<size_t,num_dimensions>(output_shape));
        auto output = NdarrayMetadata<T,num_dimensions>(Array.shape);

        auto input_iter = Array.data_buffer.get();    
        auto output_iter = output.data_buffer.get();
        for(size_t i = 0;i<Array.total_size;i++){
                output_iter[i] = std::round(input_iter[i]);
        }
        return output;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T , 1> ravel(NdarrayMetadata<T, num_dimensions> a){
        
        array<size_t, 1> out_shape = a.total_size;
        vector<int64_t> output_allocated_memory(calc_size<size_t, 1>(out_shape));
        auto output = create_array<int64_t, 1>(output_allocated_memory.data(), out_shape);    
        auto iter_input = a.data_buffer.get();
        auto iter_output = output.data_buffer.get();

        for (size_t i=0;i<a.total_size;i++)
            iter_output[i] = iter_input[i] ;

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
    T sum(NdarrayMetadata<T, num_dimensions> a){

        size_t output = 0;
        auto input_iter = a.data_buffer.get();
        for(size_t i = 0;i<a.total_size;i++){
            output += input_iter[i];
        }
        return output;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions> swapaxes(NdarrayMetadata<T, num_dimensions> a, size_t axis1, size_t axis2){
        auto shape = a.shape;
        shape[axis1] = a.shape[axis2];
        shape[axis2] = a.shape[axis1];

        array<size_t,num_dimensions> output_shape = shape;
        vector<int64_t> allocated_memory3(calc_size<size_t,num_dimensions>(output_shape));
        auto output = create_array<int64_t,num_dimensions>(allocated_memory3.data(), output_shape);
        return output;
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions-1> squeeze(NdarrayMetadata<T, num_dimensions> a, size_t axis){
        
        // if(a.shape[axis] != 1)
        // {
        //     cout<< " Error, can't squeeze an axis whose value is not 1";
        //     return a;
        // } else {
            auto shape = removeArrayElement(a.shape,axis);  
            array<size_t,num_dimensions-1> output_shape = shape;
            vector<int64_t> allocated_memory3(calc_size<size_t,num_dimensions-1>(output_shape));
            auto output = create_array<int64_t,num_dimensions-1>(allocated_memory3.data(), output_shape);

            
        for(size_t i = 0;i<output.total_size;i++){
            output.data_buffer.get()[i] = a.data_buffer.get()[i];
        }

            return output;
        // }
    }

    template<typename T, size_t num_dimensions> 
    NdarrayMetadata<T, num_dimensions> transpose(NdarrayMetadata<T, num_dimensions> a){
        auto shape = a.shape;
        std::reverse(std::begin(shape),std::end(shape));

        array<size_t,num_dimensions> output_shape = shape;
        vector<int64_t> allocated_memory3(calc_size<size_t,num_dimensions>(output_shape));
        auto output = create_array<int64_t,num_dimensions>(allocated_memory3.data(), output_shape);

        
        auto iter_input = a.data_buffer.get();
        auto iter_output = output.data_buffer.get();
        for(size_t i = 0;i<a.total_size;i++){
            iter_output[i] = iter_input[i];
        }
        return output;
    }
}
#endif