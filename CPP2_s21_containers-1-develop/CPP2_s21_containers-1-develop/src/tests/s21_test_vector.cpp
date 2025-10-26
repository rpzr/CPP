#include <gtest/gtest.h>

#include <vector>

#include "../vector/s21_vector.h"

TEST(DefaultConstructor, NoParameters) {
  s21::vector<int> s21_vec1;
  s21::vector<double> s21_vec2;
  s21::vector<std::string> s21_vec3;

  std::vector<int> std_vec1;
  std::vector<double> std_vec2;
  std::vector<std::string> std_vec3;

  EXPECT_EQ(s21_vec1.size(), std_vec1.size());
  EXPECT_EQ(s21_vec1.capacity(), std_vec1.capacity());
  EXPECT_EQ(s21_vec1.data(), std_vec1.data());
  EXPECT_EQ(s21_vec2.size(), std_vec2.size());
  EXPECT_EQ(s21_vec2.capacity(), std_vec2.capacity());
  EXPECT_EQ(s21_vec2.data(), std_vec2.data());
  EXPECT_EQ(s21_vec3.size(), std_vec3.size());
  EXPECT_EQ(s21_vec3.capacity(), std_vec3.capacity());
  EXPECT_EQ(s21_vec3.data(), std_vec3.data());
}

TEST(VectorConstructorSizeTest, DefaultValues) {
  s21::vector<int> s21_vec(5);
  std::vector<int> std_vec(5);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorConstructorSizeTest, NonTrivialType) {
  s21::vector<std::string> s21_vec(3);
  std::vector<std::string> std_vec(3);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorConstructorSizeTest, ZeroSize) {
  s21::vector<double> s21_vec(0);
  std::vector<double> std_vec(0);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  EXPECT_EQ(s21_vec.data(), std_vec.data());
}

TEST(VectorConstructorSizeTest, MaxSizeCheck) {
  EXPECT_THROW(s21::vector<int> s21_vec(-1), std::length_error);
  EXPECT_THROW(std::vector<int> std_vec(-1), std::length_error);
}

TEST(VectorConstructorSizeTest, MemoryAllocation) {
  s21::vector<char> s21_vec(10);
  std::vector<char> std_vec(10);

  EXPECT_EQ(s21_vec.size(), 10U);
  EXPECT_EQ(s21_vec.capacity(), 10U);

  EXPECT_EQ(std_vec.size(), 10U);
  EXPECT_EQ(std_vec.capacity(), 10U);
}

TEST(VectorCopyConstructorTest, CopyEmptyVector) {
  s21::vector<int> s21_empty;
  std::vector<int> std_empty;

  s21::vector<int> s21_copy(s21_empty);
  std::vector<int> std_copy(std_empty);

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.data(), nullptr);
}

TEST(VectorCopyConstructorTest, CopyNonEmptyVector) {
  s21::vector<int> s21_original = {1, 2, 3, 4, 5};
  std::vector<int> std_original = {1, 2, 3, 4, 5};

  s21::vector<int> s21_copy(s21_original);
  std::vector<int> std_copy(std_original);

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  for (size_t i = 0; i < s21_copy.size(); ++i) {
    EXPECT_EQ(s21_copy[i], std_copy[i]);
  }

  EXPECT_EQ(s21_original.size(), 5U);
  EXPECT_EQ(std_original.size(), 5U);
}

TEST(VectorCopyConstructorTest, CopyStringType) {
  s21::vector<std::string> s21_original = {"Hello", "World", "!"};
  std::vector<std::string> std_original = {"Hello", "World", "!"};

  s21::vector<std::string> s21_copy(s21_original);
  std::vector<std::string> std_copy(std_original);

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  for (size_t i = 0; i < s21_copy.size(); ++i) {
    EXPECT_EQ(s21_copy[i], std_copy[i]);
  }
}

TEST(VectorCopyConstructorTest, SelfCopyCheck) {
  s21::vector<int> s21_vec = {10, 20, 30};
  s21_vec = s21_vec;

  EXPECT_EQ(s21_vec.size(), 3U);
  EXPECT_EQ(s21_vec[0], 10);
  EXPECT_EQ(s21_vec[1], 20);
  EXPECT_EQ(s21_vec[2], 30);
}

