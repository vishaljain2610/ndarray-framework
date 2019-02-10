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
	
	array<size_t, 3> shape3 = {3, 3, 3};
	cout << calc_size<size_t, 3>(shape3) << endl;
	vector<int64_t> allocated_memory3(calc_size<size_t, 3>(shape3));
	auto array3d = create_array<int64_t, 3>(allocated_memory3.data(), shape3);
	array3d(2, 0, 1) = 2;
    return 0;
}