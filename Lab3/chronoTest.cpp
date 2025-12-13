#include "include/sort.h"
#include <iostream>
#include <chrono>

void timeInsertSort(int* arr, int size)
{
    using namespace std::chrono;
    
    auto start = high_resolution_clock::now();
    
    sort(&arr[0], &arr[size-1], [](int a, int b) { return a <= b; });
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end-start);
    std::cout << "Insertion sort (size = "<< size << ") took " << duration.count() << " nanoseconds\n";
}

void timeQuickSort(int* arr, int size)
{
    using namespace std::chrono;
    
    auto start = high_resolution_clock::now();
    
    insertionSort(&arr[0], &arr[size-1], [](int a, int b) { return a <= b; });
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end-start);
    std::cout << "Quick sort (size = "<< size << ") took " << duration.count() << " nanoseconds\n";
}

int main() {
    
    int size = 2;
    for(int i = 0; size <= 1000; i++)
    {
        int arr[size];
        for(int j = 0; j < size; j++)
        {
          arr[j] = 1;
        }
        timeInsertSort(arr, size);
        timeQuickSort(arr, size);
        size+=2;
    }
    
    return 0;
}
