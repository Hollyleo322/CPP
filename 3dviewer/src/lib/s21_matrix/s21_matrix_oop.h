#pragma once
#include <algorithm>
#include <stdexcept>

template <int rows, int cols>
class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  float matrix_[rows * cols];
  void CreateMatrix();
  bool IsSameMatrixSize(const S21Matrix& other) const;
  bool IsSquareMatrix() const;

 public:
  S21Matrix();  // Default constructor
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() = default;

  template <int other_rows, int other_cols>
  void copyTo(S21Matrix<other_rows, other_cols>& other) const;

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const float num);
  void MulQuadMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;

  int GetRows() const;
  int GetCols() const;

  float& operator()(int row, int col);
  const float& operator()(int row, int col) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  template <int other_rows, int other_cols>
  S21Matrix<rows, other_cols> operator*(
      const S21Matrix<other_rows, other_cols>& other) const;
  S21Matrix operator*(const float num) const;
  bool operator==(const S21Matrix& other) const;
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  void operator*=(const float num);
};

#include "s21_matrix_oop.tpp"
#include "s21_matrix_oop_operators.tpp"
