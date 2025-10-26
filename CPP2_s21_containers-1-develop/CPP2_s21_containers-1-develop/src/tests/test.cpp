#include <gtest/gtest.h>

#include "s21_test_array.cpp"
#include "s21_test_list.cpp"
#include "s21_test_map.cpp"
#include "s21_test_multiset.cpp"
#include "s21_test_part3.cpp"
#include "s21_test_queue.cpp"
#include "s21_test_set.cpp"
#include "s21_test_stack.cpp"
#include "s21_test_vector.cpp"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}