TEST(VectorMoveTest, MoveConstructorBasic) {
  s21::vector<int> s21_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};

  s21::vector<int> s21_moved(std::move(s21_vec));
  std::vector<int> std_moved(std::move(std_vec));

  EXPECT_EQ(s21_moved.size(), std_moved.size());
  EXPECT_EQ(s21_moved.capacity(), std_moved.capacity());
  for (size_t i = 0; i < s21_moved.size(); ++i) {
    EXPECT_EQ(s21_moved[i], std_moved[i]);
  }

  EXPECT_EQ(s21_vec.size(), 0U);
  EXPECT_EQ(s21_vec.capacity(), 0U);
  EXPECT_EQ(s21_vec.data(), nullptr);

  EXPECT_EQ(std_vec.size(), 0U);
  EXPECT_EQ(std_vec.capacity(), 0U);
  EXPECT_EQ(std_vec.data(), nullptr);
}

TEST(VectorMoveTest, MoveConstructorEmpty) {
  s21::vector<double> s21_vec;
  std::vector<double> std_vec;

  s21::vector<double> s21_moved(std::move(s21_vec));
  std::vector<double> std_moved(std::move(std_vec));

  EXPECT_EQ(s21_moved.size(), std_moved.size());
  EXPECT_EQ(s21_moved.capacity(), std_moved.capacity());
  EXPECT_EQ(s21_moved.data(), nullptr);

  EXPECT_EQ(s21_vec.size(), 0U);
  EXPECT_EQ(s21_vec.capacity(), 0U);
  EXPECT_EQ(s21_vec.data(), nullptr);
}

TEST(VectorMoveTest, MoveConstructorWithStrings) {
  s21::vector<std::string> s21_vec = {"hello", "world"};
  std::vector<std::string> std_vec = {"hello", "world"};

  s21::vector<std::string> s21_moved(std::move(s21_vec));
  std::vector<std::string> std_moved(std::move(std_vec));

  EXPECT_EQ(s21_moved.size(), std_moved.size());
  for (size_t i = 0; i < s21_moved.size(); ++i) {
    EXPECT_EQ(s21_moved[i], std_moved[i]);
  }

  EXPECT_EQ(s21_vec.size(), 0U);
  EXPECT_EQ(s21_vec.capacity(), 0U);
  EXPECT_EQ(s21_vec.data(), nullptr);

  EXPECT_EQ(std_vec.size(), 0U);
  EXPECT_TRUE(std_vec.empty());
}

TEST(VectorMoveTest, MoveAssignment) {
  s21::vector<int> s21_vec = {10, 20, 30};
  std::vector<int> std_vec = {10, 20, 30};

  s21::vector<int> s21_moved;
  std::vector<int> std_moved;

  s21_moved = std::move(s21_vec);
  std_moved = std::move(std_vec);

  EXPECT_EQ(s21_moved.size(), std_moved.size());
  EXPECT_EQ(s21_moved[0], std_moved[0]);

  EXPECT_EQ(s21_vec.size(), 0U);
  EXPECT_EQ(std_vec.size(), 0U);
}

TEST(VectorInitializerListTest, EmptyList) {
  s21::vector<int> s21_vec{};
  std::vector<int> std_vec{};

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  EXPECT_EQ(s21_vec.data(), nullptr);
}

TEST(VectorInitializerListTest, IntList) {
  s21::vector<int> s21_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorInitializerListTest, StringList) {
  s21::vector<std::string> s21_vec = {"Hello", "World", "!"};
  std::vector<std::string> std_vec = {"Hello", "World", "!"};

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorInitializerListTest, MoveSemanticsCheck) {
  s21::vector<std::string> s21_vec = {std::string("Hello"),
                                      std::string("World")};
  std::vector<std::string> std_vec = {std::string("Hello"),
                                      std::string("World")};

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorInitializerListTest, LargeList) {
  s21::vector<int> s21_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> std_vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorCopyAssignmentTest, SelfAssignment) {
  s21::vector<int> v = {1, 2, 3};
  v = v;
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorCopyAssignmentTest, EmptyToEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2;
  v1 = v2;
  EXPECT_TRUE(v1.empty());
  EXPECT_EQ(v1.capacity(), 0);
}

TEST(VectorCopyAssignmentTest, EmptyToNonEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2;
  v1 = v2;
  EXPECT_TRUE(v1.empty());
  EXPECT_EQ(v1.capacity(), 0);
}

