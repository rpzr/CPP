#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <stdexcept>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;

 public:
  S21Matrix();  // Базовый конструктор для дефолтной размерности
  S21Matrix(int rows, int cols);  // Конструктор с размерностями
  S21Matrix(const S21Matrix& other);  // Конструктор копирования
  S21Matrix(S21Matrix&& other);  // Конструктор переноса

  ~S21Matrix();  // Деструктор

  // Helpers
  void AllocMem(int rows, int cols);
  void ResizeMatrix(int rows, int cols);
  double Minor(int row, int col);

  // Accessors, mutators
  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int rows);

  // Methods
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // Overloads

  // ==, -, +, *(num), *(matrix)
  bool operator==(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  friend S21Matrix operator*(double num, S21Matrix& other);

  // =, +=, -=, *=(num), *=(matrix)
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);

  // Index out of range
  double& operator()(int rows, int cols);
};

#endif