#include <gtest/gtest.h>
#include "include/Array.h"
#include <string>
#include <iostream>

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


TEST(AssigmentTest, MoveCopyAssigment)
{
  Array<int> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(i+1);
  
  Array<int> b = a;
  EXPECT_EQ(b[0], a[0]);
  EXPECT_NE(a.getArr(), nullptr);
  Array<int> c = std::move(a);
  EXPECT_EQ(a.getArr(), nullptr);
  EXPECT_EQ(c[0], 1);
  
  Array<std::string> d(5);
  for(int i = 0; i < 9; i++)
    d.insert(std::to_string(i+1));
    
  Array<std::string> e = d;
  EXPECT_EQ(e[0], d[0]);
  EXPECT_NE(d.getArr(), nullptr);
  Array<std::string> f = std::move(d);
  EXPECT_EQ(d.getArr(), nullptr);
  EXPECT_EQ(f[0], "1");
}


TEST(SubscriptOperatorTest, ReturnNonConstInt)
{
  Array<int> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(i+1);
  EXPECT_EQ(a[0], 1);
}
TEST(SubscriptOperatorTest, ReturnNonConstString)
{
  Array<std::string> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(std::to_string(i+1));
  EXPECT_EQ(a[0], "1");
}
TEST(SubscriptOperatorTest, ReturnConstInt)
{
  Array<int> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(i+1);
  const Array<int> b = std::move(a);
  const int val = b[0];
  EXPECT_EQ(val, 1);
}
TEST(SubscriptOperatorTest, ReturnConstString)
{
  Array<std::string> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(std::to_string(i+1));
  const Array<std::string> b = std::move(a);
  const std::string val = b[0];
  EXPECT_EQ(val, "1");
}


TEST(RemoveTest, RemoveInt)
{
  Array<int> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(i+1);
  a.remove(0);
  EXPECT_EQ(a.size(), 8);
  EXPECT_EQ(a[0], 2);
}
TEST(RemoveTest, RemoveString)
{
  Array<std::string> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(std::to_string(i+1));
  a.remove(0);
  EXPECT_EQ(a.size(), 8);
  EXPECT_EQ(a[0], "2");
}
TEST(RemoveTest, RemoveStringMiddle)
{
  Array<std::string> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(std::to_string(i+1));
  a.remove(5);
  EXPECT_EQ(a.size(), 8);
  EXPECT_EQ(a[5], "7");
}


TEST(InsertTest, InsertAfterRemoveString)
{
  Array<std::string> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(std::to_string(i+1));
  a.remove(0);
  a.insert("aa");
  EXPECT_EQ(a.size(), 9);
  EXPECT_EQ(a[8], "aa");
}

TEST(IteratorTest, BeginIterator)
{
  Array<int> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(i+1);
  Array<int>::Iterator iter = a.iterator();  
  EXPECT_EQ(iter.get(), 1);
  EXPECT_TRUE(iter.hasNext());
  iter.next();
  EXPECT_EQ(iter.get(), 2);
  iter.set(54);
  EXPECT_EQ(iter.get(), 54);
}
TEST(IteratorTest, ReverseIterator)
{
  Array<int> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(i+1);
  Array<int>::Iterator iter = a.reverseIterator();  
  EXPECT_EQ(iter.get(), 9);
  EXPECT_FALSE(iter.hasNext());
}
TEST(IteratorTest, BeginConstIterator)
{
  Array<int> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(i+1);
  const Array<int> b = a;
  Array<int>::ConstIterator iter = b.iterator();  
  EXPECT_EQ(iter.get(), 1);
  EXPECT_TRUE(iter.hasNext());
  iter.next();
  EXPECT_EQ(iter.get(), 2);
}
TEST(IteratorTest, ReverseConstIterator)
{
  Array<int> a(5);
  for(int i = 0; i < 9; i++)
    a.insert(i+1);
  const Array<int> b = a;
  Array<int>::ConstIterator iter = b.reverseIterator();  
  EXPECT_EQ(iter.get(), 9);
  EXPECT_FALSE(iter.hasNext());
}

// TEST(InsertTest, InsertAfterAssigment)
// {
//   Array<std::string> a(5);
//   for(int i = 0; i < 9; i++)
//     a.insert(std::to_string(i+1));
//   Array<std::string> b = a;
//   a.insert("aa");
//   EXPECT_EQ(a[9], "aa");
//   b.insert("bb");
//   EXPECT_EQ(b[9], "bb");
//   Array<std::string> c = std::move(a);
//   c.insert("cc");
//   EXPECT_EQ(c[9], "aa");
//   EXPECT_EQ(c[10], "cc");
// }

// TEST(RemoveTest, RemoveAfterAssigment)
// {
//   Array<std::string> a(5);
//   for(int i = 0; i < 9; i++)
//     a.insert(std::to_string(i+1));
//   Array<std::string> b = a;
//   a.remove(4);
//   EXPECT_EQ(a[4], "6");
//   b.remove(0);
//   EXPECT_EQ(b[0], "2");
//   Array<std::string> c = std::move(a);
//   c.remove(6);
//   EXPECT_EQ(c[6], "9");
// }

//iter + const
//reverse iter + const