TEST(VectorCopyAssignmentTest, NonEmptyToEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {4, 5, 6};
  v1 = v2;
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[1], 5);
  EXPECT_EQ(v1[2], 6);
}

TEST(VectorCopyAssignmentTest, NonEmptyToNonEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6, 7};
  v1 = v2;
  EXPECT_EQ(v1.size(), 4);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[1], 5);
  EXPECT_EQ(v1[2], 6);
  EXPECT_EQ(v1[3], 7);
}

TEST(VectorCopyAssignmentTest, NonTrivialType) {
  s21::vector<std::string> v1 = {"a", "b"};
  s21::vector<std::string> v2 = {"x", "y", "z"};
  v1 = v2;
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1[0], "x");
  EXPECT_EQ(v1[1], "y");
  EXPECT_EQ(v1[2], "z");
}

TEST(VectorCopyAssignmentTest, CompareWithStdVector) {
  std::vector<int> std_v1 = {1, 2};
  std::vector<int> std_v2 = {3, 4, 5};
  std_v1 = std_v2;

  s21::vector<int> s21_v1 = {1, 2};
  s21::vector<int> s21_v2 = {3, 4, 5};
  s21_v1 = s21_v2;

  EXPECT_EQ(s21_v1.size(), std_v1.size());
  for (size_t i = 0; i < s21_v1.size(); ++i) {
    EXPECT_EQ(s21_v1[i], std_v1[i]);
  }
}

TEST(VectorCopyAssignmentTest, CapacityHandling) {
  s21::vector<int> v1(10);
  s21::vector<int> v2(5);
  v1 = v2;
  EXPECT_EQ(v1.size(), 5);
  EXPECT_GE(v1.capacity(), 5);
}

TEST(VectorMoveAssignmentTest, EmptyToEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2;
  v1 = std::move(v2);
  EXPECT_TRUE(v1.empty());
  EXPECT_TRUE(v2.empty());
}

TEST(VectorMoveAssignmentTest, EmptyToNonEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2;
  v1 = std::move(v2);
  EXPECT_TRUE(v1.empty());
  EXPECT_TRUE(v2.empty());
}

TEST(VectorMoveAssignmentTest, NonEmptyToEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {4, 5, 6};
  v1 = std::move(v2);
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[1], 5);
  EXPECT_EQ(v1[2], 6);
  EXPECT_TRUE(v2.empty());
}

TEST(VectorMoveAssignmentTest, NonEmptyToNonEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6, 7};
  v1 = std::move(v2);
  EXPECT_EQ(v1.size(), 4);
  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[1], 5);
  EXPECT_EQ(v1[2], 6);
  EXPECT_EQ(v1[3], 7);
  EXPECT_TRUE(v2.empty());
}

TEST(VectorMoveAssignmentTest, NonTrivialType) {
  s21::vector<std::string> v1 = {"a", "b"};
  s21::vector<std::string> v2 = {"x", "y", "z"};
  v1 = std::move(v2);
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1[0], "x");
  EXPECT_EQ(v1[1], "y");
  EXPECT_EQ(v1[2], "z");
  EXPECT_TRUE(v2.empty());
}

TEST(VectorMoveAssignmentTest, CompareWithStdVector) {
  std::vector<int> std_v1 = {1, 2};
  std::vector<int> std_v2 = {3, 4, 5};
  std_v1 = std::move(std_v2);

  s21::vector<int> s21_v1 = {1, 2};
  s21::vector<int> s21_v2 = {3, 4, 5};
  s21_v1 = std::move(s21_v2);

  EXPECT_EQ(s21_v1.size(), std_v1.size());
  EXPECT_EQ(s21_v2.size(), std_v2.size());
  for (size_t i = 0; i < s21_v1.size(); ++i) {
    EXPECT_EQ(s21_v1[i], std_v1[i]);
  }
}

TEST(VectorMoveAssignmentTest, MoveStateAfterAssignment) {
  s21::vector<int> v1 = {1, 2};
  s21::vector<int> v2 = {3, 4, 5};
  v1 = std::move(v2);

  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1.capacity(), 3);
  EXPECT_NE(v1.data(), nullptr);

  EXPECT_EQ(v2.size(), 0);
  EXPECT_EQ(v2.capacity(), 0);
  EXPECT_EQ(v2.data(), nullptr);
}

