#include <iostream>
using namespace std;
// Driver code 
int main() 
{ 
    int testcase;
    while(testcase--!=0){
        int64_t sum,l1,l2,price;
        cin >> sum >> l1 >> l2 >> price;
        cout << (price*(l1+l2)*sum/l2) << endl;
    }
    return 0; 
} 