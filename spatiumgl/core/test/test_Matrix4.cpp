#include <gtest/gtest.h>

#include <spatiumgl/Matrix4x4.hpp>

#include <iostream>

TEST(Matrix4, constructorDefault)
{
  const spgl::Matrix4 result;
  const spgl::Matrix4 correct = {
    { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }
  };
  EXPECT_EQ(correct, result);
}

TEST(Matrix4, constructorDiagonal)
{
  const spgl::Matrix4 result(3);
  const spgl::Matrix4 correct = {
    { 3, 0, 0, 0 }, { 0, 3, 0, 0 }, { 0, 0, 3, 0 }, { 0, 0, 0, 3 }
  };
  EXPECT_EQ(correct, result);
}

TEST(Matrix4, constructorInitializerList)
{
  const spgl::Matrix4 result = {
    { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 }
  };
  EXPECT_EQ(result[0][0], 1);
  EXPECT_EQ(result[0][1], 2);
  EXPECT_EQ(result[0][2], 3);
  EXPECT_EQ(result[0][3], 4);
  EXPECT_EQ(result[1][0], 5);
  EXPECT_EQ(result[1][1], 6);
  EXPECT_EQ(result[1][2], 7);
  EXPECT_EQ(result[1][3], 8);
  EXPECT_EQ(result[2][0], 9);
  EXPECT_EQ(result[2][1], 10);
  EXPECT_EQ(result[2][2], 11);
  EXPECT_EQ(result[2][3], 12);
  EXPECT_EQ(result[3][0], 13);
  EXPECT_EQ(result[3][1], 14);
  EXPECT_EQ(result[3][2], 15);
  EXPECT_EQ(result[3][3], 16);
}

TEST(Matrix4, compareEqual)
{
  const spgl::Matrix4 matrix1 = {
    { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 }
  };
  const spgl::Matrix4 matrix2 = {
    { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 }
  };
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(Matrix4, compareUnequal)
{
  const spgl::Matrix4 matrix1 = {
    { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 }
  };
  const spgl::Matrix4 matrix2 = {
    { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 9, 9, 9 }, { 13, 14, 15, 16 }
  };
  EXPECT_TRUE(matrix1 != matrix2);
}

// addMatrix
// subtractMatrix
// multiplyScalar
// multiplyMatrix
// multiplyVector
// divideScalar
// transpose
// transposed
// omit

TEST(Matrix4, determinant) {}

// minor

TEST(Matrix4, inverse)
{
  // Example:
  // https://www.mathsisfun.com/algebra/matrix-inverse-row-operations-gauss-jordan.html
  const spgl::Matrix4 matrix = {
    { 4, 0, 0, 1 }, { 0, 0, 1, 0 }, { 2, 2, 0, 0 }, { 0, 0, 0, 1 }
  };
  const spgl::Matrix4 result = matrix.inverse();
  const spgl::Matrix4 correct = { { 0.25, 0, 0, -0.25 },
                                       { -0.25, 0, 0.5, 0.25 },
                                       { 0, 1, 0, 0 },
                                       { 0, 0, 0, 1 } };
  EXPECT_EQ(correct, result);
}

TEST(Matrix4, viewport)
{
  const spgl::Vector2i size(640, 480);
  const spgl::Matrix4 viewport = spgl::Matrix4::viewport(size);

  const spgl::Vector4 bottomLeftNDC(-1, -1, 0, 1);
  const spgl::Vector4 bottomLeftScreen = viewport * bottomLeftNDC;
  EXPECT_EQ(bottomLeftScreen, spgl::Vector4(0, 0, 0, 1));

  const spgl::Vector4 topRightNDC(1, 1, 0, 1);
  const spgl::Vector4 topRightScreen = viewport * topRightNDC;
  EXPECT_EQ(topRightScreen, spgl::Vector4(640, 480, 0, 1));
}

// output