TEST(VectorMoveAssignmentTest, MemoryLeakCheck) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  int* original_data = v1.data();

  s21::vector<int> v2 = {6, 7, 8};
  v1 = std::move(v2);
  EXPECT_NE(v1.data(), original_data);
}

TEST(VectorAtTest, ValidIndex) {
  s21::vector<int> s21_vec = {10, 20, 30};
  std::vector<int> std_vec = {10, 20, 30};

  EXPECT_EQ(s21_vec.at(0), std_vec.at(0));
  EXPECT_EQ(s21_vec.at(1), std_vec.at(1));
  EXPECT_EQ(s21_vec.at(2), std_vec.at(2));
}

TEST(VectorAtTest, ConstVersion) {
  const s21::vector<int> s21_vec = {1, 2, 3};
  const std::vector<int> std_vec = {1, 2, 3};

  EXPECT_EQ(s21_vec.at(0), std_vec.at(0));
  EXPECT_EQ(s21_vec.at(1), std_vec.at(1));
  EXPECT_EQ(s21_vec.at(2), std_vec.at(2));
}

TEST(VectorAtTest, OutOfRange) {
  s21::vector<int> s21_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};

  EXPECT_THROW(s21_vec.at(3), std::out_of_range);
  EXPECT_THROW(std_vec.at(3), std::out_of_range);
  EXPECT_THROW(s21_vec.at(100), std::out_of_range);
  EXPECT_THROW(std_vec.at(100), std::out_of_range);
}

TEST(VectorAtTest, EmptyVector) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  EXPECT_THROW(s21_vec.at(0), std::out_of_range);
  EXPECT_THROW(std_vec.at(0), std::out_of_range);
}

TEST(VectorAtTest, StringType) {
  s21::vector<std::string> s21_vec = {"a", "bb", "ccc"};
  std::vector<std::string> std_vec = {"a", "bb", "ccc"};

  EXPECT_EQ(s21_vec.at(0), std_vec.at(0));
  EXPECT_EQ(s21_vec.at(1), std_vec.at(1));
  EXPECT_EQ(s21_vec.at(2), std_vec.at(2));
}

TEST(VectorAtTest, Modification) {
  s21::vector<int> s21_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};

  s21_vec.at(1) = 100;
  std_vec.at(1) = 100;

  EXPECT_EQ(s21_vec.at(1), std_vec.at(1));
  EXPECT_EQ(s21_vec[1], std_vec[1]);
}

TEST(VectorAtTest, CompareWithOperator) {
  s21::vector<int> s21_vec = {5, 10, 15};
  std::vector<int> std_vec = {5, 10, 15};

  EXPECT_EQ(s21_vec.at(0), s21_vec[0]);
  EXPECT_EQ(s21_vec.at(1), s21_vec[1]);
  EXPECT_EQ(s21_vec.at(2), s21_vec[2]);

  EXPECT_EQ(std_vec.at(0), std_vec[0]);
  EXPECT_EQ(std_vec.at(1), std_vec[1]);
  EXPECT_EQ(std_vec.at(2), std_vec[2]);
}

TEST(VectorReserveTest, IncreaseCapacity) {
  s21::vector<int> s21_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};

  size_t new_capacity = 10;
  s21_vec.reserve(new_capacity);
  std_vec.reserve(new_capacity);

  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorReserveTest, SmallerCapacityNoChange) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  s21_vec.reserve(10);
  std_vec.reserve(10);

  size_t original_capacity = s21_vec.capacity();
  s21_vec.reserve(5);
  std_vec.reserve(5);

  EXPECT_EQ(s21_vec.capacity(), original_capacity);
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
}

TEST(VectorReserveTest, MaxSizeCheck) {
  s21::vector<int> s21_vec;

  EXPECT_THROW(s21_vec.reserve(s21_vec.max_size() + 1), std::out_of_range);
}

TEST(VectorReserveTest, ZeroCapacity) {
  s21::vector<int> s21_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};

  s21_vec.reserve(0);
  std_vec.reserve(0);

  EXPECT_GE(s21_vec.capacity(), s21_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
}

