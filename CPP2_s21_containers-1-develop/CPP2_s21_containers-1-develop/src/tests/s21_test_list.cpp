#include <gtest/gtest.h>

#include <list>

#include "../list/s21_list.h"

// =============================================
// BASIC CONSTRUCTION AND INITIALIZATION TESTS
// =============================================

TEST(ListTest, DefaultConstructor) {
  s21::list<int> myList;
  EXPECT_TRUE(myList.empty());
  EXPECT_EQ(myList.size(), 0);
}

TEST(ListTest, SizeConstructor) {
  s21::list<int> myList(5);
  EXPECT_EQ(myList.size(), 5);
  EXPECT_FALSE(myList.empty());
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, 0);
  }
}

TEST(ListTest, InitializerListConstructor) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.size(), 5);
  auto it = myList.begin();
  for (int i = 1; i <= 5; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(ListTest, CopyConstructorEmpty) {
  s21::list<int> emptyList;
  s21::list<int> copyList(emptyList);
  EXPECT_TRUE(copyList.empty());
}

TEST(ListTest, CopyConstructorSingleElement) {
  s21::list<int> original = {42};
  s21::list<int> copy(original);
  EXPECT_EQ(copy.size(), 1);
  EXPECT_EQ(copy.front(), 42);
  EXPECT_EQ(copy.back(), 42);
}

TEST(ListTest, CopyConstructorLargeList) {
  s21::list<int> original;
  for (int i = 0; i < 1000; ++i) {
    original.push_back(i);
  }
  s21::list<int> copy(original);
  EXPECT_EQ(copy.size(), 1000);
  auto it = copy.begin();
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(ListTest, MoveConstructorEmpty) {
  s21::list<int> emptyList;
  s21::list<int> movedList(std::move(emptyList));
  EXPECT_TRUE(movedList.empty());
  EXPECT_TRUE(emptyList.empty());
}

TEST(ListTest, MoveConstructorSingleElement) {
  s21::list<int> original = {42};
  s21::list<int> moved(std::move(original));
  EXPECT_EQ(moved.size(), 1);
  EXPECT_EQ(moved.front(), 42);
  EXPECT_TRUE(original.empty());
}

TEST(ListTest, MoveConstructorLargeList) {
  s21::list<int> original;
  for (int i = 0; i < 1000; ++i) {
    original.push_back(i);
  }
  s21::list<int> moved(std::move(original));
  EXPECT_EQ(moved.size(), 1000);
  EXPECT_TRUE(original.empty());
  auto it = moved.begin();
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(ListTest, MoveAssignmentOperator) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {4, 5, 6};
  list2 = std::move(list1);
  EXPECT_EQ(list2.size(), 3);
  EXPECT_TRUE(list1.empty());
  int expected[] = {1, 2, 3};
  int i = 0;
  for (const auto &elem : list2) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

// =============================================
// ELEMENT ACCESS TESTS
// =============================================

TEST(ListTest, Front) {
  s21::list<int> myList = {10, 20, 30};
  EXPECT_EQ(myList.front(), 10);
}

TEST(ListTest, Back) {
  s21::list<int> myList = {10, 20, 30};
  EXPECT_EQ(myList.back(), 30);
}

TEST(ListTest, FrontEmptyList) {
  s21::list<int> emptyList;
  EXPECT_THROW(emptyList.front(), std::out_of_range);
}

TEST(ListTest, BackEmptyList) {
  s21::list<int> emptyList;
  EXPECT_THROW(emptyList.back(), std::out_of_range);
}

// =============================================
// ITERATOR TESTS
// =============================================

TEST(ListTest, IteratorBeginEnd) {
  s21::list<int> myList = {1, 2, 3};
  auto it = myList.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, myList.end());
}

TEST(ListTest, ConstIteratorBeginEnd) {
  const s21::list<int> myList = {1, 2, 3};
  auto it = myList.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, myList.end());
}

TEST(ListTest, IteratorPostIncrement) {
  s21::list<int> myList = {1, 2, 3};
  auto it = myList.begin();
  EXPECT_EQ(*it++, 1);
  EXPECT_EQ(*it, 2);
}

TEST(ListTest, IteratorPreIncrement) {
  s21::list<int> myList = {1, 2, 3};
  auto it = myList.begin();
  EXPECT_EQ(*++it, 2);
}

TEST(ListTest, IteratorPostDecrement) {
  s21::list<int> myList = {1, 2, 3};
  auto it = myList.begin();
  ++it;
  EXPECT_EQ(*it--, 2);
  EXPECT_EQ(*it, 1);
}

TEST(ListTest, IteratorPreDecrement) {
  s21::list<int> myList = {1, 2, 3};
  auto it = myList.begin();
  ++it;
  EXPECT_EQ(*--it, 1);
}

TEST(ListTest, IteratorEquality) {
  s21::list<int> myList = {1, 2, 3};
  auto it1 = myList.begin();
  auto it2 = myList.begin();
  EXPECT_TRUE(it1 == it2);
  ++it1;
  EXPECT_FALSE(it1 == it2);
}

TEST(ListTest, IteratorInequality) {
  s21::list<int> myList = {1, 2, 3};
  auto it1 = myList.begin();
  auto it2 = myList.begin();
  EXPECT_FALSE(it1 != it2);
  ++it1;
  EXPECT_TRUE(it1 != it2);
}

// =============================================
// CAPACITY TESTS
// =============================================

TEST(ListTest, Empty) {
  s21::list<int> emptyList;
  EXPECT_TRUE(emptyList.empty());
  emptyList.push_back(1);
  EXPECT_FALSE(emptyList.empty());
  emptyList.pop_back();
  EXPECT_TRUE(emptyList.empty());
}

TEST(ListTest, Size) {
  s21::list<int> myList;
  EXPECT_EQ(myList.size(), 0);
  myList.push_back(1);
  EXPECT_EQ(myList.size(), 1);
  myList.push_back(2);
  EXPECT_EQ(myList.size(), 2);
  myList.pop_back();
  EXPECT_EQ(myList.size(), 1);
  myList.pop_back();
  EXPECT_EQ(myList.size(), 0);
}

TEST(ListTest, MaxSize) {
  s21::list<int> myList;
  EXPECT_GT(myList.max_size(), 0);
}

// =============================================
// MODIFIER TESTS
// =============================================

TEST(ListTest, PushBack) {
  s21::list<int> myList;
  myList.push_back(1);
  EXPECT_EQ(myList.back(), 1);
  myList.push_back(2);
  EXPECT_EQ(myList.back(), 2);
  EXPECT_EQ(myList.size(), 2);
}

TEST(ListTest, PushFront) {
  s21::list<int> myList;
  myList.push_front(1);
  EXPECT_EQ(myList.front(), 1);
  myList.push_front(2);
  EXPECT_EQ(myList.front(), 2);
  EXPECT_EQ(myList.size(), 2);
}

TEST(ListTest, PopBack) {
  s21::list<int> myList = {1, 2, 3};
  myList.pop_back();
  EXPECT_EQ(myList.back(), 2);
  myList.pop_back();
  EXPECT_EQ(myList.back(), 1);
  myList.pop_back();
  EXPECT_TRUE(myList.empty());
}

TEST(ListTest, PopFront) {
  s21::list<int> myList = {1, 2, 3};
  myList.pop_front();
  EXPECT_EQ(myList.front(), 2);
  myList.pop_front();
  EXPECT_EQ(myList.front(), 3);
  myList.pop_front();
  EXPECT_TRUE(myList.empty());
}

TEST(ListTest, Clear) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  EXPECT_EQ(myList.size(), 5);
  myList.clear();
  EXPECT_TRUE(myList.empty());
  EXPECT_EQ(myList.size(), 0);
}

