#include <gtest/gtest.h>
#include "include/Array.h"
#include <string>
#include <iostream>

class ArrayTest : public testing::Test
{
  protected:
  void SetUp() override
  {
  
  }
  void TearDown() override
  {
    
  }

  Array<int> aInt;
  Array<std::string> aString;
  Array<Array<int>> aArray;
};

TEST(ConstructorTest, DefaultConstructor)
{
  Array<int> a;
  EXPECT_NE(a.getArr(), nullptr);
}
TEST(ConstructorTest, IntParamConstructor)
{
  Array<int> a(5);
  EXPECT_EQ(a.getCapacity(), 5);
}


TEST(InsertTest, EndIntInsert)
{
  Array<int> a;
  for(int i = 0; i < 5; i++)
    a.insert(i+1);
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.getCapacity(), 8);
  EXPECT_EQ(a.getArr()[0], 1);
  EXPECT_EQ(a.getArr()[4], 5);
}
TEST(InsertTest, EndInsertMoreThanMaxCapacity)
{
  Array<int> a;
  for(int i = 0; i < 9; i++)
    a.insert(i+1);
  EXPECT_EQ(a.size(), 9);
  EXPECT_EQ(a.getCapacity(), 12);
  EXPECT_EQ(a.getArr()[0], 1);
  EXPECT_EQ(a.getArr()[8], 9);
}
TEST(InsertTest, EndStringInsert)
{
  Array<std::string> a;
  for(int i = 0; i < 5; i++)
    a.insert("asd_" + std::to_string(i+1));
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.getCapacity(), 8);
  EXPECT_EQ(a.getArr()[0], "asd_1");
  EXPECT_EQ(a.getArr()[4], "asd_5");
}
TEST(InsertTest, EndStringInsertMoreThanMaxCapacity)
{
  Array<std::string> a;
  for(int i = 0; i < 9; i++)
    a.insert("asd_" + std::to_string(i+1));
  EXPECT_EQ(a.size(), 9);
  EXPECT_EQ(a.getCapacity(), 12);
  EXPECT_EQ(a.getArr()[0], "asd_1");
  EXPECT_EQ(a.getArr()[8], "asd_9");
}


TEST(CopyTest, MoveConstructorWithEmpty)
{
  Array<int> a(5);
  Array<int> b(std::move(a));
  EXPECT_EQ(a.getArr(), nullptr);
  EXPECT_NE(b.getArr(), nullptr);
}
TEST(CopyTest, MoveConstructorInt)
{
  Array<int> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(i+1);
  
  Array<int> b(std::move(a));
  EXPECT_EQ(a.getArr(), nullptr);
  EXPECT_EQ(b.getArr()[0], 1);
  EXPECT_EQ(b.getArr()[8], 9);
}
TEST(CopyTest, MoveConstructorString)
{
  Array<std::string> a(5);
  for(int i = 0; i < 9; i++)
    a.insert("asd_" + std::to_string(i+1));
  
  Array<std::string> b(std::move(a));
  EXPECT_EQ(a.getArr(), nullptr);
  EXPECT_EQ(b.getArr()[0], "asd_1");
  EXPECT_EQ(b.getArr()[8], "asd_9");
}
TEST(CopyTest, CopyConstructorWithEmpty)
{
  Array<int> a(5);
  Array<int> b(a);
  EXPECT_NE(a.getArr(), nullptr);
  EXPECT_NE(b.getArr(), nullptr);
}
TEST(CopyTest, CopyConstructorInt)
{
  Array<int> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(i+1);
  
  Array<int> b(a);
  EXPECT_EQ(b.getArr()[0], a.getArr()[0]);
  EXPECT_EQ(b.getArr()[8], a.getArr()[8]);
}
TEST(CopyTest, CopyConstructorString)
{
  Array<std::string> a(5);
  for(int i = 0; i < 9; i++)
    a.insert("asd_" + std::to_string(i+1));
  
  Array<std::string> b(a);
  EXPECT_EQ(b.getArr()[0], a.getArr()[0]);
  EXPECT_EQ(b.getArr()[8], a.getArr()[8]);
}


// TEST(DestructorTest, Destr)
// {

// }


// TEST(AssigmentTest, MoveCopyAssigment)
// {

// }


// TEST(SubscriptOperatorTest, ReturnConst)
// {

// }
// TEST(SubscriptOperatorTest, ReturnNonConst)
// {

// }

// end insert
// !end insert

// remove