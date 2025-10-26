#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool res = true;
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    res = false;
  }
  for (int i = 0; i < rows_ && res; ++i) {
    for (int j = 0; j < cols_ && res; ++j) {
      if ((std::fabs(matrix_[i][j] - other.matrix_[i][j])) > 1e-7) {
        res = false;
      }
    }
  }
  return res;
}
void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("SIZE MUST BE THE SAME");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::out_of_range("SIZE MUST BE THE SAME");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }
}
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}
void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("COLS of 1 MATRIX != ROWS of 2 MATRIX!");
  }
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(res);
}
S21Matrix S21Matrix::Transpose() {
  S21Matrix res(this->cols_, this->rows_);
  for (int i = 0; i < res.rows_; ++i) {
    for (int j = 0; j < res.cols_; ++j) {
      res(i, j) = matrix_[j][i];
    }
  }
  return res;
}
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("ROWS MUST = COLS");
  }
  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = matrix_[0][0];
  } else {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        res.matrix_[i][j] = pow(-1.0, i + j) * this->Minor(i, j);
      }
    }
  }
  return res;
}
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("ROWS MUST = COLS");
  }

  double det = 0.0;
  if (rows_ == 1) {
    det = matrix_[0][0];
  } else if (rows_ == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int j = 0; j < cols_; ++j) {
      det += pow(-1, j) * matrix_[0][j] * Minor(0, j);
    }
  }
  return det;
}
S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::out_of_range("ROWS MUST = COLS");
  }
  double det = this->Determinant();
  if (det == 0.0) {
    throw std::logic_error("DETERMINANT = 0. INVERSE MATRIX DOESNT EXISTS");
  }
  S21Matrix res(rows_, cols_);
  if (rows_ == 1) {
    res.matrix_[0][0] = 1.0 / matrix_[0][0];
  } else {
    res = this->CalcComplements();
    res = res.Transpose();
    res = (1.0 / det) * res;
  }
  return res;
}