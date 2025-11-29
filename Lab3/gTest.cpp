#include <gtest/gtest.h>
#include "include/sort.h"
#include <string>
#include <iostream>

class SortTest : public testing::Test {
protected:
  SortTest() {}

  int arr[8] = {6, 5, 3, 1, 8, 7, 2, 4};
};

TEST_F(SortTest, Less)
{
  print(arr, 8);
  sort(&arr[0], &arr[std::size(arr)-1], [](int a, int b) { return a < b; });
  print(arr, 8);
  for(int i = 0; i < std::size(arr); i++)
  {
    EXPECT_EQ(arr[i], i+1);
  }
}

TEST_F(SortTest, LessOrEq) 
{
  sort(&arr[0], &arr[std::size(arr)-1], [](int a, int b) { return a <= b; });
  for(int i = 0; i < std::size(arr); i++)
  {
    EXPECT_EQ(arr[i], i+1);
  }
} 