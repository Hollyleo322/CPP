#include "s21_matrix_oop.h"

// constructors

template <int rows, int cols>
S21Matrix<rows, cols>::S21Matrix() : rows_(rows), cols_(cols) {
  CreateMatrix();
}

template <int rows, int cols>
void S21Matrix<rows, cols>::CreateMatrix() {
  for (int i = 0; i < rows_ * cols_; i++) {
    matrix_[i] = 0;
  }
}

template <int rows, int cols>
S21Matrix<rows, cols>::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
}

template <int rows, int cols>
S21Matrix<rows, cols>::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_) {
  for (int i = 0; i < rows_ * cols_; i++) {
    matrix_[i] = other.matrix_[i];
  }
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.rows_ = 0;
  other.cols_ = 0;
}

// subfunc

template <int rows, int cols>
bool S21Matrix<rows, cols>::IsSameMatrixSize(const S21Matrix& other) const {
  bool rule1 = this->rows_ == other.rows_;
  bool rule2 = this->cols_ == other.cols_;
  return rule1 && rule2;
}

template <int rows, int cols>
bool S21Matrix<rows, cols>::IsSquareMatrix() const {
  bool res = false;
  if (this->rows_ == this->cols_ && this->rows_ > 0) res = true;
  return res;
}

// main func

template <int rows, int cols>
bool S21Matrix<rows, cols>::EqMatrix(const S21Matrix& other) const {
  bool res = true;
  bool breakFlag = false;
  if (IsSameMatrixSize(other)) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (this->matrix_[i * cols_ + j] !=
            other.matrix_[i * other.cols_ + j]) {
          breakFlag = true;
          break;
        }
      }
      if (breakFlag) break;
    }
  } else {
    res = false;
  }
  return res;
}

template <int rows, int cols>
void S21Matrix<rows, cols>::SumMatrix(const S21Matrix& other) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i * cols_ + j] += other.matrix_[i * other.cols_ + j];
    }
  }
}

template <int rows, int cols>
void S21Matrix<rows, cols>::SubMatrix(const S21Matrix& other) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i * cols_ + j] -= other.matrix_[i * other.cols_ + j];
    }
  }
}

template <int rows, int cols>
void S21Matrix<rows, cols>::MulNumber(const float num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i * cols_ + j] *= num;
    }
  }
}

template <int rows, int cols>
void S21Matrix<rows, cols>::MulQuadMatrix(const S21Matrix& other) {
  static_assert(rows == cols, "Matrix must be square");
  S21Matrix result;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[i * result.cols_ + j] +=
            this->matrix_[i * cols_ + k] * other.matrix_[k * other.cols_ + j];
      }
    }
  }
  *this = result;
}

template <int rows, int cols>
S21Matrix<rows, cols> S21Matrix<rows, cols>::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j * result.cols_ + i] = matrix_[i * cols_ + j];
    }
  }
  return result;
}

// getter setter

template <int rows, int cols>
int S21Matrix<rows, cols>::GetRows() const {
  return this->rows_;
}

template <int rows, int cols>
int S21Matrix<rows, cols>::GetCols() const {
  return this->cols_;
}
