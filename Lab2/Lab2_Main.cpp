#include "include/Array.h"
#include <iostream>
#include <string>

int main()
{
    using namespace std;
    
    Array<Array<int>> a(5);
  for(int i = 0; i < 3; i++)
  {
    a.insert(Array<int>(i));
  
  // a.print();
  }      
  a.remove(1);
  // a.print();
  std::cout<<"EndRemove\n";
    return 0;
}


