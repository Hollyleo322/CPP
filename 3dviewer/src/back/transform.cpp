#include "transform.h"
namespace s21 {
TransformMatrix TransformMatrixBuilder::CreateIdentityMatrix() {
  TransformMatrix matrix;
  matrix(0, 0) = 1;
  matrix(1, 1) = 1;
  matrix(2, 2) = 1;
  matrix(3, 3) = 1;
  return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateMoveMatrix(float x, float y,
                                                         float z) {
  TransformMatrix matrix = CreateIdentityMatrix();
  matrix(0, 3) = x;
  matrix(1, 3) = y;
  matrix(2, 3) = z;
  return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateScaleMatrix(float x, float y,
                                                          float z) {
  TransformMatrix matrix;
  matrix(0, 0) = x;
  matrix(1, 1) = y;
  matrix(2, 2) = z;
  matrix(3, 3) = 1;
  return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateRotationMatrix(float x_angle,
                                                             float y_angle,
                                                             float z_angle) {
  TransformMatrix res = CreateIdentityMatrix();
  if (x_angle != 0) {
    TransformMatrix m_x = CreateIdentityMatrix();
    float c = cosf(x_angle);
    float s = sinf(x_angle);
    m_x(1, 1) = c;
    m_x(1, 2) = -s;
    m_x(2, 1) = s;
    m_x(2, 2) = c;
    res = m_x * res;
  }
  if (y_angle != 0) {
    TransformMatrix m_y = CreateIdentityMatrix();
    float c = cosf(y_angle);
    float s = sinf(y_angle);
    m_y(0, 0) = c;
    m_y(0, 2) = s;
    m_y(2, 0) = -s;
    m_y(2, 2) = c;
    res = m_y * res;
  }
  if (z_angle != 0) {
    TransformMatrix m_z = CreateIdentityMatrix();
    float c = cosf(z_angle);
    float s = sinf(z_angle);
    m_z(0, 0) = c;
    m_z(0, 1) = -s;
    m_z(1, 0) = s;
    m_z(1, 1) = c;
    res = m_z * res;
  }
  return res;
}

TransformMatrix TransformMatrixBuilder::CreatePerspectiveMatrix(
    float view_angle, float aspect, float zNear, float zFar) {
  float top = zNear * tanf(view_angle / 2);
  float bottom = -top;
  float right = top * aspect;
  float left = -right;
  TransformMatrix matrix;
  matrix(0, 0) = (2 * zNear) / (right - left);
  matrix(1, 1) = (2 * zNear) / (top - bottom);
  matrix(0, 2) = (right + left) / (right - left);
  matrix(1, 2) = (top + bottom) / (top - bottom);
  matrix(2, 2) = -(zFar + zNear) / (zFar - zNear);
  matrix(3, 2) = -1;
  matrix(2, 3) = -(2 * zFar * zNear) / (zFar - zNear);
  return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateOrthoMatrix(float width,
                                                          float height,
                                                          float zNear,
                                                          float zFar) {
  float left = -width / 2;
  float right = width / 2;
  float top = height / 2;
  float bottom = -height / 2;
  TransformMatrix matrix;
  matrix(0, 0) = 2 / (right - left);
  matrix(1, 1) = 2 / (top - bottom);
  matrix(2, 2) = -2 / (zFar - zNear);
  matrix(0, 3) = -(right + left) / (right - left);
  matrix(1, 3) = -(top + bottom) / (top - bottom);
  matrix(2, 3) = -(zFar + zNear) / (zFar - zNear);
  matrix(3, 3) = 1;
  return matrix;
}

TransformMatrix TransformMatrixBuilder::CreateViewMatrix(const Point3D &eye,
                                                         const Point3D &center,
                                                         const S21Vector &up) {
  S21Vector forward(eye.GetX() - center.GetX(), eye.GetY() - center.GetY(),
                    eye.GetZ() - center.GetZ());
  S21Vector right = up.crossProduct(forward);
  S21Vector trueUp = forward.crossProduct(right);
  forward.normalize();
  right.normalize();
  trueUp.normalize();

  TransformMatrix viewMatrix = TransformMatrixBuilder::CreateIdentityMatrix();
  viewMatrix(0, 0) = right.x;
  viewMatrix(0, 1) = right.y;
  viewMatrix(0, 2) = right.z;
  viewMatrix(1, 0) = trueUp.x;
  viewMatrix(1, 1) = trueUp.y;
  viewMatrix(1, 2) = trueUp.z;
  viewMatrix(2, 0) = forward.x;
  viewMatrix(2, 1) = forward.y;
  viewMatrix(2, 2) = forward.z;

  TransformMatrix moveMatrix = TransformMatrixBuilder::CreateMoveMatrix(
      -eye.GetX(), -eye.GetY(), -eye.GetZ());
  viewMatrix = viewMatrix * moveMatrix;

  return viewMatrix;
}

TransformMatrix TransformMatrix::operator*(const TransformMatrix &var) const {
  TransformMatrix result;
  result.matrix_ = this->matrix_ * var.matrix_;
  return result;
}

Point3D TransformMatrix::TransformPoint(const Point3D &var) const {
  float x = var.GetX();
  float y = var.GetY();
  float z = var.GetZ();
  float w = var.GetW();

  const auto &m = matrix_;
  // Выполняем умножение матрицы 4x4 на вектор 4x1
  float resultX = m(0, 0) * x + m(0, 1) * y + m(0, 2) * z + m(0, 3) * w;
  float resultY = m(1, 0) * x + m(1, 1) * y + m(1, 2) * z + m(1, 3) * w;
  float resultZ = m(2, 0) * x + m(2, 1) * y + m(2, 2) * z + m(2, 3) * w;
  float resultW = m(3, 0) * x + m(3, 1) * y + m(3, 2) * z + m(3, 3) * w;

  return Point3D(resultX, resultY, resultZ, resultW);
}

Point3D TransformMatrix::operator*(const Point3D &var) const {
  return TransformPoint(var);
}

float S21Vector::length() const { return sqrt(x * x + y * y + z * z); }

void S21Vector::normalize() {
  float len = length();
  if (len > 0) {
    x /= len;
    y /= len;
    z /= len;
  }
}

S21Vector S21Vector::crossProduct(const S21Vector &v2) const {
  return S21Vector(y * v2.z - z * v2.y, z * v2.x - x * v2.z,
                   x * v2.y - y * v2.x);
}
}  // namespace s21