TEST(VectorReserveTest, NonTrivialType) {
  s21::vector<std::string> s21_vec = {"a", "bb", "ccc"};
  std::vector<std::string> std_vec = {"a", "bb", "ccc"};

  s21_vec.reserve(10);
  std_vec.reserve(10);

  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorShrinkToFitTest, EmptyVector) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  s21_vec.shrink_to_fit();
  std_vec.shrink_to_fit();

  EXPECT_EQ(s21_vec.capacity(), 0);
  EXPECT_EQ(s21_vec.data(), nullptr);
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
}

TEST(VectorShrinkToFitTest, AlreadyFitted) {
  s21::vector<int> s21_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};

  size_t original_capacity = s21_vec.capacity();
  s21_vec.shrink_to_fit();
  std_vec.shrink_to_fit();

  EXPECT_EQ(s21_vec.capacity(), original_capacity);
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorShrinkToFitTest, ReduceCapacity) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  s21_vec.reserve(10);
  std_vec.reserve(10);
  s21_vec.push_back(1);
  s21_vec.push_back(2);
  std_vec.push_back(1);
  std_vec.push_back(2);

  s21_vec.shrink_to_fit();
  std_vec.shrink_to_fit();

  EXPECT_EQ(s21_vec.capacity(), s21_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  EXPECT_EQ(s21_vec[0], std_vec[0]);
  EXPECT_EQ(s21_vec[1], std_vec[1]);
}

TEST(VectorShrinkToFitTest, NonTrivialType) {
  s21::vector<std::string> s21_vec = {"a", "bb", "ccc"};
  std::vector<std::string> std_vec = {"a", "bb", "ccc"};

  s21_vec.reserve(10);
  std_vec.reserve(10);
  s21_vec.shrink_to_fit();
  std_vec.shrink_to_fit();

  EXPECT_EQ(s21_vec.capacity(), s21_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorShrinkToFitTest, CompareWithStdVector) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  for (int i = 0; i < 100; ++i) {
    s21_vec.push_back(i);
    std_vec.push_back(i);
  }
  s21_vec.reserve(200);
  std_vec.reserve(200);

  s21_vec.shrink_to_fit();
  std_vec.shrink_to_fit();

  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorPushBackTest, EmptyVector) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  s21_vec.push_back(1);
  std_vec.push_back(1);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  EXPECT_EQ(s21_vec[0], std_vec[0]);
}

TEST(VectorPushBackTest, MultiplePushBack) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  for (int i = 0; i < 100; ++i) {
    s21_vec.push_back(i);
    std_vec.push_back(i);
  }

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_GE(s21_vec.capacity(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorPushBackTest, Reallocation) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  size_t initial_capacity = s21_vec.capacity();
  for (size_t i = 0; i <= initial_capacity; ++i) {
    s21_vec.push_back(i);
    std_vec.push_back(i);
  }

  EXPECT_GT(s21_vec.capacity(), initial_capacity);
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorPushBackTest, NonTrivialType) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  s21_vec.push_back("first");
  s21_vec.push_back("second");
  std_vec.push_back("first");
  std_vec.push_back("second");

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorPushBackTest, CompareWithStdVectorGrowth) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  for (int i = 0; i < 1000; ++i) {
    s21_vec.push_back(i);
    std_vec.push_back(i);
    EXPECT_EQ(s21_vec.size(), std_vec.size());
    if (i % 100 == 0) {
      EXPECT_NEAR(s21_vec.capacity(), std_vec.capacity(),
                  std_vec.capacity() / 2);
    }
  }
}

TEST(VectorEraseTest, EraseFirstElement) {
  s21::vector<int> s21_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};

  s21_vec.erase(s21_vec.begin());
  std_vec.erase(std_vec.begin());

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec[0], std_vec[0]);
  EXPECT_EQ(s21_vec[1], std_vec[1]);
}

TEST(VectorEraseTest, EraseMiddleElement) {
  s21::vector<std::string> s21_vec = {"a", "b", "c", "d"};
  std::vector<std::string> std_vec = {"a", "b", "c", "d"};

  s21_vec.erase(s21_vec.begin() + 2);
  std_vec.erase(std_vec.begin() + 2);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec[0], std_vec[0]);
  EXPECT_EQ(s21_vec[1], std_vec[1]);
  EXPECT_EQ(s21_vec[2], std_vec[2]);
}

TEST(VectorEraseTest, EraseLastElement) {
  s21::vector<int> s21_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};

  s21_vec.erase(s21_vec.end() - 1);
  std_vec.erase(std_vec.end() - 1);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.back(), std_vec.back());
}

