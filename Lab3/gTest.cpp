#include <gtest/gtest.h>
#include "include/sort.h"
#include <string>
#include <iostream>

class SortTest : public testing::Test {
protected:
  SortTest() {}

  int arr[8] = {6, 5, 3, 1, 8, 7, 2, 4};
  int sorted[5] = {1, 2, 3, 4, 5};
  int same[10] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
  
  std::string arrS[8] = {"f","e", "c","a", "h", "g", "b", "d"};
  std::string arrSorted[8] = {"a", "b", "c", "d", "e", "f", "g", "h"};
  std::string sortedS[5] = {"a", "b", "c", "d", "e"};
  std::string sortedSorted[5] = {"a", "b", "c", "d", "e"};
  std::string sameS[10] = {"c", "a", "d", "a", "e", "i", "b", "f", "e", "c"};
  std::string sameSorted[10] = {"a", "a", "b", "c", "c", "d", "e", "e", "f", "i"};
};

TEST_F(SortTest, Less)
{
  sort(&arr[0], &arr[std::size(arr)-1], [](int a, int b) { return a < b; });
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

TEST_F(SortTest, LessSorted)
{
  sort(&sorted[0], &sorted[std::size(sorted)-1], [](int a, int b) { return a < b; });
  for(int i = 0; i < std::size(sorted); i++)
  {
    EXPECT_EQ(sorted[i], i+1);
  }
}

TEST_F(SortTest, LessOrEqSorted) 
{
  sort(&sorted[0], &sorted[std::size(sorted)-1], [](int a, int b) { return a <= b; });
  for(int i = 0; i < std::size(sorted); i++)
  {
    EXPECT_EQ(sorted[i], i+1);
  }
}

TEST_F(SortTest, GreaterInvSorted)
{
  int size = std::size(sorted);
  sort(&sorted[0], &sorted[size-1], [](int a, int b) { return a > b; });
  for(int i = 0; i < size; i++)
  {
    EXPECT_EQ(sorted[i], size-i);
  }
}

TEST_F(SortTest, GreaterOrEqInvSorted) 
{
  int size = std::size(sorted);
  sort(&sorted[0], &sorted[size-1], [](int a, int b) { return a >= b; });
  for(int i = 0; i < size; i++)
  {
    EXPECT_EQ(sorted[i], size-i);
  }
} 

TEST_F(SortTest, LessSame)
{
  int size = std::size(same);
  sort(&same[0], &same[size-1], [](int a, int b) { return a < b; });
  EXPECT_EQ(same[0], 1);
  EXPECT_EQ(same[1], 1);
  EXPECT_EQ(same[2], 2);
  EXPECT_EQ(same[3], 3);
  EXPECT_EQ(same[4], 3);
  EXPECT_EQ(same[5], 4);
  EXPECT_EQ(same[6], 5);
  EXPECT_EQ(same[7], 5);
  EXPECT_EQ(same[8], 6);
  EXPECT_EQ(same[9], 9);
}

TEST_F(SortTest, LessOrEqSame) 
{
  int size = std::size(same);
  sort(&same[0], &same[size-1], [](int a, int b) { return a <= b; });
  EXPECT_EQ(same[0], 1);
  EXPECT_EQ(same[1], 1);
  EXPECT_EQ(same[2], 2);
  EXPECT_EQ(same[3], 3);
  EXPECT_EQ(same[4], 3);
  EXPECT_EQ(same[5], 4);
  EXPECT_EQ(same[6], 5);
  EXPECT_EQ(same[7], 5);
  EXPECT_EQ(same[8], 6);
  EXPECT_EQ(same[9], 9);
} 

TEST(UniqueTests, OneElement)
{
  int arr[1] = {0};
  sort(&arr[0], &arr[0], [](int a, int b) { return a < b; });
  EXPECT_EQ(arr[0], 0);
}

TEST(UniqueTests, Empty)
{
  int arr[0];
  EXPECT_NO_THROW(sort(&arr[0], &arr[0], [](int a, int b) { return a < b; }));
}

TEST(UniqueTests, AllSameLess)
{
  int size = 7;
  int arr[size];
  for(int i = 0; i < size; i++)
  {
    arr[i] = size;
  }
  sort(&arr[0], &arr[size-1], [](int a, int b) { return a < b; });
  for(int i = 0; i < size; i++)
  {
    EXPECT_EQ(arr[i], size);
  }
}

TEST(UniqueTests, AllSameLessOrEq)
{
  int size = 7;
  int arr[size];
  for(int i = 0; i < size; i++)
  {
    arr[i] = size;
  }
  sort(&arr[0], &arr[size-1], [](int a, int b) { return a <= b; });
  for(int i = 0; i < size; i++)
  {
    EXPECT_EQ(arr[i], size);
  }
}

TEST(UniqueTests, AllSameLessBig)
{
  int size = 100000;
  int arr[size];
  for(int i = 0; i < size; i++)
  {
    arr[i] = 1;
  }
  sort(&arr[0], &arr[size-1], [](int a, int b) { return a <= b; });
  for(int i = 0; i < size; i++)
  {
    EXPECT_EQ(arr[i], 1);
  }
}











TEST_F(SortTest, LessString)
{
  sort(&arrS[0], &arrS[std::size(arrS)-1], [](std::string a, std::string b) { return a[0] < b[0]; });
  for(int i = 0; i < std::size(arrS); i++)
  {
    EXPECT_EQ(arrS[i], arrSorted[i]);
  }
}

TEST_F(SortTest, LessOrEqString)
{
  sort(&arrS[0], &arrS[std::size(arrS)-1], [](std::string a, std::string b) { return a[0] <= b[0]; });
  for(int i = 0; i < std::size(arrS); i++)
  {
    EXPECT_EQ(arrS[i], arrSorted[i]);
  }
}
TEST_F(SortTest, LessStringSorted)
{
  sort(&sortedS[0], &sortedS[std::size(sortedS)-1], [](std::string a, std::string b) { return a[0] < b[0]; });
  for(int i = 0; i < std::size(sortedS); i++)
  {
    EXPECT_EQ(sortedS[i], sortedSorted[i]);
  }
}

TEST_F(SortTest, LessOrEqStringSorted) 
{
  sort(&sortedS[0], &sortedS[std::size(sortedS)-1], [](std::string a, std::string b) { return a[0] <= b[0]; });
  for(int i = 0; i < std::size(sortedS); i++)
  {
    EXPECT_EQ(sortedS[i], sortedSorted[i]);
  }
}

TEST_F(SortTest, GreaterStringInvSorted)
{
  int size = std::size(sortedS);
  sort(&sortedS[0], &sortedS[size-1], [](std::string a, std::string b) { return a[0] > b[0]; });
  for(int i = 0; i < size; i++)
  {
    EXPECT_EQ(sortedS[i], sortedSorted[size-i-1]);
  }
}

TEST_F(SortTest, GreaterOrEqStringInvSorted) 
{
  int size = std::size(sortedS);
  sort(&sortedS[0], &sortedS[size-1], [](std::string a, std::string b) { return a[0] >= b[0]; });
  for(int i = 0; i < size; i++)
  {
    EXPECT_EQ(sortedS[i], sortedSorted[size-i-1]);
  }
} 

TEST_F(SortTest, LessStringSame)
{
  int size = std::size(sameS);
  sort(&sameS[0], &sameS[size-1], [](std::string a, std::string b) { return a[0] < b[0]; });
  for(int i = 0; i < size; i++)
  {
    EXPECT_EQ(sameS[i], sameSorted[i]);
  }
}

TEST_F(SortTest, LessOrEqStringSame) 
{
  int size = std::size(sameS);
  sort(&sameS[0], &sameS[size-1], [](std::string a, std::string b) { return a[0] <= b[0]; });
  for(int i = 0; i < size; i++)
  {
    EXPECT_EQ(sameS[i], sameSorted[i]);
  }
} 

TEST(UniqueStringTests, OneElement)
{
  std::string arr[1] = {"a"};
  sort(&arr[0], &arr[0], [](std::string a, std::string b) { return a[0] < b[0]; });
  EXPECT_EQ(arr[0], "a");
}

TEST(UniqueStringTests, AllSameLess)
{
  int size = 7;
  std::string arr[size];
  for(int i = 0; i < size; i++)
  {
    arr[i] = "x";
  }
  sort(&arr[0], &arr[size-1], [](std::string a, std::string b) { return a[0] < b[0]; });
  for(int i = 0; i < size; i++)
  {
    EXPECT_EQ(arr[i], "x");
  }
}

TEST(UniqueStringTests, AllSameLessOrEq)
{
  int size = 7;
  std::string arr[size];
  for(int i = 0; i < size; i++)
  {
    arr[i] = "x";
  }
  sort(&arr[0], &arr[size-1], [](std::string a, std::string b) { return a[0] <= b[0]; });
  for(int i = 0; i < size; i++)
  {
    EXPECT_EQ(arr[i], "x");
  }
}

// TEST(UniqueStringTests, AllSameLessBig)
// {
//   int size = 100000;
//   std::string* arr = new std::string[size];
//   for(int i = 0; i < size; i++)
//   {
//     arr[i] = "z";
//   }
//   sort(&arr[0], &arr[size-1], [](std::string a, std::string b) { return a[0] <= b[0]; });
//   for(int i = 0; i < size; i++)
//   {
//     EXPECT_EQ(arr[i], "z");
//   }
//   delete[] arr;
// }
