#include "../transform.h"

#include <gtest/gtest.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace s21;

TEST(TransformBuilderTest, Identity) {
  auto m = TransformMatrixBuilder::CreateIdentityMatrix();
  EXPECT_EQ(m(0, 0), 1);
  EXPECT_EQ(m(1, 1), 1);
  EXPECT_EQ(m(2, 2), 1);
  EXPECT_EQ(m(3, 3), 1);
}

TEST(TransformBuilderTest, Move) {
  auto m = TransformMatrixBuilder::CreateMoveMatrix(1, 2, 3);
  EXPECT_EQ(m(0, 3), 1);
  EXPECT_EQ(m(1, 3), 2);
  EXPECT_EQ(m(2, 3), 3);
  EXPECT_EQ(m(3, 3), 1);
}

TEST(TransformBuilderTest, Scale) {
  auto m = TransformMatrixBuilder::CreateScaleMatrix(1, 2, 3);
  EXPECT_EQ(m(0, 0), 1);
  EXPECT_EQ(m(1, 1), 2);
  EXPECT_EQ(m(2, 2), 3);
  EXPECT_EQ(m(3, 3), 1);
}

TEST(TransformBuilderTest, ViewMatrix) {
  auto ref = glm::lookAt(glm::vec3(10, 10, 10), glm::vec3(1, 2, 3),
                         glm::vec3(1, 1, 0));

  std::cout << "Reference Matrix" << std::endl;
  for (int j1 = 0; j1 < 4; j1++) {
    for (int i1 = 0; i1 < 4; i1++) {
      std::cout << ref[i1][j1] << " ";
    }
    std::cout << std::endl;
  }

  auto m = TransformMatrixBuilder::CreateViewMatrix(
      Point3D(10, 10, 10), Point3D(1, 2, 3), S21Vector(1, 1, 0));

  std::cout << "Self Matrix" << std::endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << m(i, j) << " ";
    }
    std::cout << std::endl;
  }

  // дичь с индексами потому-что в glm в памяти хранятся блоки - столбцы, а не
  // как обычно блоки-строки
  for (int j1 = 0, i2 = 0; j1 < 4; j1++, i2++) {
    for (int i1 = 0, j2 = 0; i1 < 4; i1++, j2++) {
      EXPECT_NEAR(m(i2, j2), ref[i1][j1], 0.0001);
    }
  }
}

TEST(TransformBuilderTest, ProjectionMatrix) {
  auto ref = glm::perspective(glm::radians(30.0f), 4.0f / 3.0f, 1.0f, 200.0f);

  std::cout << "Reference Matrix" << std::endl;
  for (int j1 = 0; j1 < 4; j1++) {
    for (int i1 = 0; i1 < 4; i1++) {
      std::cout << ref[i1][j1] << " ";
    }
    std::cout << std::endl;
  }

  auto m = TransformMatrixBuilder::CreatePerspectiveMatrix(
      Convert::toRad(30), 4.0f / 3.0f, 1.0f, 200.0f);

  std::cout << "Self Matrix" << std::endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << m(i, j) << " ";
    }
    std::cout << std::endl;
  }

  // дичь с индексами потому-что в glm в памяти хранятся блоки - столбцы, а не
  // как обычно блоки-строки
  for (int j1 = 0, i2 = 0; j1 < 4; j1++, i2++) {
    for (int i1 = 0, j2 = 0; i1 < 4; i1++, j2++) {
      EXPECT_NEAR(m(i2, j2), ref[i1][j1], 0.0001);
    }
  }
}

TEST(TransformBuildTest, OrthoMatrix) {
  auto ref = glm::ortho(-400.0f, 400.0f, -300.0f, 300.0f, 1.0f, 200.0f);

  std::cout << "Reference Matrix" << std::endl;
  for (int j1 = 0; j1 < 4; j1++) {
    for (int i1 = 0; i1 < 4; i1++) {
      std::cout << ref[i1][j1] << " ";
    }
    std::cout << std::endl;
  }

  auto m =
      TransformMatrixBuilder::CreateOrthoMatrix(800.0f, 600.0f, 1.0f, 200.0f);

  std::cout << "Self Matrix" << std::endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << m(i, j) << " ";
    }
    std::cout << std::endl;
  }

  // дичь с индексами потому-что в glm в памяти хранятся блоки - столбцы, а не
  // как обычно блоки-строки
  for (int j1 = 0, i2 = 0; j1 < 4; j1++, i2++) {
    for (int i1 = 0, j2 = 0; i1 < 4; i1++, j2++) {
      EXPECT_NEAR(m(i2, j2), ref[i1][j1], 0.0001);
    }
  }
}

TEST(TransformTest, MovePoint) {
  auto m = TransformMatrixBuilder::CreateMoveMatrix(1, 2, 3);
  auto p = Point3D(1, 2, 3);
  auto res = m * p;
  EXPECT_EQ(res.GetX(), 2);
  EXPECT_EQ(res.GetY(), 4);
  EXPECT_EQ(res.GetZ(), 6);
}

TEST(TransformTest, MovePoint2) {
  auto m = TransformMatrixBuilder::CreateMoveMatrix(-1, -2, -3);
  auto p = Point3D(1, 2, 3);
  auto res = m * p;
  EXPECT_EQ(res.GetX(), 0);
  EXPECT_EQ(res.GetY(), 0);
  EXPECT_EQ(res.GetZ(), 0);
}

TEST(TransformTest, ScalePoint) {
  auto m = TransformMatrixBuilder::CreateScaleMatrix(1, 2, 3);
  auto p = Point3D(1, 2, 3);
  auto res = m * p;
  EXPECT_EQ(res.GetX(), 1);
  EXPECT_EQ(res.GetY(), 4);
  EXPECT_EQ(res.GetZ(), 9);
}

TEST(TransformTest, ScalePoint2) {
  auto m = TransformMatrixBuilder::CreateScaleMatrix(0, 0, 0);
  auto p = Point3D(1, 2, 3);
  auto res = m * p;
  EXPECT_EQ(res.GetX(), 0);
  EXPECT_EQ(res.GetY(), 0);
  EXPECT_EQ(res.GetZ(), 0);
}

TEST(TransformTest, XRotatePoint) {
  auto m =
      TransformMatrixBuilder::CreateRotationMatrix(Convert::toRad(90), 0, 0);
  auto p = Point3D(0, 1, 0);
  auto res = m * p;
  EXPECT_NEAR(res.GetX(), 0, 0.0001);
  EXPECT_NEAR(res.GetY(), 0, 0.0001);
  EXPECT_NEAR(res.GetZ(), 1, 0.0001);
}

TEST(TransformTest, YRotatePoint) {
  auto m =
      TransformMatrixBuilder::CreateRotationMatrix(0, Convert::toRad(90), 0);
  auto p = Point3D(0, 0, 1);
  auto res = m * p;
  EXPECT_NEAR(res.GetX(), 1, 0.0001);
  EXPECT_NEAR(res.GetY(), 0, 0.0001);
  EXPECT_NEAR(res.GetZ(), 0, 0.0001);
}

TEST(TransformTest, ZRotatePoint) {
  auto m =
      TransformMatrixBuilder::CreateRotationMatrix(0, 0, Convert::toRad(90));
  auto p = Point3D(1, 0, 0);
  auto res = m * p;
  EXPECT_NEAR(res.GetX(), 0, 0.0001);
  EXPECT_NEAR(res.GetY(), 1, 0.0001);
  EXPECT_NEAR(res.GetZ(), 0, 0.0001);
}

TEST(TransformTest, XYZRotatePoint) {
  auto m = TransformMatrixBuilder::CreateRotationMatrix(
      Convert::toRad(180), Convert::toRad(30), Convert::toRad(75));
  auto p = Point3D(100, 100, 0);
  auto res = m * p;

  EXPECT_NEAR(res.GetX(), 119.0, 0.1);
  EXPECT_NEAR(res.GetY(), 57.8, 0.1);
  EXPECT_NEAR(res.GetZ(), -50, 0.1);

  std::cout << "x: " << res.GetX() << std::endl;
  std::cout << "y: " << res.GetY() << std::endl;
  std::cout << "z: " << res.GetZ() << std::endl;
}

TEST(TransformTest, MatrixMultiplyPipeline) {
  Point3D cube[4] = {Point3D(-50, -50, 0), Point3D(50, -50, 0),
                     Point3D(50, 50, 0), Point3D(-50, 50, 0)};

  glm::mat4 view_ref = glm::lookAt(glm::vec3(0, -50, -100),
                                   glm::vec3(0, 25, -1), glm::vec3(0, 1, 0));

  auto view_new = TransformMatrixBuilder::CreateViewMatrix(
      Point3D(0, -50, -100), Point3D(0, 25, -1), S21Vector(0, 1, 0));

  glm::mat4 persp_ref =
      glm::perspective(Convert::toRad(55.0f), 4.0f / 3.0f, 10.0f, 300.0f);

  auto persp_new = TransformMatrixBuilder::CreatePerspectiveMatrix(
      Convert::toRad(55.0f), 4.0f / 3.0f, 10.0f, 300.0f);

  std::cout << "projection cube " << std::endl;

  for (int i = 0; i < 4; i++) {
    auto p_ref = persp_ref * view_ref *
                 glm::vec4(cube[i].GetX(), cube[i].GetY(), cube[i].GetZ(), 1);

    std::cout << "ref transform:p.x " << p_ref.x << " p.y " << p_ref.y
              << " p.z " << p_ref.z << std::endl;

    auto p_new = persp_new * view_new * cube[i];
    std::cout << "new transform:p.x " << p_new.GetX() << " p.y " << p_new.GetY()
              << " p.z " << p_new.GetZ() << std::endl;

    EXPECT_NEAR(p_ref.x, p_new.GetX(), 0.0001);
    EXPECT_NEAR(p_ref.y, p_new.GetY(), 0.0001);
    EXPECT_NEAR(p_ref.z, p_new.GetZ(), 0.0001);
  }

  std::cout << std::endl;
}
