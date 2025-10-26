#include "s21_matrix_oop.h"

void S21Matrix::AllocMem(int rows, int cols) {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{};
  }
}

void S21Matrix::ResizeMatrix(int new_rows, int new_cols) {
  S21Matrix tmp(new_rows, new_cols);

  for (int i = 0; i < std::min(rows_, new_rows); ++i) {
    for (int j = 0; j < std::min(cols_, new_cols); ++j) {
      tmp.matrix_[i][j] = this->matrix_[i][j];
    }
  }
  this->~S21Matrix();
  this->rows_ = new_rows;
  this->cols_ = new_cols;
  this->AllocMem(new_rows, new_cols);
  for (int i = 0; i < std::min(rows_, new_rows); ++i) {
    for (int j = 0; j < std::min(cols_, new_cols); ++j) {
      this->matrix_[i][j] = tmp.matrix_[i][j];
    }
  }
}

double S21Matrix::Minor(int row, int col) {
  double res = 1.0;
  int count_i = 0, count_j = 0;
  if (rows_ == 1) {
    throw std::out_of_range("Incorrect input, matrix should be more than 1x1");
  }

  S21Matrix tmp(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i != row && j != col) {
        if (count_j < cols_ - 1) {
          tmp(count_i, count_j) = matrix_[i][j];
          ++count_j;
        } else {
          count_j = 0;
          ++count_i;
          tmp(count_i, count_j) = matrix_[i][j];
          ++count_j;
        }
      }
    }
  }
  res = tmp.Determinant();
  return res;
}

int S21Matrix::GetRows() { return rows_; }
int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows <= 0) {
    throw std::out_of_range("ROWS MUST BE > 0");
  } else if (rows != rows_) {
    this->ResizeMatrix(rows, cols_);
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0) {
    throw std::out_of_range("COLS MUST BE > 0");
  } else if (cols != cols_) {
    this->ResizeMatrix(rows_, cols);
  }
}