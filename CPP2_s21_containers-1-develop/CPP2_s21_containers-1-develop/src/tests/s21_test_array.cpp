#include <gtest/gtest.h>

#include "../array/s21_array.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr.size(), 5);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], i + 1);
  }
}

TEST(ArrayTest, InitializerListConstructorThrow) {
  EXPECT_THROW((s21::array<int, 3>{1, 2, 3, 4}), std::out_of_range);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 4> arr1 = {4, 3, 2, 1};
  s21::array<int, 4> arr2(arr1);

  EXPECT_EQ(arr1.size(), arr2.size());
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2(std::move(arr1));

  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, MoveAssignment) {
  s21::array<int, 4> arr1 = {4, 3, 2, 1};
  s21::array<int, 4> arr2;
  arr2 = std::move(arr1);

  EXPECT_EQ(arr2[0], 4);
  EXPECT_EQ(arr2[1], 3);
  EXPECT_EQ(arr2[2], 2);
  EXPECT_EQ(arr2[3], 1);
}

TEST(ArrayTest, AtMethod) {
  s21::array<int, 3> arr = {10, 20, 30};
  EXPECT_EQ(arr.at(0), 10);
  EXPECT_EQ(arr.at(1), 20);
  EXPECT_EQ(arr.at(2), 30);
}

TEST(ArrayTest, AtMethodThrow) {
  s21::array<int, 3> arr;
  EXPECT_THROW(arr.at(3), std::out_of_range);
  EXPECT_THROW(arr.at(-1), std::out_of_range);
}

TEST(ArrayTest, OperatorBrackets) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);

  arr[1] = 10;
  EXPECT_EQ(arr[1], 10);
}

TEST(ArrayTest, FrontMethod) {
  s21::array<int, 3> arr1 = {5, 10, 15};
  EXPECT_EQ(arr1.front(), 5);

  s21::array<char, 2> arr2 = {'a', 'b'};
  EXPECT_EQ(arr2.front(), 'a');
}

TEST(ArrayTest, BackMethod) {
  s21::array<int, 4> arr1 = {5, 10, 15, 20};
  EXPECT_EQ(arr1.back(), 20);

  s21::array<char, 3> arr2 = {'x', 'y', 'z'};
  EXPECT_EQ(arr2.back(), 'z');
}

TEST(ArrayTest, DataMethod) {
  s21::array<int, 3> arr = {1, 2, 3};
  int* ptr = arr.data();
  EXPECT_EQ(ptr[0], 1);
  EXPECT_EQ(ptr[1], 2);
  EXPECT_EQ(ptr[2], 3);

  ptr[1] = 10;
  EXPECT_EQ(arr[1], 10);
}

TEST(ArrayTest, BeginEndMethods) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  int sum = 0;
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 15);
}

TEST(ArrayTest, CBeginCEndMethods) {
  const s21::array<int, 4> arr = {4, 3, 2, 1};
  int product = 1;
  for (auto it = arr.cbegin(); it != arr.cend(); ++it) {
    product *= *it;
  }
  EXPECT_EQ(product, 24);
}

TEST(ArrayTest, EmptyMethod) {
  s21::array<int, 0> arr0;
  EXPECT_TRUE(arr0.empty());

  s21::array<int, 1> arr1;
  EXPECT_FALSE(arr1.empty());
}

TEST(ArrayTest, SizeMethod) {
  s21::array<int, 0> arr0;
  EXPECT_EQ(arr0.size(), 0);

  s21::array<int, 5> arr5;
  EXPECT_EQ(arr5.size(), 5);

  s21::array<double, 100> arr100;
  EXPECT_EQ(arr100.size(), 100);
}

TEST(ArrayTest, MaxSizeMethod) {
  s21::array<int, 0> arr0;
  EXPECT_EQ(arr0.max_size(), 0);

  s21::array<int, 5> arr5;
  EXPECT_EQ(arr5.max_size(), 5);

  s21::array<double, 100> arr100;
  EXPECT_EQ(arr100.max_size(), 100);
}

TEST(ArrayTest, SwapMethod) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2 = {4, 5, 6};

  arr1.swap(arr2);

  EXPECT_EQ(arr1[0], 4);
  EXPECT_EQ(arr1[1], 5);
  EXPECT_EQ(arr1[2], 6);

  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
}

TEST(ArrayTest, FillMethod) {
  s21::array<int, 5> arr;
  arr.fill(42);

  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 42);
  }

  s21::array<std::string, 3> str_arr;
  str_arr.fill("test");
  for (size_t i = 0; i < str_arr.size(); ++i) {
    EXPECT_EQ(str_arr[i], "test");
  }
}

TEST(ArrayTest, ZeroSizeArray) {
  s21::array<int, 0> arr;
  EXPECT_TRUE(arr.empty());
  EXPECT_EQ(arr.size(), 0);
  EXPECT_EQ(arr.max_size(), 0);
  EXPECT_THROW(arr.at(0), std::out_of_range);
}

TEST(ArrayTest, IteratorOperations) {
  s21::array<int, 4> arr = {10, 20, 30, 40};
  auto it = arr.begin();

  EXPECT_EQ(*it, 10);
  ++it;
  EXPECT_EQ(*it, 20);
  it += 2;
  EXPECT_EQ(*it, 40);
  --it;
  EXPECT_EQ(*it, 30);
  it--;
  EXPECT_EQ(*it, 20);
}

TEST(ArrayTest, DifferentTypes) {
  s21::array<double, 3> d_arr = {1.1, 2.2, 3.3};
  EXPECT_DOUBLE_EQ(d_arr[0], 1.1);
  EXPECT_DOUBLE_EQ(d_arr.at(1), 2.2);

  s21::array<char, 2> c_arr = {'a', 'b'};
  EXPECT_EQ(c_arr.front(), 'a');
  EXPECT_EQ(c_arr.back(), 'b');

  s21::array<std::string, 2> s_arr = {"hello", "world"};
  EXPECT_EQ(s_arr[0], "hello");
  EXPECT_EQ(s_arr.at(1), "world");
}