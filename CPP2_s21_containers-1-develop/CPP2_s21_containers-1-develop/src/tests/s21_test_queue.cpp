#include <gtest/gtest.h>

#include "../queue/s21_queue.h"

using s21::queue;

// Конструкторы
TEST(QueueTest, DefaultConstructor) {
  queue<int> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0u);
}

TEST(QueueTest, InitializerListConstructor) {
  queue<int> q{1, 2, 3};
  EXPECT_EQ(q.size(), 3u);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, CopyConstructor) {
  queue<int> q1{1, 2, 3};
  queue<int> q2(q1);
  EXPECT_EQ(q2.size(), 3u);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);
}

TEST(QueueTest, MoveConstructor) {
  queue<int> q1{1, 2, 3};
  queue<int> q2(std::move(q1));
  EXPECT_EQ(q2.size(), 3u);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_TRUE(q1.empty());
}

TEST(QueueTest, MoveAssignment) {
  queue<int> q1{1, 2};
  queue<int> q2;
  q2 = std::move(q1);
  EXPECT_EQ(q2.size(), 2u);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_TRUE(q1.empty());
}

// Методы доступа
TEST(QueueTest, FrontBackAccess) {
  queue<std::string> q{"first", "second"};
  EXPECT_EQ(q.front(), "first");
  EXPECT_EQ(q.back(), "second");
}

TEST(QueueTest, FrontEmptyException) {
  queue<int> q;
  EXPECT_THROW(q.front(), std::out_of_range);
  EXPECT_THROW(q.back(), std::out_of_range);
}

// Модификаторы
TEST(QueueTest, PushPop) {
  queue<int> q;
  q.push(10);
  EXPECT_EQ(q.size(), 1u);
  EXPECT_EQ(q.front(), 10);

  q.push(20);
  EXPECT_EQ(q.size(), 2u);
  EXPECT_EQ(q.back(), 20);

  q.pop();
  EXPECT_EQ(q.size(), 1u);
  EXPECT_EQ(q.front(), 20);

  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, PopEmptyException) {
  queue<int> q;
  EXPECT_THROW(q.pop(), std::out_of_range);
}

TEST(QueueTest, Swap) {
  queue<int> q1{1, 2};
  queue<int> q2{3};
  q1.swap(q2);

  EXPECT_EQ(q1.size(), 1u);
  EXPECT_EQ(q1.front(), 3);
  EXPECT_EQ(q2.size(), 2u);
  EXPECT_EQ(q2.front(), 1);
}

TEST(QueueTest, IteratorEquality) {
  queue<int> q{1, 2};
  auto it1 = q.begin();
  auto it2 = q.begin();
  EXPECT_TRUE(it1 == it2);
  ++it2;
  EXPECT_TRUE(it1 != it2);
}

// Очистка через деструктор (неявно)
TEST(QueueTest, DestructorNoLeak) {
  queue<int>* q = new queue<int>{1, 2, 3};
  delete q;
  SUCCEED();  // Если нет утечек — успешно
}

// Проверка шаблонов с другим типом
TEST(QueueTest, WithDoubleType) {
  queue<double> q;
  q.push(1.5);
  q.push(2.5);
  EXPECT_EQ(q.front(), 1.5);
  EXPECT_EQ(q.back(), 2.5);
  EXPECT_EQ(q.size(), 2u);
}

TEST(QueueTest, StringQueuePushPop) {
  queue<std::string> q;
  q.push("alpha");
  q.push("beta");
  EXPECT_EQ(q.front(), "alpha");
  EXPECT_EQ(q.back(), "beta");

  q.pop();
  EXPECT_EQ(q.front(), "beta");
}

TEST(QueueTest, StringQueueCopy) {
  queue<std::string> q1{"one", "two"};
  queue<std::string> q2(q1);
  EXPECT_EQ(q2.size(), 2u);
  EXPECT_EQ(q2.front(), "one");
  EXPECT_EQ(q2.back(), "two");
}

TEST(QueueTest, StringQueueIterator) {
  queue<std::string> q{"a", "b", "c"};
  std::string concat;
  for (auto it = q.begin(); it != q.end(); ++it) {
    concat += *it;
  }
  EXPECT_EQ(concat, "abc");
}

// Итератор
TEST(QueueTest, IteratorTraverse) {
  queue<int> q{10, 20, 30};
  int sum = 0;
  for (auto it = q.begin(); it != q.end(); ++it) {
    sum += *it;
  }
  EXPECT_EQ(sum, 60);
}

TEST(QueueTest, IteratorBackwardTraversal) {
  queue<int> q{1, 2, 3};  // front = 1, back = 3
  auto it = q.begin();
  ++it;  // 2
  ++it;  // 3
  --it;  // back to 2
  EXPECT_EQ(*it, 2);
  --it;  // back to 1
  EXPECT_EQ(*it, 1);
}

TEST(QueueTest, IteratorFullTraversalOrder) {
  queue<int> q{100, 200, 300};
  std::vector<int> result;
  for (auto it = q.begin(); it != q.end(); ++it) {
    result.push_back(*it);
  }
  std::vector<int> expected{100, 200, 300};  // FIFO порядок
  EXPECT_EQ(result, expected);
}

TEST(QueueTest, IteratorEmptyQueue) {
  queue<int> q;
  auto it = q.begin();
  auto end = q.end();
  EXPECT_TRUE(it == end);
}

TEST(QueueTest, IteratorDecrementAtBeginGivesNull) {
  queue<int> q{1, 2};
  auto it = q.begin();
  --it;
  EXPECT_TRUE(it == q.end());
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