TEST(ListTest, InsertAtBeginning) {
  s21::list<int> myList = {2, 3};
  auto it = myList.insert(myList.begin(), 1);
  EXPECT_EQ(*it, 1);
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.size(), 3);
}

TEST(ListTest, InsertAtEnd) {
  s21::list<int> myList = {1, 2};
  auto it = myList.insert(myList.end(), 3);
  EXPECT_EQ(*it, 3);
  EXPECT_EQ(myList.back(), 3);
  EXPECT_EQ(myList.size(), 3);
}

TEST(ListTest, InsertInMiddle) {
  s21::list<int> myList = {1, 3};
  auto it = myList.begin();
  ++it;
  it = myList.insert(it, 2);
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(myList.size(), 3);
  int expected[] = {1, 2, 3};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, InsertMultiple) {
  s21::list<int> myList;
  auto it = myList.begin();
  for (int i = 0; i < 10; ++i) {
    it = myList.insert(it, i);
  }
  EXPECT_EQ(myList.size(), 10);
  int i = 9;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, i--);
  }
}

TEST(ListTest, EraseAtBeginning) {
  s21::list<int> myList = {1, 2, 3};
  myList.erase(myList.begin());
  EXPECT_EQ(myList.front(), 2);
  EXPECT_EQ(myList.size(), 2);
}

