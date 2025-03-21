#include "s21_matrix_oop.h"

template <int rows, int cols>
float& S21Matrix<rows, cols>::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Matrix index out of range");
  }
  return matrix_[row * cols_ + col];
}

template <int rows, int cols>
const float& S21Matrix<rows, cols>::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Matrix index out of range");
  }
  return matrix_[row * cols_ + col];
}

template <int rows, int cols>
S21Matrix<rows, cols>& S21Matrix<rows, cols>::operator=(
    const S21Matrix& other) {
  if (this != &other) {
    for (int i = 0; i < rows_ * cols_; i++) {
      matrix_[i] = other.matrix_[i];
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
  }
  return *this;
}

template <int rows, int cols>
S21Matrix<rows, cols>& S21Matrix<rows, cols>::operator=(
    S21Matrix&& other) noexcept {
  if (this != &other) {
    for (int i = 0; i < rows_ * cols_; i++) {
      matrix_[i] = other.matrix_[i];
    }
    rows_ = other.rows_;
    cols_ = other.cols_;

    other.rows_ = 0;
    other.cols_ = 0;
  }
  return *this;
}

template <int rows, int cols>
S21Matrix<rows, cols> S21Matrix<rows, cols>::operator+(
    const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

template <int rows, int cols>
S21Matrix<rows, cols> S21Matrix<rows, cols>::operator-(
    const S21Matrix& other) const {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

template <int rows, int cols>
template <int other_rows, int other_cols>
S21Matrix<rows, other_cols> S21Matrix<rows, cols>::operator*(
    const S21Matrix<other_rows, other_cols>& other) const {
  S21Matrix<rows, other_cols> result;

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.GetCols(); j++) {
      for (int k = 0; k < this->cols_; k++) {
        result(i, j) += this->matrix_[i * cols_ + k] * other(k, j);
      }
    }
  }

  return result;
}

template <int rows, int cols>
S21Matrix<rows, cols> S21Matrix<rows, cols>::operator*(const float num) const {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

template <int rows, int cols>
bool S21Matrix<rows, cols>::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

template <int rows, int cols>
void S21Matrix<rows, cols>::operator+=(const S21Matrix& other) {
  SumMatrix(other);
}

template <int rows, int cols>
void S21Matrix<rows, cols>::operator-=(const S21Matrix& other) {
  SubMatrix(other);
}

template <int rows, int cols>
void S21Matrix<rows, cols>::operator*=(const S21Matrix& other) {
  MulQuadMatrix(other);
}

template <int rows, int cols>
void S21Matrix<rows, cols>::operator*=(const float num) {
  MulNumber(num);
}