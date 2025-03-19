#pragma once
#include <cmath>
#include <exception>
#include <iostream>

class S21Matrix_exception : public std::exception {
 private:
  int code;
  std::string var;

 public:
  S21Matrix_exception(const std::string &msg, int str) : code{str}, var{msg} {}
  int get_code(S21Matrix_exception &ex) { return ex.code; }
  std::string get_message(S21Matrix_exception &ex) { return ex.var; }
};

class S21Matrix {
 private:
  int rows_, columns_;
  double **matrix;

 public:
  S21Matrix() : rows_(1), columns_(1) {
    alloc_memory_for_matrix(*this);
    init_zeros();
  }
  S21Matrix(int rows, int cols) : rows_(rows), columns_(cols) {
    alloc_memory_for_matrix(*this);
    init_zeros();
  }
  S21Matrix(const S21Matrix &other) {
    rows_ = other.rows_;
    columns_ = other.columns_;
    alloc_memory_for_matrix(*this);
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < columns_; j++) {
        matrix[i][j] = other.matrix[i][j];
      }
    }
  }
  S21Matrix(S21Matrix &&other) {
    rows_ = other.rows_;
    columns_ = other.columns_;
    matrix = other.matrix;
    other.matrix = nullptr;
  }
  ~S21Matrix() {
    for (int i = 0; i < this->rows_; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
  void init_zeros();
  int get_rows() { return rows_; }
  int get_columns() { return columns_; }
  double **get_matrix() { return matrix; }
  void set_rows(int num);
  void set_columns(int num);
  void set_matrix(double array[], int size);
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  void alloc_memory_for_matrix(S21Matrix &other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix MinorMatrix(S21Matrix &var, int row, int col);
  const S21Matrix &operator=(const S21Matrix &var);
  S21Matrix operator+(const S21Matrix &var);
  S21Matrix operator-(const S21Matrix &var);
  S21Matrix operator*(const S21Matrix &var);
  S21Matrix operator*(const double value);
  const S21Matrix &operator+=(const S21Matrix &var);
  const S21Matrix &operator-=(const S21Matrix &var);
  const S21Matrix &operator*=(const S21Matrix &var);
  const S21Matrix &operator*=(const double var);
  bool operator==(const S21Matrix &var);
  double operator()(int i, int j);
  void free_memory(S21Matrix &other);
  double get_determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
};
double multymatrix(double **first, double **second, int row, int column,
                   int value_for_cycle);