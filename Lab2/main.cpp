#include "include/Array.h"
#include <iostream>

int main()
{
    using namespace std;
    
    Array<int> a{};
    Array<int> b = a;
    
    for(int i = 0; i < 20; i++)
    {
        b.insert(i, i);
        b.print();
    }
    
    
    b.insert(5, 99);
    b.print();
        
    return 0;
}


