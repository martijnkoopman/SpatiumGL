#include <gtest/gtest.h>

#include <spatiumgl/Matrix.hpp>

// constructor
// constructorEmpty
// constructorDiagonal
// constructorInitializerList
// compareEqual
// compareUnequal
// addMatrix
// subtractMatrix
// multiplyScalar
// multiplyMatrix
// multiplyVector
// divideScalar
// transpose
// transposed
// omit
// determinant
// minor
// inverse
// output

TEST(Matrix2, constructor)
{

  // 1 2
  // 3 4
  spgl::Matrix2 m1 = { 1, 3, 3, 4 };
  EXPECT_EQ(m1[0][0], 1);
  EXPECT_EQ(m1[0][1], 3);
  EXPECT_EQ(m1[1][0], 3);
  EXPECT_EQ(m1[1][1], 4);

  //spgl::Matrix2 m2 = { { 1, 3 }, { 3, 4 } };
//  EXPECT_EQ(m2[0][0], 1);
//  EXPECT_EQ(m2[0][1], 3);
//  EXPECT_EQ(m2[1][0], 3);
//  EXPECT_EQ(m2[1][1], 4);
}

TEST(Matrix2, multiplyMatrix)
{
  // 1 2
  // 3 4
  spgl::Matrix2 m1 = { 1, 3, 2, 4 };

  // 5 6
  // 7 8
  spgl::Matrix2 m2 = { 5, 7, 6, 8 };

  // Multiply
  const spgl::Matrix2 result = m1 * m2;

  // Compare

  EXPECT_EQ(result[0][0], 19);
  EXPECT_EQ(result[0][1], 43);
  EXPECT_EQ(result[1][0], 22);
  EXPECT_EQ(result[1][1], 50);
}

TEST(Matrix2, omit)
{
  const spgl::Matrix<double, 2, 2> matrix = { { 1, 2 }, { 3, 4 } };
  const spgl::Matrix<double, 1, 1> result = matrix.omit(0,0);
  EXPECT_EQ(result[0][0], 4);
};

TEST(Matrix2, determinant)
{
  // Example: https://www.mathsisfun.com/algebra/matrix-determinant.html
  const spgl::Matrix2 matrix = { { 3, 4 }, { 8, 6 } };
  const double det = matrix.determinant();
  EXPECT_EQ(det, -14);
};
