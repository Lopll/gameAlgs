#include <iostream>
#include <string>
#include "include/sort.h"

int main()
{   
    // int same[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::string same[3] = {"b", "A", "a"};
    // int same[8] = {6, 5, 3, 1, 8, 7, 2, 4};
    int size = std::size(same);
    print(&same[0], &same[size-1]);
    insertionSort(&same[0], &same[size-1], [](std::string a, std::string b) { return a[0] < b[0]; });
    print(&same[0], &same[size-1]);
    return 0;
}