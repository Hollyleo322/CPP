#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

using namespace std;

TEST(EqMatrix, test) {
  S21Matrix a(3, 2);
  S21Matrix b(3, 2);
  S21Matrix c(3, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  c.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  ASSERT_EQ(a.EqMatrix(b), true);
  ASSERT_EQ(c.EqMatrix(a), false);
}

TEST(SumMatrix, test) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix c(2, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double array_result[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  a.SumMatrix(b);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(a.get_matrix()[i][j], array_result[3 * i + j]);
    }
  }
  ASSERT_THROW(a.SumMatrix(c), S21Matrix_exception);
}

TEST(SubMatrix, test) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix c(2, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double array_result[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  a.SubMatrix(b);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(a.get_matrix()[i][j], array_result[3 * i + j]);
    }
  }
  ASSERT_THROW(a.SubMatrix(c), S21Matrix_exception);
}
TEST(MulNumber, test) {
  S21Matrix a(3, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double array_result[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
  double b = 2;
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  a.MulNumber(b);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(a.get_matrix()[i][j], array_result[3 * i + j]);
    }
  }
}
TEST(MulMatrix, test) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix c(2, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double array_result[] = {30, 36, 42, 66, 81, 96, 102, 126, 150};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  a.MulMatrix(b);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(a.get_matrix()[i][j], array_result[3 * i + j]);
    }
  }
  ASSERT_THROW(a.MulMatrix(c), S21Matrix_exception);
}
TEST(set_matrix, test) {
  S21Matrix a(3, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double array_result[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(a.get_matrix()[i][j], array_result[3 * i + j]);
    }
  }
  ASSERT_THROW(a.set_matrix(array_result, 8), S21Matrix_exception);
}
TEST(transpose, test) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double array_result[] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b = a.Transpose();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(b.get_matrix()[i][j], array_result[3 * i + j]);
    }
  }
}
TEST(determinant, test) {
  S21Matrix a(3, 3);
  S21Matrix b(2, 4);
  double init_array[] = {1, 4, 2, 4, 5, 234, 2, 5, 110};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  ASSERT_DOUBLE_EQ(a.Determinant(), -488);
  ASSERT_THROW(b.Determinant(), S21Matrix_exception);
}
TEST(calccomplements, test_greater_than_one) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix c(3, 2);
  double init_array[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  double array_result[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  c.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b = a.CalcComplements();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(b.get_matrix()[i][j], array_result[3 * i + j]);
    }
  }
  ASSERT_THROW(c.CalcComplements(), S21Matrix_exception);
}
TEST(calcomplements, test_one) {
  S21Matrix a(1, 1);
  S21Matrix b(1, 1);
  double init_array[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b = a.CalcComplements();
  ASSERT_DOUBLE_EQ(b.get_matrix()[0][0], 1);
}
TEST(Inverse, test_greater_than_one) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  double init_array[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  double array_result[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b = a.InverseMatrix();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(b.get_matrix()[i][j], array_result[3 * i + j]);
    }
  }
}
TEST(Inverse, test_one) {
  S21Matrix a(1, 1);
  S21Matrix b(1, 1);
  S21Matrix c(3, 3);
  double init_array2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  c.set_matrix(init_array2, sizeof(init_array2) / sizeof(init_array2[0]));
  double init_array[] = {123.1231, 2};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  double check = 1 / 123.1231;
  b = a.InverseMatrix();
  ASSERT_DOUBLE_EQ(b.get_matrix()[0][0], check);
  ASSERT_THROW(c.InverseMatrix(), S21Matrix_exception);
}
TEST(Operator, equal) {
  S21Matrix a(2, 2);
  S21Matrix b(1, 2);
  double init_array[] = {1, 2, 3, 4};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b = a;
  ASSERT_DOUBLE_EQ(a.get_rows(), b.get_rows());
  ASSERT_DOUBLE_EQ(a.get_columns(), b.get_columns());
}
TEST(Operator, plus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 1);
  double init_array[] = {1, 2, 3, 4};
  double res_array[] = {2, 4, 6, 8};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  c.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  S21Matrix d = a + b;
  for (int i = 0; i < d.get_rows(); i++) {
    for (int j = 0; j < d.get_columns(); j++) {
      ASSERT_DOUBLE_EQ(d.get_matrix()[i][j], res_array[2 * i + j]);
    }
  }
  ASSERT_THROW(a + c, S21Matrix_exception);
}
TEST(Operator, minus) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 1);
  double init_array[] = {1, 2, 3, 4};
  double res_array[] = {0, 0, 0, 0};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  c.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  S21Matrix d = a - b;
  for (int i = 0; i < d.get_rows(); i++) {
    for (int j = 0; j < d.get_columns(); j++) {
      ASSERT_DOUBLE_EQ(d.get_matrix()[i][j], res_array[2 * i + j]);
    }
  }
  ASSERT_THROW(a + c, S21Matrix_exception);
}
TEST(Operator, mul) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix c(2, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double res_array[] = {30, 36, 42, 66, 81, 96, 102, 126, 150};
  double mul = 2;
  double res_array2[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  c.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  S21Matrix d = a * b;
  for (int i = 0; i < d.get_rows(); i++) {
    for (int j = 0; j < d.get_columns(); j++) {
      ASSERT_DOUBLE_EQ(d.get_matrix()[i][j], res_array[3 * i + j]);
    }
  }
  S21Matrix f = a * mul;
  for (int i = 0; i < f.get_rows(); i++) {
    for (int j = 0; j < f.get_columns(); j++) {
      ASSERT_DOUBLE_EQ(f.get_matrix()[i][j], res_array2[3 * i + j]);
    }
  }
  ASSERT_THROW(a * c, S21Matrix_exception);
}
TEST(Operator, eq_eq) {
  S21Matrix a(3, 2);
  S21Matrix b(3, 2);
  S21Matrix c(3, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  c.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  ASSERT_EQ(a == b, true);
  ASSERT_EQ(a == c, false);
}
TEST(Operator, plus_eq) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix c(2, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double array_result[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  a += b;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(a.get_matrix()[i][j], array_result[3 * i + j]);
    }
  }
  ASSERT_THROW(a += c, S21Matrix_exception);
}
TEST(Operator, minus_eq) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix c(2, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double array_result[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  a -= b;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(a.get_matrix()[i][j], array_result[3 * i + j]);
    }
  }
  ASSERT_THROW(a -= c, S21Matrix_exception);
}
TEST(Operator, mul_eq) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix c(2, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  double res_array[] = {30, 36, 42, 66, 81, 96, 102, 126, 150};
  double mul = 2;
  double res_array2[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  b.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  c.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  a *= b;
  for (int i = 0; i < a.get_rows(); i++) {
    for (int j = 0; j < a.get_columns(); j++) {
      ASSERT_DOUBLE_EQ(a.get_matrix()[i][j], res_array[3 * i + j]);
    }
  }
  b *= mul;
  for (int i = 0; i < b.get_rows(); i++) {
    for (int j = 0; j < b.get_columns(); j++) {
      ASSERT_DOUBLE_EQ(b.get_matrix()[i][j], res_array2[3 * i + j]);
    }
  }
  ASSERT_THROW(a *= c, S21Matrix_exception);
}
TEST(Operator, indexes) {
  S21Matrix a(3, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  ASSERT_DOUBLE_EQ(a(2, 2), a.get_matrix()[2][2]);
  ASSERT_THROW(a(4, 3), S21Matrix_exception);
}
TEST(Set, rows) {
  S21Matrix a(3, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  double res_array[] = {1, 2, 3, 4, 5, 6};
  double res_array2[] = {1, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0};
  a.set_rows(2);
  for (int i = 0; i < a.get_rows(); i++) {
    for (int j = 0; j < a.get_columns(); j++) {
      ASSERT_DOUBLE_EQ(a.get_matrix()[i][j], res_array[3 * i + j]);
    }
  }
  a.set_rows(4);
  for (int i = 0; i < a.get_rows(); i++) {
    for (int j = 0; j < a.get_columns(); j++) {
      ASSERT_DOUBLE_EQ(a.get_matrix()[i][j], res_array2[3 * i + j]);
    }
  }
}
TEST(Set, columns) {
  S21Matrix a(3, 3);
  double init_array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  a.set_matrix(init_array, sizeof(init_array) / sizeof(init_array[0]));
  double res_array[] = {1, 2, 4, 5, 7, 8};
  double res_array2[] = {1, 2, 0, 0, 4, 5, 0, 0, 7, 8, 0, 0};
  a.set_columns(2);
  for (int i = 0; i < a.get_rows(); i++) {
    for (int j = 0; j < a.get_columns(); j++) {
      ASSERT_DOUBLE_EQ(a.get_matrix()[i][j], res_array[2 * i + j]);
    }
  }
  a.set_columns(4);
  for (int i = 0; i < a.get_rows(); i++) {
    for (int j = 0; j < a.get_columns(); j++) {
      ASSERT_DOUBLE_EQ(a.get_matrix()[i][j], res_array2[4 * i + j]);
    }
  }
}
int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}