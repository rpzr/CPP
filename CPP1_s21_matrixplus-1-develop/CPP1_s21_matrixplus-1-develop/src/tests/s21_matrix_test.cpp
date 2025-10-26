#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

void FillMatrix(S21Matrix& matrix,
                std::initializer_list<std::initializer_list<double>> values) {
  int i = 0;
  for (auto row : values) {
    int j = 0;
    for (auto value : row) {
      matrix(i, j) = value;
      ++j;
    }
    ++i;
  }
}

TEST(MatrixTest, DefaultInit) {
  S21Matrix test;
  EXPECT_EQ(test.GetRows(), 3);
  EXPECT_EQ(test.GetCols(), 3);
}

TEST(MatrixTest, ParametrInit) {
  int rows = 1, cols = 1;
  S21Matrix test(rows, cols);

  ASSERT_EQ(test.GetRows(), rows);
  ASSERT_EQ(test.GetCols(), cols);
}

TEST(MatrixTest, ValueInit) {
  int rows = 2, cols = 2;
  S21Matrix test(rows, cols);

  ASSERT_EQ(test.GetRows(), rows);
  ASSERT_EQ(test.GetCols(), cols);

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      EXPECT_EQ(test(row, col), 0);
    }
  }
}

TEST(MatrixTest, CopyInit) {
  int rows = 4, cols = 4;
  S21Matrix test1(rows, cols);
  test1(1, 2) = 5;
  S21Matrix test2(test1);

  ASSERT_EQ(test2.GetRows(), rows);
  ASSERT_EQ(test2.GetCols(), cols);

  for (int row = 0; row < rows; ++row) {
    for (int col = 0; col < cols; ++col) {
      EXPECT_EQ(test2(row, col), test1(row, col));
    }
  }
}

TEST(MatrixTest, MoveInit) {
  int rows = 4, cols = 4;
  S21Matrix test1(rows, cols);
  test1(1, 1) = 8;
  S21Matrix test2(*&test1);

  ASSERT_EQ(test2.GetRows(), rows);
  ASSERT_EQ(test2.GetCols(), cols);

  EXPECT_EQ(test2(1, 1), 8);
}
TEST(MatrixTest, InvalidConstructor) {
  EXPECT_THROW(S21Matrix(-3, 3), std::out_of_range);
  EXPECT_THROW(S21Matrix(0, 3), std::out_of_range);
}

TEST(MatrixTest, SetCols_GetCols3_2) {
  S21Matrix m1(3, 3);
  FillMatrix(m1, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  m1.SetCols(2);

  S21Matrix res(3, 2);
  FillMatrix(res, {{1, 2}, {4, 5}, {7, 8}});
  EXPECT_EQ(m1.GetCols(), 2);

  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 2; ++col) {
      EXPECT_EQ(m1(row, col), res(row, col));
    }
  }
}

TEST(MatrixTest, SetCols_GetCols_2_3) {
  S21Matrix m1(2, 2);
  FillMatrix(m1, {{1, 2}, {3, 4}});
  m1.SetCols(3);

  S21Matrix res(2, 3);
  FillMatrix(res, {{1, 2, 0}, {3, 4, 0}});
  EXPECT_EQ(m1.GetCols(), 3);

  for (int row = 0; row < 2; ++row) {
    for (int col = 0; col < 3; ++col) {
      EXPECT_EQ(m1(row, col), res(row, col));
    }
  }
}