TEST(VectorEraseTest, EraseFromSingleElement) {
  s21::vector<int> s21_vec = {42};
  std::vector<int> std_vec = {42};

  s21_vec.erase(s21_vec.begin());
  std_vec.erase(std_vec.begin());

  EXPECT_TRUE(s21_vec.empty());
  EXPECT_TRUE(std_vec.empty());
}

TEST(VectorEraseTest, InvalidPosition) {
  s21::vector<std::string> s21_vec = {"one", "two", "three"};
  std::vector<std::string> std_vec = {"one", "two", "three"};

  s21_vec.erase(s21_vec.end() + 1);
  std_vec.erase(std_vec.end() + 1);

  for (size_t i = 0; i < std_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
}

TEST(VectorEraseTest, NonTrivialType) {
  s21::vector<std::string> s21_vec = {"one", "two", "three"};
  std::vector<std::string> std_vec = {"one", "two", "three"};

  s21_vec.erase(s21_vec.begin() + 1);
  std_vec.erase(std_vec.begin() + 1);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec[0], std_vec[0]);
  EXPECT_EQ(s21_vec[1], std_vec[1]);
}

TEST(VectorEraseTest, MultipleErase) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  for (int i = 0; i < 100; ++i) {
    s21_vec.push_back(i);
    std_vec.push_back(i);
  }

  for (int i = 0; i < 50; ++i) {
    s21_vec.erase(s21_vec.begin() + i);
    std_vec.erase(std_vec.begin() + i);
  }

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorInsertTest, InsertAtBeginning) {
  s21::vector<int> s21_vec = {2, 3, 4};
  std::vector<int> std_vec = {2, 3, 4};

  s21_vec.insert(s21_vec.begin(), 1);
  std_vec.insert(std_vec.begin(), 1);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorInsertTest, InsertAtMiddle) {
  s21::vector<std::string> s21_vec = {"a", "c", "d"};
  std::vector<std::string> std_vec = {"a", "c", "d"};

  auto s21_it = s21_vec.insert(s21_vec.begin() + 1, "b");
  auto std_it = std_vec.insert(std_vec.begin() + 1, "b");

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(*s21_it, *std_it);
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorInsertTest, InsertAtEnd) {
  s21::vector<int> s21_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};

  s21_vec.insert(s21_vec.end(), 4);
  std_vec.insert(std_vec.end(), 4);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.back(), std_vec.back());
}

TEST(VectorInsertTest, InsertToEmptyVector) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  s21_vec.insert(s21_vec.begin(), 42);
  std_vec.insert(std_vec.begin(), 42);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec[0], std_vec[0]);
}

TEST(VectorInsertTest, InsertWithReallocation) {
  s21::vector<int> s21_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};

  s21_vec.reserve(3);
  std_vec.reserve(3);

  s21_vec.insert(s21_vec.begin() + 1, 99);
  std_vec.insert(std_vec.begin() + 1, 99);

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorInsertTest, InvalidPosition) {
  s21::vector<int> s21_vec = {1, 2, 3};

  EXPECT_THROW(s21_vec.insert(s21_vec.end() + 1, 4), std::out_of_range);
  EXPECT_THROW(s21_vec.insert(s21_vec.begin() - 1, 0), std::out_of_range);
}

TEST(VectorInsertTest, ReturnValueCheck) {
  s21::vector<int> s21_vec = {10, 20, 30};
  std::vector<int> std_vec = {10, 20, 30};

  auto s21_it = s21_vec.insert(s21_vec.begin() + 1, 15);
  auto std_it = std_vec.insert(std_vec.begin() + 1, 15);

  EXPECT_EQ(*s21_it, *std_it);
  EXPECT_EQ(s21_it - s21_vec.begin(), std_it - std_vec.begin());
}

TEST(VectorInsertTest, MultipleInsertions) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  for (int i = 0; i < 100; ++i) {
    auto pos = s21_vec.begin() + (i % std::max<size_t>(1, s21_vec.size()));
    s21_vec.insert(pos, i);
    std_vec.insert(std_vec.begin() + (i % std::max<size_t>(1, std_vec.size())),
                   i);
  }

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

