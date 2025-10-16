#include "include/Array.h"
#include <iostream>

int main()
{
    using namespace std;
    
    Array<int> a1;
    Array<int> a2(a1);
    Array<int> a3(std::move(a1));
    
    // cout << a1.capacity << endl;
    // cout << a2.capacity << endl;
    // cout << a3.capacity << endl;
    return 0;
}