TEST(ListTest, EraseAtEnd) {
  s21::list<int> myList = {1, 2, 3};
  auto it = myList.begin();
  ++it;
  ++it;
  myList.erase(it);
  EXPECT_EQ(myList.back(), 2);
  EXPECT_EQ(myList.size(), 2);
}

TEST(ListTest, EraseInMiddle) {
  s21::list<int> myList = {1, 2, 3};
  auto it = myList.begin();
  ++it;
  myList.erase(it);
  EXPECT_EQ(myList.size(), 2);
  EXPECT_EQ(myList.front(), 1);
  EXPECT_EQ(myList.back(), 3);
}

TEST(ListTest, EraseMultiple) {
  s21::list<int> myList;
  for (int i = 0; i < 10; ++i) {
    myList.push_back(i);
  }
  auto it = myList.begin();
  for (int i = 0; i < 5; ++i) {
    // Since erase doesn't return an iterator, we need to:
    // 1. Get the next iterator before erasing
    auto next_it = it;
    ++next_it;
    // 2. Erase the current element
    myList.erase(it);
    // 3. Move to the next element
    it = next_it;
  }
  EXPECT_EQ(myList.size(), 5);
  int expected[] = {5, 6, 7, 8, 9};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, Swap) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {4, 5, 6, 7};
  list1.swap(list2);
  EXPECT_EQ(list1.size(), 4);
  EXPECT_EQ(list2.size(), 3);
  int expected1[] = {4, 5, 6, 7};
  int expected2[] = {1, 2, 3};
  int i = 0;
  for (const auto &elem : list1) {
    EXPECT_EQ(elem, expected1[i++]);
  }
  i = 0;
  for (const auto &elem : list2) {
    EXPECT_EQ(elem, expected2[i++]);
  }
}

TEST(ListTest, SwapEmpty) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2;
  list1.swap(list2);
  EXPECT_TRUE(list1.empty());
  EXPECT_EQ(list2.size(), 3);
}

TEST(ListTest, SwapBothEmpty) {
  s21::list<int> list1;
  s21::list<int> list2;
  list1.swap(list2);
  EXPECT_TRUE(list1.empty());
  EXPECT_TRUE(list2.empty());
}

// =============================================
// OPERATIONS TESTS
// =============================================

