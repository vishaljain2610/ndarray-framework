#include <iostream>
#include <vector>
#include <numeric>

#include "ndarray.hpp"

using namespace std;

int main()
{	
	array<size_t, 3> shape3 = {3, 3, 3};
	// cout << calc_size<size_t, 3>(shape3) << endl;
	vector<int64_t> allocated_memory3(calc_size<size_t, 3>(shape3));
	auto array3d = create_array<int64_t, 3>(allocated_memory3.data(), shape3);
	
	array3d(2, 1, 1) = 2;
	// cout << "HERE " << array3d(2,1,1) << endl;
	auto array2d = array3d[2];
	auto array1d = array2d[1];
	auto array1d2 = array3d[2][1];
	// cout << "HERE " << array1d(1) << endl;
	// cout << "HERE " << array1d2(1) << endl;
    return 0;
}