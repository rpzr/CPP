#include <gtest/gtest.h>

#include <list>
#include <stdexcept>

#include "../list/s21_list.h"
#include "../queue/s21_queue.h"
#include "../stack/s21_stack.h"
#include "../vector/s21_vector.h"

TEST(Part3, ListInsertMany1) {
  s21::list<int> l;
  l.push_back(1);
  l.push_back(4);
  auto it = l.insert_many(++l.begin(), 2, 3);
  EXPECT_EQ(l.size(), 4);
  EXPECT_EQ(*it, 4);
}

TEST(Part3, ListInsertManyBack) {
  s21::list<int> myList = {1, 2};
  myList.insert_many_back(3, 4);
  EXPECT_EQ(myList.size(), 4);
  EXPECT_EQ(myList.back(), 4);
}

TEST(Part3, ListInsertManyFront) {
  // Создаем список с начальными значениями
  s21::list<int> myList = {3, 4};

  // Вставляем несколько элементов в начало
  myList.insert_many_front(1, 2);

  // Проверяем размер списка
  EXPECT_EQ(myList.size(), 4);

  // Проверяем порядок элементов
  auto it = myList.begin();
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);

  // Проверяем, что больше нет элементов в списке
  ++it;
  EXPECT_EQ(it, myList.end());
}

TEST(Part3, ListInsertMany) {
  s21::list<int> myList = {1, 4};
  auto it = myList.begin();
  ++it;
  myList.insert_many(it, 2, 3);
  EXPECT_EQ(myList.size(), 4);
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 4);
  it = myList.begin();
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(Part3, VectorInsertManyBack_1) {
  s21::vector<int> vector{1, 2, 3};
  std::vector<int> original{1, 2, 3};
  vector.insert_many_back(1, 2, 3);
  original.insert(original.end(), {1, 2, 3});
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  for (int i = 0; i < 6; ++i) EXPECT_EQ(vector.at(i), original.at(i));
}

TEST(Part3, VectorInsertManyBack_2) {
  s21::vector<int> vector;
  std::vector<int> original;
  vector.insert_many_back(1, 2, 3);
  original.insert(original.end(), {1, 2, 3});
  EXPECT_EQ(vector.size(), original.size());
  for (int i = 0; i < 3; ++i) EXPECT_EQ(vector.at(i), original.at(i));
}

TEST(Part3, VectorInsertManyBack_3) {
  s21::vector<int> vector(50);
  std::vector<int> original(50);
  vector.insert_many_back(1, 2, 3);
  original.insert(original.end(), {1, 2, 3});
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  for (int i = 0; i < 53; ++i) EXPECT_EQ(vector.at(i), original.at(i));
}

TEST(Part3, VectorInsertMany_1) {
  s21::vector<int> vector{1, 2, 3};
  std::vector<int> original{1, 2, 3};
  auto it_vector = vector.insert_many(vector.cbegin() + 1, 8, 3, 2, 4, 5);
  auto it_original = original.insert(original.cbegin() + 1, {8, 3, 2, 4, 5});
  for (size_t i = 0; i < vector.size(); ++i)
    EXPECT_EQ(vector.at(i), original.at(i));
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(*it_vector, *it_original);
}

TEST(Part3, VectorInsertMany_2) {
  s21::vector<int> vector;
  std::vector<int> original;
  auto it_vector = vector.insert_many(vector.cend(), 8, 3, 2, 4, 5);
  auto it_original = original.insert(original.cend(), {8, 3, 2, 4, 5});
  for (size_t i = 0; i < vector.size(); ++i) {
    EXPECT_EQ(vector.at(i), original.at(i));
  }
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(*it_vector, *it_original);
}

TEST(Part3, VectorInsertMany_4) {
  s21::vector<int> vector;
  std::vector<int> original;
  auto it_vector = vector.insert_many(vector.cend(), 8);
  auto it_original = original.insert(original.cend(), {8});
  for (size_t i = 0; i < vector.size(); ++i) {
    EXPECT_EQ(vector.at(i), original.at(i));
  }
  EXPECT_EQ(vector.size(), original.size());
  EXPECT_EQ(vector.capacity(), original.capacity());
  EXPECT_EQ(*it_vector, *it_original);
}

TEST(Part3, VectorInsertMany_3) {
  s21::vector<int> vector{1, 2, 3};
  EXPECT_THROW(vector.insert_many(vector.cend() + 1, 5, 6), std::out_of_range);
  EXPECT_THROW(vector.insert_many(vector.cbegin() - 1, 5, 6),
               std::out_of_range);
}

TEST(Part3, QueueInsertManyBack_1) {
  s21::queue<int> our_queue_int;
  our_queue_int.insert_many_back(1, 2, 3);
  EXPECT_EQ(our_queue_int.front(), 1);
  EXPECT_EQ(our_queue_int.back(), 3);
}

TEST(Part3, QueueInsertManyBack_2) {
  s21::queue<int> our_queue_int({111, 4, 5, 6});
  our_queue_int.insert_many_back(1, 2, 3);
  EXPECT_EQ(our_queue_int.front(), 111);
  EXPECT_EQ(our_queue_int.back(), 3);
  EXPECT_EQ(our_queue_int.size(), 7);
}

TEST(Part3, QueueInsertManyBack_3) {
  s21::queue<int> our_queue_int({111, 4, 5, 6});
  our_queue_int.pop();
  our_queue_int.insert_many_back(0);
  ASSERT_EQ(our_queue_int.back(), 0);
  ASSERT_EQ(our_queue_int.size(), 4);
}

TEST(Part3, StackInsertManyBack_1) {
  s21::stack<int> stack({111, 4, 5, 6});
  stack.insert_many_back(0, -3, -33, -55);
  ASSERT_EQ(stack.top(), -55);
  ASSERT_EQ(stack.size(), 8);
}

TEST(Part3, StackInsertManyBack_2) {
  s21::stack<int> stack;
  stack.insert_many_back(111, 4, 5, 6);
  ASSERT_EQ(stack.top(), 6);
  ASSERT_EQ(stack.size(), 4);
}

TEST(Part3, StackInsertManyBack_3) {
  s21::stack<int> stack({111, 4, 5, 6});
  stack.pop();
  stack.insert_many_back(0);
  ASSERT_EQ(stack.top(), 0);
  ASSERT_EQ(stack.size(), 4);
}