TEST(ListTest, MergeEmpty) {
  s21::list<int> list1 = {1, 3, 5};
  s21::list<int> list2;
  list1.merge(list2);
  EXPECT_EQ(list1.size(), 3);
  EXPECT_TRUE(list2.empty());
  int expected[] = {1, 3, 5};
  int i = 0;
  for (const auto &elem : list1) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, MergeIntoEmpty) {
  s21::list<int> list1;
  s21::list<int> list2 = {2, 4, 6};
  list1.merge(list2);
  EXPECT_EQ(list1.size(), 3);
  EXPECT_TRUE(list2.empty());
  int expected[] = {2, 4, 6};
  int i = 0;
  for (const auto &elem : list1) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, MergeAlreadySorted) {
  s21::list<int> list1 = {1, 3, 5};
  s21::list<int> list2 = {2, 4, 6};
  list1.merge(list2);
  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());
  int expected[] = {1, 2, 3, 4, 5, 6};
  int i = 0;
  for (const auto &elem : list1) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, MergeReverseOrder) {
  s21::list<int> list1 = {5, 3, 1};
  s21::list<int> list2 = {6, 4, 2};
  list1.sort();
  list2.sort();
  list1.merge(list2);
  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());
  int expected[] = {1, 2, 3, 4, 5, 6};
  int i = 0;
  for (const auto &elem : list1) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, SpliceAtBeginning) {
  s21::list<int> list1 = {4, 5, 6};
  s21::list<int> list2 = {1, 2, 3};
  list1.splice(list1.begin(), list2);
  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());
  int expected[] = {1, 2, 3, 4, 5, 6};
  int i = 0;
  for (const auto &elem : list1) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, SpliceAtEnd) {
  s21::list<int> list1 = {1, 2, 3};
  s21::list<int> list2 = {4, 5, 6};
  list1.splice(list1.end(), list2);
  EXPECT_EQ(list1.size(), 6);
  EXPECT_TRUE(list2.empty());
  int expected[] = {1, 2, 3, 4, 5, 6};
  int i = 0;
  for (const auto &elem : list1) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, SpliceInMiddle) {
  s21::list<int> list1 = {1, 4};
  s21::list<int> list2 = {2, 3};
  auto it = list1.begin();
  ++it;
  list1.splice(it, list2);
  EXPECT_EQ(list1.size(), 4);
  EXPECT_TRUE(list2.empty());
  int expected[] = {1, 2, 3, 4};
  int i = 0;
  for (const auto &elem : list1) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, ReverseEmpty) {
  s21::list<int> emptyList;
  emptyList.reverse();
  EXPECT_TRUE(emptyList.empty());
}

TEST(ListTest, ReverseSingleElement) {
  s21::list<int> myList = {42};
  myList.reverse();
  EXPECT_EQ(myList.size(), 1);
  EXPECT_EQ(myList.front(), 42);
}

TEST(ListTest, ReverseEvenElements) {
  s21::list<int> myList = {1, 2, 3, 4};
  myList.reverse();
  int expected[] = {4, 3, 2, 1};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, ReverseOddElements) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  myList.reverse();
  int expected[] = {5, 4, 3, 2, 1};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, UniqueEmpty) {
  s21::list<int> emptyList;
  emptyList.unique();
  EXPECT_TRUE(emptyList.empty());
}

TEST(ListTest, UniqueSingleElement) {
  s21::list<int> myList = {42};
  myList.unique();
  EXPECT_EQ(myList.size(), 1);
  EXPECT_EQ(myList.front(), 42);
}

TEST(ListTest, UniqueNoDuplicates) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  myList.unique();
  EXPECT_EQ(myList.size(), 5);
  int expected[] = {1, 2, 3, 4, 5};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, UniqueAllSame) {
  s21::list<int> myList = {1, 1, 1, 1, 1};
  myList.unique();
  EXPECT_EQ(myList.size(), 1);
  EXPECT_EQ(myList.front(), 1);
}

TEST(ListTest, UniqueSomeDuplicates) {
  s21::list<int> myList = {1, 1, 2, 2, 3, 4, 4, 5, 5, 5};
  myList.unique();
  EXPECT_EQ(myList.size(), 5);
  int expected[] = {1, 2, 3, 4, 5};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, SortEmpty) {
  s21::list<int> emptyList;
  emptyList.sort();
  EXPECT_TRUE(emptyList.empty());
}

TEST(ListTest, SortSingleElement) {
  s21::list<int> myList = {42};
  myList.sort();
  EXPECT_EQ(myList.size(), 1);
  EXPECT_EQ(myList.front(), 42);
}

