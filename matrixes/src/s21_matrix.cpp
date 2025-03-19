#include "s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->columns_ != other.columns_) {
    return false;
  }
  bool res = true;
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.columns_; j++) {
      if (fabs(this->matrix[i][j] - other.matrix[i][j]) > 1e-7) {
        res = false;
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->columns_ != other.columns_) {
    throw S21Matrix_exception("different matrix dimensions", 2);
  } else {
    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.columns_; j++) {
        this->matrix[i][j] += other.matrix[i][j];
      }
    }
  }
}
void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->columns_ != other.columns_) {
    throw S21Matrix_exception("different matrix dimensions", 2);
  } else {
    for (int i = 0; i < other.rows_; i++) {
      for (int j = 0; j < other.columns_; j++) {
        this->matrix[i][j] -= other.matrix[i][j];
      }
    }
  }
}
void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->columns_; j++) {
      this->matrix[i][j] *= num;
    }
  }
}
double multymatrix(double **first, double **second, int row, int column,
                   int value_for_cycle) {
  double res = 0, tmp = 0;
  for (int i = 0; i < value_for_cycle; i++) {
    tmp = first[row][i] * second[i][column];
    res += tmp;
  }
  return res;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->columns_ != other.rows_) {
    throw S21Matrix_exception(
        "Number of columns first matrix not equal number of rows second matrix",
        2);
  } else {
    S21Matrix tmp(this->rows_, other.columns_);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < other.columns_; j++) {
        tmp.matrix[i][j] =
            multymatrix(this->matrix, other.matrix, i, j, this->columns_);
      }
    }
    *this = tmp;
  }
}
void S21Matrix::set_matrix(double array[], int size) {
  if (size < this->columns_ * this->rows_) {
    throw S21Matrix_exception("incorrect dimension array of ints", 2);
  } else {
    int count = 0;
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->columns_; j++) {
        this->matrix[i][j] = array[count];
        count += 1;
      }
    }
  }
}
void S21Matrix::alloc_memory_for_matrix(S21Matrix &other) {
  if (other.rows_ && other.columns_) {
    matrix = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
      matrix[i] = new double[columns_];
    }
  }
}
S21Matrix S21Matrix::Transpose() {
  S21Matrix transpose_matrix(this->columns_, this->rows_);
  for (int i = 0; i < this->columns_; i++) {
    for (int j = 0; j < this->rows_; j++) {
      transpose_matrix.matrix[i][j] = this->matrix[j][i];
    }
  }
  return transpose_matrix;
}
S21Matrix S21Matrix::MinorMatrix(S21Matrix &var, int row, int col) {
  S21Matrix minor(var.get_rows() - 1, var.get_columns() - 1);
  int k = 0, s = 0;
  for (int i = 0; i < var.get_rows(); i++) {
    if (i == row) {
      continue;
    }
    s = 0;
    for (int j = 0; j < var.get_columns(); j++) {
      if (j != col) {
        minor.get_matrix()[k][s] = var.get_matrix()[i][j];
        s += 1;
      }
    }
    k += 1;
  }
  return minor;
}
double S21Matrix::Determinant() {
  double res = 0;
  if (this->rows_ != this->columns_) {
    throw S21Matrix_exception("rows not equal columns", 2);
  } else {
    res = get_determinant();
  }
  return res;
}
const S21Matrix &S21Matrix::operator=(const S21Matrix &var) {
  if (this == &var) {
    return var;
  }
  free_memory(*this);
  this->rows_ = var.rows_;
  this->columns_ = var.columns_;
  alloc_memory_for_matrix(*this);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->columns_; j++) {
      this->matrix[i][j] = var.matrix[i][j];
    }
  }
  return *this;
}
S21Matrix S21Matrix::operator+(const S21Matrix &var) {
  S21Matrix res(this->rows_, this->columns_);
  if (this->rows_ == var.rows_ && this->columns_ == var.columns_) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->columns_; j++) {
        res.matrix[i][j] = this->matrix[i][j] + var.matrix[i][j];
      }
    }
  } else {
    throw S21Matrix_exception("different matrix dimensions", 2);
  }
  return res;
}
S21Matrix S21Matrix::operator-(const S21Matrix &var) {
  S21Matrix res(this->rows_, this->columns_);
  if (this->rows_ == var.rows_ && this->columns_ == var.columns_) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->columns_; j++) {
        res.matrix[i][j] = this->matrix[i][j] - var.matrix[i][j];
      }
    }
  } else {
    throw S21Matrix_exception("different matrix dimensions", 2);
  }
  return res;
}
S21Matrix S21Matrix::operator*(const S21Matrix &var) {
  S21Matrix res(this->rows_, var.columns_);
  if (this->columns_ == var.rows_) {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < var.columns_; j++) {
        res.matrix[i][j] =
            multymatrix(this->matrix, var.matrix, i, j, this->columns_);
      }
    }
  } else {
    throw S21Matrix_exception(
        "Number of columns first matrix not equal number of rows second matrix",
        2);
  }
  return res;
}
S21Matrix S21Matrix::operator*(const double value) {
  S21Matrix res(this->rows_, this->columns_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->columns_; j++) {
      res.matrix[i][j] = this->matrix[i][j] * value;
    }
  }
  return res;
}
bool S21Matrix::operator==(const S21Matrix &var) { return this->EqMatrix(var); }
const S21Matrix &S21Matrix::operator+=(const S21Matrix &var) {
  if (this->rows_ == var.rows_ && this->columns_ == var.columns_) {
    this->SumMatrix(var);
  } else {
    throw S21Matrix_exception("different matrix dimensions", 2);
  }
  return *this;
}
const S21Matrix &S21Matrix::operator-=(const S21Matrix &var) {
  if (this->rows_ == var.rows_ && this->columns_ == var.columns_) {
    this->SubMatrix(var);
  } else {
    throw S21Matrix_exception("different matrix dimensions", 2);
  }
  return *this;
}
const S21Matrix &S21Matrix::operator*=(const S21Matrix &var) {
  if (this->columns_ == var.rows_) {
    this->MulMatrix(var);
  } else {
    throw S21Matrix_exception(
        "Number of columns first matrix not equal number of rows second matrix",
        2);
  }
  return *this;
}
const S21Matrix &S21Matrix::operator*=(const double var) {
  this->MulNumber(var);
  return *this;
}
double S21Matrix::operator()(int i, int j) {
  double res = 0;
  if (i * j > this->rows_ * this->columns_) {
    throw S21Matrix_exception("index is out of range", 2);
  } else {
    res = this->matrix[i][j];
  }
  return res;
}
void S21Matrix::free_memory(S21Matrix &other) {
  if (other.matrix) {
    for (int i = 0; i < other.rows_; i++) {
      delete[] other.matrix[i];
    }
    delete[] other.matrix;
  }
}
double S21Matrix::get_determinant() {
  double res = 0;
  int sign = -1;
  if (this->rows_ == 2 && this->columns_ == 2) {
    res = this->matrix[0][0] * this->matrix[1][1] -
          this->matrix[0][1] * this->matrix[1][0];
  } else if (this->rows_ == 1 && this->columns_ == 1) {
    res = this->matrix[0][0];
  } else {
    for (int i = 0; i < this->columns_; i++) {
      S21Matrix minor = MinorMatrix(*this, 0, i);
      res += pow(sign, i) * this->matrix[0][i] * minor.get_determinant();
    }
  }
  return res;
}
S21Matrix S21Matrix::CalcComplements() {
  S21Matrix res;
  if (this->rows_ != this->columns_) {
    throw S21Matrix_exception("rows not equal columns", 2);
  } else if (this->rows_ > 1 && this->columns_ > 1) {
    S21Matrix tmp(this->rows_, this->columns_);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->columns_; j++) {
        S21Matrix minor = MinorMatrix(*this, i, j);
        tmp.matrix[i][j] = minor.get_determinant();
        tmp.matrix[i][j] *= pow(-1, i + j);
      }
    }
    res = tmp;
  } else if (this->rows_ == 1 && this->columns_ == 1) {
    res.matrix[0][0] = this->matrix[0][0];
  }
  return res;
}
S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix res;
  if (this->get_determinant() == 0) {
    throw S21Matrix_exception("determinant is equal to zero", 2);
  } else if (this->rows_ == 1 && this->columns_ == 1) {
    res.matrix[0][0] = 1 / this->get_determinant();
  } else {
    S21Matrix comp, transpose;
    double deter = this->get_determinant();
    comp = this->CalcComplements();
    transpose = comp.Transpose();
    transpose.MulNumber(1 / deter);
    res = transpose;
  }
  return res;
}
void S21Matrix::set_rows(int num) {
  if (num > this->rows_) {
    S21Matrix res(num, this->columns_);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->columns_; j++) {
        res.matrix[i][j] = this->matrix[i][j];
      }
    }
    for (int i = this->rows_; i < num; i++) {
      for (int j = 0; j < this->columns_; j++) {
        res.matrix[i][j] = 0;
      }
    }
    *this = res;
  } else if (num < this->rows_ && num) {
    S21Matrix res(num, this->columns_);
    for (int i = 0; i < num; i++) {
      for (int j = 0; j < this->columns_; j++) {
        res.matrix[i][j] = this->matrix[i][j];
      }
    }
    *this = res;
  } else {
    return;
  }
}
void S21Matrix::set_columns(int num) {
  if (num > this->columns_) {
    S21Matrix res(this->rows_, num);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < num; j++) {
        if (j >= this->columns_) {
          res.matrix[i][j] = 0;
        } else {
          res.matrix[i][j] = this->matrix[i][j];
        }
      }
    }
    *this = res;
  } else if (num < this->columns_ && num) {
    S21Matrix res(this->rows_, num);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < num; j++) {
        res.matrix[i][j] = this->matrix[i][j];
      }
    }
    *this = res;
  } else {
    return;
  }
}
void S21Matrix::init_zeros() {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->columns_; j++) {
      this->matrix[i][j] = 0;
    }
  }
}