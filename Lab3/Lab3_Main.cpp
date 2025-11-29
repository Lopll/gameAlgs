#include <iostream>
#include "include/sort.h"

int main()
{   
    int arr[] = {6, 5, 3, 1, 8, 7, 2, 4};
    print(arr, 8);
    sort(&arr[0], &arr[7], [](int a, int b) { return a < b; });
    print(arr, 8);
    return 0;
}