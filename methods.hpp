#ifndef METHODS_H
#define METHODS_H

#include <iostream>
#include <array>
#include <algorithm>
#include <memory>
#include <cstdarg>
#include<string.h> 

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

template<typename T, size_t num_dimensions> 
bool all(NdarrayMetadata<T, num_dimensions> a){

    bool output = true;
    auto input_iter = a.data_buffer.get();
    for(size_t i = 0;i<a.total_size;i++){
		if(input_iter[i] == 0 || input_iter[i] == false)
            output = false;
	}
    return output;
}

template<typename T, size_t num_dimensions> 
bool any(NdarrayMetadata<T, num_dimensions> a){

    bool output = false;
    auto input_iter = a.data_buffer.get();
    for(size_t i = 0;i<a.total_size;i++){
		if(input_iter[i] != 0 || input_iter[i] != false)
            output = true;
	}
    return output;
}

template<typename T, size_t num_dimensions> 
T argmax(NdarrayMetadata<T, num_dimensions> a){

    auto output = 0;
    auto input_iter = a.data_buffer.get();
    for(size_t i = 0;i<a.total_size;i++){
        if(output < input_iter[i])
		    output = i;
	}
    return output;
}

template<typename T, size_t num_dimensions> 
T argmin(NdarrayMetadata<T, num_dimensions> a){

    auto output = 0;
    auto input_iter = a.data_buffer.get();
    for(size_t i = 0;i<a.total_size;i++){
        if(output > input_iter[i])
		    output = i;
	}
    return output;
}

template<typename T, size_t num_dimensions> 
NdarrayMetadata<T, num_dimensions> astype(NdarrayMetadata<T, num_dimensions> a ,string dtype, bool copy){
    auto iter_input = a.data_buffer.get();    
    	array<size_t, num_dimensions> out_shape = a.shape;
        vector<int64_t> output_allocated_memory(calc_size<size_t, num_dimensions>(out_shape));
    auto	output = create_array<int64_t, num_dimensions>(output_allocated_memory.data(), out_shape);    
    
    auto iter_output = output.data_buffer.get();
    for (size_t i =0; i<a.total_size;i++){
        if(dtype == "int")
            iter_output[i] = (int)iter_input[i]; 
        else if (dtype == "float") 
            iter_output[i] = (float)iter_input[i];
        else if (dtype == "double")
            iter_output[i] = (double)iter_input[i];
        else
            iter_output[i] = to_string(iter_input[i]);
    }
    return output;
}

template<typename T, size_t num_dimensions> 
NdarrayMetadata<T, num_dimensions> byteswap(NdarrayMetadata<T, num_dimensions> a){
    auto iter_input = a.data_buffer.get();    
    
    array<size_t, num_dimensions> out_shape = a.shape;
    vector<int64_t> output_allocated_memory(calc_size<size_t, num_dimensions>(out_shape));
    auto output = create_array<int64_t, num_dimensions>(output_allocated_memory.data(), out_shape);    
    
    auto iter_output = output.data_buffer.get();
    
    for (size_t i =0; i<a.total_size;i++){
        iter_output[i] = __builtin_bswap32 (iter_input[i]);
        cout << iter_output[i] << " ";
    }
    return output;
}

template<typename T, size_t num_dimensions> 
void clip(NdarrayMetadata<T, num_dimensions> a ,int64_t min,int64_t max){
    
    auto iter_input = a.data_buffer.get();

    for(size_t i=0;i<a.total_size;i++){
        if(iter_input[i] < min)
            iter_input[i] = min;
        if(iter_input[i] > max)
            iter_input[i] = max;
    }
}

template<typename T, size_t num_dimensions> 
NdarrayMetadata<T, num_dimensions> copy(NdarrayMetadata<T, num_dimensions> a){

    auto iter_input = a.data_buffer.get();   
    
    array<size_t, num_dimensions> out_shape = a.shape;
    vector<int64_t> output_allocated_memory(calc_size<size_t, num_dimensions>(out_shape));
    auto output = create_array<int64_t, num_dimensions>(output_allocated_memory.data(), out_shape);    
    
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

    auto output = 0;
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
NdarrayMetadata<T, num_dimensions> round(NdarrayMetadata<T, num_dimensions> a, size_t decimals){
    array<size_t,num_dimensions> output_shape = a.shape;
	vector<int64_t> allocated_memory3(calc_size<size_t,num_dimensions>(output_shape));
	auto output = create_array<int64_t,num_dimensions>(allocated_memory3.data(), output_shape);

    auto input_iter = a.data_buffer.get();    
    auto output_iter = output.data_buffer.get();
    for(size_t i = 0;i<a.total_size;i++){
		    output_iter[i] = round(input_iter[i]);
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

#endif