TEST(ListTest, SortAlreadySorted) {
  s21::list<int> myList = {1, 2, 3, 4, 5};
  myList.sort();
  EXPECT_EQ(myList.size(), 5);
  int expected[] = {1, 2, 3, 4, 5};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, SortReverseOrder) {
  s21::list<int> myList = {5, 4, 3, 2, 1};
  myList.sort();
  EXPECT_EQ(myList.size(), 5);
  int expected[] = {1, 2, 3, 4, 5};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, SortRandomOrder) {
  s21::list<int> myList = {3, 1, 4, 5, 2};
  myList.sort();
  EXPECT_EQ(myList.size(), 5);
  int expected[] = {1, 2, 3, 4, 5};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, SortLargeList) {
  s21::list<int> myList;
  for (int i = 0; i < 100; ++i) {
    myList.push_back(99 - i);
  }
  myList.sort();
  EXPECT_EQ(myList.size(), 100);
  auto it = myList.begin();
  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

// =============================================
// EDGE CASE TESTS
// =============================================

TEST(ListTest, InsertAtEndOfEmptyList) {
  s21::list<int> emptyList;
  auto it = emptyList.insert(emptyList.end(), 42);
  EXPECT_EQ(*it, 42);
  EXPECT_EQ(emptyList.size(), 1);
  EXPECT_EQ(emptyList.front(), 42);
  EXPECT_EQ(emptyList.back(), 42);
}

TEST(ListTest, EraseOnlyElement) {
  s21::list<int> myList = {42};
  myList.erase(myList.begin());
  EXPECT_TRUE(myList.empty());
  EXPECT_EQ(myList.size(), 0);
}

TEST(ListTest, PopBackOnlyElement) {
  s21::list<int> myList = {42};
  myList.pop_back();
  EXPECT_TRUE(myList.empty());
  EXPECT_EQ(myList.size(), 0);
}

TEST(ListTest, PopFrontOnlyElement) {
  s21::list<int> myList = {42};
  myList.pop_front();
  EXPECT_TRUE(myList.empty());
  EXPECT_EQ(myList.size(), 0);
}

TEST(ListTest, MergeSameList) {
  s21::list<int> myList = {1, 2, 3};
  myList.merge(myList);
  EXPECT_EQ(myList.size(), 3);
  int expected[] = {1, 2, 3};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, SpliceSameList) {
  s21::list<int> myList = {1, 2, 3};
  myList.splice(myList.begin(), myList);
  EXPECT_EQ(myList.size(), 3);
  int expected[] = {1, 2, 3};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, SortWithDuplicates) {
  s21::list<int> myList = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
  myList.sort();
  EXPECT_EQ(myList.size(), 10);
  int expected[] = {1, 1, 2, 3, 3, 4, 5, 5, 6, 9};
  int i = 0;
  for (const auto &elem : myList) {
    EXPECT_EQ(elem, expected[i++]);
  }
}

TEST(ListTest, LargeNumberOfElements) {
  s21::list<int> myList;
  const int count = 10000;
  for (int i = 0; i < count; ++i) {
    myList.push_back(i);
  }
  EXPECT_EQ(myList.size(), count);
  auto it = myList.begin();
  for (int i = 0; i < count; ++i) {
    EXPECT_EQ(*it, i);
    ++it;
  }
}

TEST(ListTest, StringElements) {
  s21::list<std::string> myList = {"hello", "world", "test"};
  EXPECT_EQ(myList.size(), 3);
  auto it = myList.begin();
  EXPECT_EQ(*it, "hello");
  ++it;
  EXPECT_EQ(*it, "world");
  ++it;
  EXPECT_EQ(*it, "test");
}

TEST(ListTest, CustomStructElements) {
  struct Point {
    int x, y;
    bool operator==(const Point &other) const {
      return x == other.x && y == other.y;
    }
  };

  s21::list<Point> points = {{1, 2}, {3, 4}, {5, 6}};
  EXPECT_EQ(points.size(), 3);
  auto it = points.begin();
  EXPECT_EQ(*it, (Point{1, 2}));
  ++it;
  EXPECT_EQ(*it, (Point{3, 4}));
  ++it;
  EXPECT_EQ(*it, (Point{5, 6}));
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }