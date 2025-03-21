#pragma once
#include <cmath>

#include "../lib/s21_matrix/s21_matrix_oop.h"
#include "data_figure.h"

#undef M_PI
#define M_PI 3.14159265
namespace s21 {
class Point3D;

class S21Vector : private S21Matrix<3, 1> {
 public:
  S21Vector(float x, float y, float z) : S21Matrix() {
    (*this)(0, 0) = x;
    (*this)(1, 0) = y;
    (*this)(2, 0) = z;
  }
  void normalize();
  float length() const;
  S21Vector crossProduct(const S21Vector &other) const;
  float &x = (*this)(0, 0);
  float &y = (*this)(1, 0);
  float &z = (*this)(2, 0);
};

class TransformMatrix {
 private:
  S21Matrix<4, 4> matrix_;

 public:
  TransformMatrix() = default;
  float &operator()(int row, int col) { return matrix_(row, col); }
  TransformMatrix operator*(const TransformMatrix &var) const;
  Point3D TransformPoint(const Point3D &var) const;
  Point3D operator*(const Point3D &var) const;
};

class TransformMatrixBuilder {
 public:
  static TransformMatrix CreateIdentityMatrix();
  static TransformMatrix CreateRotationMatrix(float x_angle_rad,
                                              float y_angle_rad,
                                              float z_angle_rad);
  static TransformMatrix CreateMoveMatrix(float x, float y, float z);
  static TransformMatrix CreateScaleMatrix(float x, float y, float z);
  static TransformMatrix CreatePerspectiveMatrix(float view_angle_rad,
                                                 float aspect, float zNear,
                                                 float zFar);
  static TransformMatrix CreateOrthoMatrix(float width, float height,
                                           float zNear, float zFar);
  static TransformMatrix CreateViewMatrix(const Point3D &eye,
                                          const Point3D &center,
                                          const S21Vector &up = S21Vector(0, 1,
                                                                          0));
};

class Convert {
 public:
  static float toDeg(float radians) { return radians * 180.0f / M_PI; }
  static float toRad(float degrees) { return degrees * M_PI / 180.0f; }
};
}  // namespace s21