TEST(VectorSwapTest, SwapNonEmptyVectors) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6, 7};

  std::vector<int> std_v1 = {1, 2, 3};
  std::vector<int> std_v2 = {4, 5, 6, 7};

  v1.swap(v2);
  std_v1.swap(std_v2);

  EXPECT_EQ(v1.size(), std_v1.size());
  EXPECT_EQ(v2.size(), std_v2.size());
  EXPECT_EQ(v1.capacity(), std_v1.capacity());
  EXPECT_EQ(v2.capacity(), std_v2.capacity());

  for (size_t i = 0; i < v1.size(); ++i) EXPECT_EQ(v1[i], std_v1[i]);
  for (size_t i = 0; i < v2.size(); ++i) EXPECT_EQ(v2[i], std_v2[i]);
}

TEST(VectorSwapTest, SwapEmptyWithNonEmpty) {
  s21::vector<std::string> v1;
  s21::vector<std::string> v2 = {"a", "b", "c"};

  std::vector<std::string> std_v1;
  std::vector<std::string> std_v2 = {"a", "b", "c"};

  v1.swap(v2);
  std_v1.swap(std_v2);

  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v1[0], "a");
  EXPECT_EQ(v1[1], "b");
  EXPECT_EQ(v1[2], "c");
}

TEST(VectorSwapTest, SwapEmptyVectors) {
  s21::vector<double> v1;
  s21::vector<double> v2;

  std::vector<double> std_v1;
  std::vector<double> std_v2;

  v1.swap(v2);
  std_v1.swap(std_v2);

  EXPECT_TRUE(v1.empty());
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v1.capacity(), 0);
  EXPECT_EQ(v2.capacity(), 0);
}

TEST(VectorSwapTest, SwapSelf) {
  s21::vector<int> v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  v.swap(v);
  std_v.swap(std_v);

  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(VectorSwapTest, CheckIteratorsAfterSwap) {
  s21::vector<int> v1 = {1, 2};
  s21::vector<int> v2 = {3, 4, 5};

  auto it1 = v1.begin();
  auto it2 = v2.begin();

  v1.swap(v2);

  EXPECT_EQ(*it1, 1);
  EXPECT_EQ(*it2, 3);
}

TEST(VectorSwapTest, CompareWithStdVector) {
  s21::vector<int> s21_v1 = {1, 2};
  s21::vector<int> s21_v2 = {3, 4, 5};

  std::vector<int> std_v1 = {1, 2};
  std::vector<int> std_v2 = {3, 4, 5};

  s21_v1.swap(s21_v2);
  std_v1.swap(std_v2);

  EXPECT_EQ(s21_v1.size(), std_v1.size());
  EXPECT_EQ(s21_v2.size(), std_v2.size());
  for (size_t i = 0; i < s21_v1.size(); ++i) EXPECT_EQ(s21_v1[i], std_v1[i]);
  for (size_t i = 0; i < s21_v2.size(); ++i) EXPECT_EQ(s21_v2[i], std_v2[i]);
}

TEST(VectorSwapTest, NonTrivialType) {
  s21::vector<std::string> v1 = {"hello"};
  s21::vector<std::string> v2 = {"world", "test"};

  std::vector<std::string> std_v1 = {"hello"};
  std::vector<std::string> std_v2 = {"world", "test"};

  v1.swap(v2);
  std_v1.swap(std_v2);

  EXPECT_EQ(v1.size(), std_v1.size());
  EXPECT_EQ(v2.size(), std_v2.size());
  for (size_t i = 0; i < v1.size(); ++i) EXPECT_EQ(v1[i], std_v1[i]);
  for (size_t i = 0; i < v2.size(); ++i) EXPECT_EQ(v2[i], std_v2[i]);
}

TEST(VectorClearTest, ClearNonEmptyVector) {
  s21::vector<int> s21_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};

  s21_vec.clear();
  std_vec.clear();

  EXPECT_TRUE(s21_vec.empty());
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_GE(s21_vec.capacity(), std_vec.capacity());
}

TEST(VectorClearTest, ClearEmptyVector) {
  s21::vector<int> s21_vec;
  std::vector<int> std_vec;

  s21_vec.clear();
  std_vec.clear();

  EXPECT_TRUE(s21_vec.empty());
  EXPECT_EQ(s21_vec.size(), std_vec.size());
}

