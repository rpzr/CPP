#include "s21_matrix_oop.h"

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range("COLS of 1 MATRIX != ROWS of 2 MATRIX!");
  } else {
    S21Matrix res(rows_, other.cols_);
    res.MulMatrix(other);
    return res;
  }
}
S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    this->ResizeMatrix(other.rows_, other.cols_);
  }
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}
S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Size of matrices must be the same!");
  } else {
    this->SumMatrix(other);
  }
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("Size of matrices must be the same!");
  } else {
    this->SubMatrix(other);
  }
  return *this;
}
S21Matrix &S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}
S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range("COLS of 1 MATRIX != ROWS of 2 MATRIX!");
  } else {
    this->MulMatrix(other);
  }
  return *this;
}

double &S21Matrix::operator()(int rows, int cols) {
  if (rows >= rows_ || cols >= cols_ || rows < 0 || cols < 0) {
    throw std::out_of_range("ROWS or COLS out of range");
  }
  return matrix_[rows][cols];
}

S21Matrix operator*(double num, S21Matrix &matrix) { return matrix * num; }