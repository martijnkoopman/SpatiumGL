#include <gtest/gtest.h>

#include <spatiumgl/Matrix.hpp>

TEST(Matrix3, constructorDefault)
{
  const spgl::Matrix3 result;
  const spgl::Matrix3 correct = { { 0, 0, 0 }, { 0, 0, 0 }, { 0, 0, 0 } };
  EXPECT_EQ(correct, result);
}

TEST(Matrix3, constructorDiagonal)
{
  const spgl::Matrix3 result(3);
  const spgl::Matrix3 correct = { { 3, 0, 0 }, { 0, 3, 0 }, { 0, 0, 3 } };
  EXPECT_EQ(correct, result);
}

TEST(Matrix3, constructorInitializerList)
{
  const spgl::Matrix3 result = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  EXPECT_EQ(result[0][0], 1);
  EXPECT_EQ(result[0][1], 2);
  EXPECT_EQ(result[0][2], 3);
  EXPECT_EQ(result[1][0], 4);
  EXPECT_EQ(result[1][1], 5);
  EXPECT_EQ(result[1][2], 6);
  EXPECT_EQ(result[2][0], 7);
  EXPECT_EQ(result[2][1], 8);
  EXPECT_EQ(result[2][2], 9);
}

TEST(Matrix3, compareEqual)
{
  const spgl::Matrix3 matrix1 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  const spgl::Matrix3 matrix2 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(Matrix3, compareUnequal)
{
  const spgl::Matrix3 matrix1 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  const spgl::Matrix3 matrix2 = { { 1, 2, 3 }, { 9, 9, 9 }, { 7, 8, 9 } };
  EXPECT_TRUE(matrix1 != matrix2);
}

TEST(Matrix3, addMatrix)
{
  const spgl::Matrix3 matrix1 = { { 4, 8, 12 },
                                     { 16, 20, 24 },
                                     { 28, 32, 36 } };
  const spgl::Matrix3 matrix2 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  const spgl::Matrix3 result = matrix1 + matrix2;
  const spgl::Matrix3 correct = { { 5, 10, 15 },
                                     { 20, 25, 30 },
                                     { 35, 40, 45 } };
  EXPECT_EQ(correct, result);
}

TEST(Matrix3, subtractMatrix)
{
  const spgl::Matrix3 matrix1 = { { 4, 8, 12 },
                                     { 16, 20, 24 },
                                     { 28, 32, 36 } };
  const spgl::Matrix3 matrix2 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  const spgl::Matrix3 result = matrix1 - matrix2;
  const spgl::Matrix3 correct = { { 3, 6, 9 },
                                     { 12, 15, 18 },
                                     { 21, 24, 27 } };
  EXPECT_EQ(correct, result);
}

TEST(Matrix3, multiplyScalar)
{
  const spgl::Matrix3 matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  const spgl::Matrix3 result = matrix * 2;
  const spgl::Matrix3 correct = { { 2, 4, 6 },
                                     { 8, 10, 12 },
                                     { 14, 16, 18 } };
  EXPECT_EQ(correct, result);
};

// multiplyMatrix

TEST(Matrix3, multiplyVector)
{
  spgl::Vector3 vector;
  vector[0] = 1;
  vector[1] = 2;
  vector[2] = 3;

  spgl::Matrix3 matrix;
  matrix[0][0] = 1;
  matrix[1][1] = 2;
  matrix[2][2] = 3;

  spgl::Vector3 res = matrix * vector;
}

TEST(Matrix3, divideScalar)
{
  const spgl::Matrix3 matrix = { { 2, 4, 6 },
                                    { 8, 10, 12 },
                                    { 14, 16, 18 } };
  const spgl::Matrix3 result = matrix / 2;
  const spgl::Matrix3 correct = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  EXPECT_EQ(correct, result);
}

// transpose

TEST(Matrix3, transposed)
{
  const spgl::Matrix3 matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
  const spgl::Matrix3 result = matrix.transposed();
  const spgl::Matrix3 correct = { { 1, 4, 7 }, { 2, 5, 8 }, { 3, 6, 9 } };
  EXPECT_EQ(correct, result);
};

// omit

TEST(Matrix3, determinant)
{
  // Example: https://www.mathsisfun.com/algebra/matrix-determinant.html
  const spgl::Matrix3 matrix = { { 6, 4, 2 }, { 1, -2, 8 }, { 1, 5, 7 } };
  const double det = matrix.determinant();
  EXPECT_EQ(det, -306);
};

// minor

TEST(Matrix3, inverse)
{
  // Example:
  // https://www.mathsisfun.com/algebra/matrix-inverse-minors-cofactors-adjugate.html
  const spgl::Matrix3 m = { { 3, 2, 0 }, { 0, 0, 1 }, { 2, -2, 1 } };
  const spgl::Matrix3 result = m.inverse();
  const spgl::Matrix3 correct = { { 0.2, -0.2, 0.2 },
                                     { 0.2, 0.3, -0.3 },
                                     { 0, 1, 0 } };
  EXPECT_EQ(correct, result);
}

// output