TEST(MatrixTest, SetRows_GetRows_3_2) {
  S21Matrix m1(3, 3);
  FillMatrix(m1, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
  m1.SetRows(2);

  S21Matrix res(2, 3);
  FillMatrix(res, {{1, 2, 3}, {4, 5, 6}});
  EXPECT_EQ(m1.GetRows(), 2);

  for (int row = 0; row < 2; ++row) {
    for (int col = 0; col < 3; ++col) {
      EXPECT_EQ(m1(row, col), res(row, col));
    }
  }
}

TEST(MatrixTest, SetRows_GetRows_2_3) {
  S21Matrix m1(2, 2);
  FillMatrix(m1, {{1, 2}, {3, 4}});
  m1.SetRows(3);

  S21Matrix res(3, 2);
  FillMatrix(res, {{1, 2}, {3, 4}, {0, 0}});
  EXPECT_EQ(m1.GetRows(), 3);

  for (int row = 0; row < 3; ++row) {
    for (int col = 0; col < 2; ++col) {
      EXPECT_EQ(m1(row, col), res(row, col));
    }
  }
}

TEST(MatrixTest, EqMatrixTrue) {
  S21Matrix m1(2, 2), m2(2, 2);
  FillMatrix(m1, {{1, 2}, {3, 4}});
  FillMatrix(m2, {{1, 2}, {3, 4}});
  EXPECT_TRUE(m1.EqMatrix(m2));
}

TEST(MatrixTest, EqMatrixFalse) {
  S21Matrix m1(2, 2), m2(2, 2);
  FillMatrix(m1, {{1, 2}, {3, 4}});
  FillMatrix(m2, {{4, 3}, {2, 1}});
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(MatrixTest, EqMatrixDifferentSizes) {
  S21Matrix m1(2, 2), m2(3, 3);
  EXPECT_FALSE(m1.EqMatrix(m2));
}

TEST(MatrixTest, SumMatrix) {
  S21Matrix m1(2, 2), m2(2, 2);
  FillMatrix(m1, {{1, 2}, {3, 4}});
  FillMatrix(m2, {{5, 6}, {7, 8}});
  m1.SumMatrix(m2);
  EXPECT_EQ(m1(0, 0), 6.0);
  EXPECT_EQ(m1(1, 1), 12.0);
}

TEST(MatrixTest, SumMatrixInvalidSize) {
  S21Matrix m1(2, 2), m2(3, 3);
  EXPECT_THROW(m1.SumMatrix(m2), std::out_of_range);
}
TEST(MatrixTest, SubMatrix) {
  S21Matrix m1(2, 2), m2(2, 2);
  FillMatrix(m1, {{5, 6}, {7, 8}});
  FillMatrix(m2, {{1, 2}, {3, 4}});
  m1.SubMatrix(m2);
  EXPECT_EQ(m1(0, 0), 4.0);
  EXPECT_EQ(m1(1, 1), 4.0);
}

TEST(MatrixTest, SubMatrixInvalidSize) {
  S21Matrix m1(2, 2), m2(3, 3);
  EXPECT_THROW(m1.SubMatrix(m2), std::out_of_range);
}

TEST(MatrixTest, MulNumber) {
  S21Matrix m(2, 2);
  FillMatrix(m, {{1, 2}, {3, 4}});
  m.MulNumber(2.0);
  EXPECT_EQ(m(0, 0), 2.0);
  EXPECT_EQ(m(1, 1), 8.0);
}

TEST(MatrixTest, MulMatrix) {
  S21Matrix m1(2, 3), m2(3, 2);
  FillMatrix(m1, {{1, 2, 3}, {4, 5, 6}});
  FillMatrix(m2, {{7, 8}, {9, 10}, {11, 12}});
  m1.MulMatrix(m2);
  EXPECT_EQ(m1(0, 0), 58);
  EXPECT_EQ(m1(1, 1), 154);
}

TEST(MatrixTest, MulMatrixInvalidSize) {
  S21Matrix m1(2, 2), m2(3, 3);
  EXPECT_THROW(m1.MulMatrix(m2), std::invalid_argument);
}

TEST(MatrixTest, Transpose) {
  S21Matrix m(2, 3);
  FillMatrix(m, {{1, 2, 3}, {4, 5, 6}});
  S21Matrix transposed = m.Transpose();
  EXPECT_EQ(transposed.GetRows(), 3);
  EXPECT_EQ(transposed.GetCols(), 2);
  EXPECT_EQ(transposed(0, 1), 4.0);
}

TEST(MatrixTest, Determinant2x2) {
  S21Matrix m(2, 2);
  FillMatrix(m, {{4, 7}, {2, 6}});
  EXPECT_EQ(m.Determinant(), 10.0);
}

TEST(MatrixTest, Determinant3x3) {
  S21Matrix m(3, 3);
  FillMatrix(m, {{6, 1, 1}, {4, -2, 5}, {2, 8, 7}});
  EXPECT_EQ(m.Determinant(), -306.0);
}

TEST(MatrixTest, DeterminantNonSquare) {
  S21Matrix m(2, 3);
  EXPECT_THROW(m.Determinant(), std::invalid_argument);
}

TEST(MatrixTest, CalcComplements) {
  S21Matrix m(3, 3);
  FillMatrix(m, {{1, 2, 3}, {0, 4, 5}, {1, 0, 6}});
  S21Matrix complements = m.CalcComplements();
  EXPECT_EQ(complements(0, 0), 24.0);
  EXPECT_EQ(complements(0, 1), 5.0);
  EXPECT_EQ(complements(0, 2), -4.0);
}

TEST(MatrixTest, CalcComplementsNonSquare) {
  S21Matrix m(2, 3);
  EXPECT_THROW(m.CalcComplements(), std::invalid_argument);
}

TEST(MatrixTest, InverseMatrix) {
  S21Matrix m(2, 2);
  FillMatrix(m, {{4, 7}, {2, 6}});
  S21Matrix inverse = m.InverseMatrix();
  EXPECT_NEAR(inverse(0, 0), 0.6, 1e-7);
  EXPECT_NEAR(inverse(0, 1), -0.7, 1e-7);
  EXPECT_NEAR(inverse(1, 0), -0.2, 1e-7);
  EXPECT_NEAR(inverse(1, 1), 0.4, 1e-7);
}

TEST(MatrixTest, InverseMatrixZeroDeterminant) {
  S21Matrix m(2, 2);
  FillMatrix(m, {{1, 2}, {2, 4}});
  EXPECT_THROW(m.InverseMatrix(), std::logic_error);
}