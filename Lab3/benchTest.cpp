#include "include/nanobench.h"
#include "include/sort.h"
#include <atomic>
#include <iostream>


int main() {
    int size = 100000;
      int arr[size];
      for(int i = 0; i < size; i++)
      {
        arr[i] = 1;
      }
    ankerl::nanobench::Bench().run("MegaSortTest", [&]
    {
        sort(&arr[0], &arr[size-1], [](int a, int b) { return a <= b; });
    });
    return 0;
}
