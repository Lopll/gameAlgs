#include "include/Array.h"
#include <iostream>
#include <string>

int main()
{
    using namespace std;
    
    Array<std::string> a(5);
  for(int i = 0; i < 9; i++)
  {
    a.insert(std::to_string(i+1));
  
  a.print();
  }      
    return 0;
}


