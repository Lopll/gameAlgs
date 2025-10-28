#include "include/Array.h"
#include <iostream>
#include <string>

int main()
{
    using namespace std;
    
    Array<string> a;
    for (int i = 0; i < 9; ++i)
        a.insert(to_string(i + 1));
    a.print();
    // for (int i = 0; i < a.size(); ++i)
        // a[i] *= 2;
    // for (auto it = a.iterator(); it.hasNext(); it.next())
        // std::cout << it.get() << std::endl;
        
    return 0;
}


