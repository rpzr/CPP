#include <gtest/gtest.h>

#include "../stack/s21_stack.h"

using s21::stack;

// Конструкторы
TEST(StackTest, DefaultConstructor) {
  stack<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

TEST(StackTest, InitializerListConstructor) {
  stack<int> s{1, 2, 3};
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.top(), 3);
}

TEST(StackTest, CopyConstructor) {
  stack<int> s1{1, 2, 3};
  stack<int> s2(s1);
  EXPECT_EQ(s2.size(), 3u);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, MoveConstructor) {
  stack<int> s1{1, 2, 3};
  stack<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3u);
  EXPECT_EQ(s2.top(), 3);
  EXPECT_TRUE(s1.empty());
}

TEST(StackTest, MoveAssignment) {
  stack<int> s1{1, 2};
  stack<int> s2;
  s2 = std::move(s1);
  EXPECT_EQ(s2.size(), 2u);
  EXPECT_EQ(s2.top(), 2);
  EXPECT_TRUE(s1.empty());
}

// Методы доступа
TEST(StackTest, TopAccess) {
  stack<std::string> s;
  s.push("one");
  s.push("two");
  EXPECT_EQ(s.top(), "two");
}

TEST(StackTest, TopEmptyException) {
  stack<int> s;
  EXPECT_THROW(s.top(), std::out_of_range);
}

// Модификаторы
TEST(StackTest, PushPop) {
  stack<int> s;
  s.push(10);
  EXPECT_EQ(s.size(), 1u);
  EXPECT_EQ(s.top(), 10);

  s.push(20);
  EXPECT_EQ(s.size(), 2u);
  EXPECT_EQ(s.top(), 20);

  s.pop();
  EXPECT_EQ(s.size(), 1u);
  EXPECT_EQ(s.top(), 10);

  s.pop();
  EXPECT_TRUE(s.empty());
}

TEST(StackTest, PopEmptyException) {
  stack<int> s;
  EXPECT_THROW(s.pop(), std::out_of_range);
}

TEST(StackTest, Swap) {
  stack<int> s1{1, 2};
  stack<int> s2{3};
  s1.swap(s2);

  EXPECT_EQ(s1.size(), 1u);
  EXPECT_EQ(s1.top(), 3);
  EXPECT_EQ(s2.size(), 2u);
  EXPECT_EQ(s2.top(), 2);
}

// Очистка через деструктор (неявно)
TEST(StackTest, DestructorNoLeak) {
  stack<int>* s = new stack<int>{1, 2, 3};
  delete s;
  SUCCEED();  // Если нет утечек — успешно
}

// Шаблоны с другими типами
TEST(StackTest, WithDoubleType) {
  stack<double> s;
  s.push(1.5);
  s.push(2.5);
  EXPECT_EQ(s.top(), 2.5);
  EXPECT_EQ(s.size(), 2u);
}

TEST(StackTest, StringStackPushPop) {
  stack<std::string> s;
  s.push("alpha");
  s.push("beta");
  EXPECT_EQ(s.top(), "beta");

  s.pop();
  EXPECT_EQ(s.top(), "alpha");
}

TEST(StackTest, StringStackCopy) {
  stack<std::string> s1{"one", "two"};
  stack<std::string> s2(s1);
  EXPECT_EQ(s2.size(), 2u);
  EXPECT_EQ(s2.top(), "two");
}

// Итераторы
TEST(StackTest, IteratorForwardTraversal) {
  stack<int> s{1, 2, 3};  // top = 3
  std::vector<int> actual;
  for (auto it = s.begin(); it != s.end(); ++it) {
    actual.push_back(*it);
  }
  std::vector<int> expected{3, 2, 1};
  EXPECT_EQ(actual, expected);
}

TEST(StackTest, IteratorBackwardTraversal) {
  stack<int> s{10, 20, 30};  // top = 30
  auto it = s.begin();
  ++it;  // 20
  ++it;  // 10
  --it;  // back to 20
  EXPECT_EQ(*it, 20);
  --it;  // back to 30
  EXPECT_EQ(*it, 30);
}

TEST(StackTest, IteratorEquality) {
  stack<int> s{5, 10};
  auto it1 = s.begin();
  auto it2 = s.begin();
  EXPECT_TRUE(it1 == it2);
  ++it2;
  EXPECT_TRUE(it1 != it2);
}

TEST(StackTest, IteratorEmpty) {
  stack<int> s;
  EXPECT_TRUE(s.begin() == s.end());
}

// int main(int argc, char** argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
