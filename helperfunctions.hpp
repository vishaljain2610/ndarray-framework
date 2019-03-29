#ifndef HELPERFUNCTION_H
#define HELPERFUNCTION_H

#include <iostream>
#include <array>
#include <algorithm>
#include <memory>
#include <cmath>
#include <cstdarg>
#include <string.h> 
#include "slice.hpp"
#include "ndarray.hpp"
#include "arithematic.hpp"
// #include "helperfunctions.hpp"
// #include "methods.hpp"
namespace numc_hf {
    template<typename T, size_t num_dimensions> 
    array<T, (num_dimensions-1)> removeArrayElement(array<T, num_dimensions> a, size_t index){
        array<T, (num_dimensions-1)> output;
        for(size_t i =0,j=0;i<a.size();i++)
            {          
                if(i!=index)
                    output[j++] = a[i];
            }
        return output;
    }
}
#endif