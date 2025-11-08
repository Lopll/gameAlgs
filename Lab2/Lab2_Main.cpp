#include "include/Array.h"
#include <iostream>
#include <string>

int main()
{
    using namespace std;
    
    Array<string> a(5);
  for(int i = 0; i < 9; i++)
  {
    a.insert("0");
    a.print();
  }      
  // a.remove(1);
  // a.print();
    return 0;
}