TEST(VectorClearTest, ClearNonTrivialType) {
  s21::vector<std::string> s21_vec = {"hello", "world"};
  std::vector<std::string> std_vec = {"hello", "world"};

  s21_vec.clear();
  std_vec.clear();

  EXPECT_TRUE(s21_vec.empty());
  EXPECT_EQ(s21_vec.size(), std_vec.size());
}

TEST(VectorClearTest, CapacityAfterClear) {
  s21::vector<int> s21_vec(10);
  std::vector<int> std_vec(10);

  size_t old_capacity = s21_vec.capacity();
  s21_vec.clear();
  std_vec.clear();

  EXPECT_EQ(s21_vec.capacity(), old_capacity);
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
}

TEST(VectorClearTest, ReuseAfterClear) {
  s21::vector<int> s21_vec = {1, 2, 3};
  s21_vec.clear();

  s21_vec.push_back(4);
  s21_vec.push_back(5);

  EXPECT_EQ(s21_vec.size(), 2);
  EXPECT_EQ(s21_vec[0], 4);
  EXPECT_EQ(s21_vec[1], 5);
}

TEST(VectorClearTest, MemoryDeallocation) {
  s21::vector<int> s21_vec(100);
  int* old_data = s21_vec.data();

  s21_vec.clear();
  s21_vec.shrink_to_fit();

  EXPECT_NE(s21_vec.data(), old_data);
  EXPECT_EQ(s21_vec.capacity(), 0);
}

TEST(VectorClearTest, CompareWithStdVector) {
  s21::vector<int> s21_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};

  s21_vec.clear();
  std_vec.clear();

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.empty(), std_vec.empty());
  EXPECT_GE(s21_vec.capacity(), std_vec.capacity());
}

TEST(VectorPopBackTest, PopFromNonEmpty) {
  s21::vector<int> s21_vec = {1, 2, 3};
  std::vector<int> std_vec = {1, 2, 3};

  s21_vec.pop_back();
  std_vec.pop_back();

  EXPECT_EQ(s21_vec.size(), 2);
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.back(), std_vec.back());
}

TEST(VectorPopBackTest, PopFromSingleElement) {
  s21::vector<std::string> s21_vec = {"hello"};
  std::vector<std::string> std_vec = {"hello"};

  s21_vec.pop_back();
  std_vec.pop_back();

  EXPECT_TRUE(s21_vec.empty());
  EXPECT_EQ(s21_vec.size(), std_vec.size());
}

TEST(VectorPopBackTest, MultiplePops) {
  s21::vector<int> s21_vec = {1, 2, 3, 4, 5};
  std::vector<int> std_vec = {1, 2, 3, 4, 5};

  for (int i = 0; i < 3; ++i) {
    s21_vec.pop_back();
    std_vec.pop_back();
  }

  EXPECT_EQ(s21_vec.size(), 2);
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.back(), std_vec.back());
}

TEST(VectorPopBackTest, NonTrivialType) {
  s21::vector<std::string> s21_vec = {"one", "two", "three"};
  std::vector<std::string> std_vec = {"one", "two", "three"};

  s21_vec.pop_back();
  std_vec.pop_back();

  EXPECT_EQ(s21_vec.size(), 2);
  EXPECT_EQ(s21_vec.back(), "two");
  EXPECT_EQ(s21_vec.back(), std_vec.back());
}

TEST(VectorPopBackTest, CapacityAfterPop) {
  s21::vector<int> s21_vec = {1, 2, 3};
  size_t old_capacity = s21_vec.capacity();

  s21_vec.pop_back();

  EXPECT_EQ(s21_vec.capacity(), old_capacity);
}

TEST(VectorPopBackTest, PopFromEmpty) {
  s21::vector<int> s21_vec;

  EXPECT_NO_THROW(s21_vec.pop_back());
  EXPECT_TRUE(s21_vec.empty());
}

TEST(VectorPopBackTest, CompareWithStdVector) {
  s21::vector<int> s21_vec = {10, 20, 30, 40};
  std::vector<int> std_vec = {10, 20, 30, 40};

  s21_vec.pop_back();
  std_vec.pop_back();

  EXPECT_EQ(s21_vec.size(), std_vec.size());
  for (size_t i = 0; i < s21_vec.size(); ++i) {
    EXPECT_EQ(s21_vec[i], std_vec[i]);
  }
}

// int main(int argc, char** argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }