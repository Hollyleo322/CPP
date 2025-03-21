#include "../transform.h"

#include <gtest/gtest.h>

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
  auto m = TransformMatrixBuilder::CreateViewMatrix(
      Point3D(10, 10, 10), Point3D(1, 2, 3), S21Vector(1, 1, 0));

  float ref[4][4] = {{0.703526, -0.703526, -0.100504, 1.00504},
                     {0.295846, 0.418514, -0.858674, 1.44315},
                     {0.646162, 0.574367, 0.502571, -17.231},
                     {0, 0, 0, 1}};
  std::cout << "Reference Matrix" << std::endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << ref[i][j] << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Self Matrix" << std::endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << m(i, j) << " ";
    }
    std::cout << std::endl;
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_NEAR(m(i, j), ref[i][j], 0.0001);
    }
  }
}

TEST(TransformBuilderTest, ProjectionMatrix) {
  float ref[4][4] = {{2.79904, 0, 0, 0},
                     {0, 3.73205, 0, 0},
                     {0, 0, -1.01005, -2.01005},
                     {0, 0, -1, 0}};

  std::cout << "Reference Matrix" << std::endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << ref[i][j] << " ";
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

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_NEAR(m(i, j), ref[i][j], 0.0001);
    }
  }
}

TEST(TransformBuildTest, OrthoMatrix) {
  float ref[4][4] = {{0.0025, 0, 0, -0},
                     {0, 0.00333333, 0, -0},
                     {0, 0, -0.0100503, -1.01005},
                     {0, 0, 0, 1}};

  std::cout << "Reference Matrix" << std::endl;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      std::cout << ref[i][j] << " ";
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

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      EXPECT_NEAR(m(i, j), ref[i][j], 0.0001);
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
  Point3D p(-50, -50, 0);

  auto view_new = TransformMatrixBuilder::CreateViewMatrix(
      Point3D(0, -50, -100), Point3D(0, 25, -1), S21Vector(0, 1, 0));

  auto persp_new = TransformMatrixBuilder::CreatePerspectiveMatrix(
      Convert::toRad(55.0f), 4.0f / 3.0f, 10.0f, 300.0f);

  float p_ref[4] = {72.0368, -116, 64.5168, 79.7092};

  std::cout << "ref transform:p.x " << p_ref[0] << " p.y " << p_ref[1]
            << " p.z " << p_ref[2] << std::endl;

  auto p_new = persp_new * view_new * p;
  std::cout << "self transform:p.x " << p_new.GetX() << " p.y " << p_new.GetY()
            << " p.z " << p_new.GetZ() << std::endl;

  EXPECT_NEAR(p_ref[0], p_new.GetX(), 0.0001);
  EXPECT_NEAR(p_ref[1], p_new.GetY(), 0.0001);
  EXPECT_NEAR(p_ref[2], p_new.GetZ(), 0.0001);

  std::cout << std::endl;
}

// std::cout << "Reference Matrix" << std::endl;
// std::cout << "{";
// for (int j1 = 0; j1 < 4; j1++) {
//   std::cout << "{";
//   for (int i1 = 0; i1 < 4; i1++) {
//     std::cout << ref[i1][j1];
//     if (i1 != 3) std::cout << ", ";
//   }
//   std::cout << "}";
//   if (j1 != 3) std::cout << ", ";
// }
// std::cout << "}" << std::endl;