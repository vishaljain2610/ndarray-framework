#include <iostream>
#include <vector>
#include <numeric>

#include "ndarray.hpp"

using namespace std;

int main()
{
    array<size_t, 2> shape = {16, 16};
	vector<int64_t> allocated_memory(calc_size<size_t, 2>(shape));
	auto array2d = create_array<int64_t, 2>(allocated_memory.data(), shape);
	array<size_t, 4> shape4 = {16, 16, 3, 2};
	vector<int64_t> allocated_memory4(calc_size<size_t, 4>(shape4));
	auto array4d = create_array<int64_t, 4>(allocated_memory4.data(), shape4);
    return 0;
}