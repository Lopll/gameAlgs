#include "include/Array.h"
#include <iostream>

int main()
{
    using namespace std;
    
    Array<int> a1;
    Array<int> a2(16);
    Array<int> a3(a2);
    
    cout << a1.capacity << endl;
    cout << a2.capacity << endl;
    cout << a3.capacity << endl;
    return 0;
}