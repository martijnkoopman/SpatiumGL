#include <gtest/gtest.h>

#include <spatiumgl/Matrix.hpp>

TEST(Matrix, Matrix_constructor)
{
	spatiumgl::MatrixT<SPATIUMGL_PRECISION, 2, 2> matrix;
	EXPECT_EQ(matrix[0][0], 0);
	EXPECT_EQ(matrix[1][1], 0);

	spatiumgl::Matrix2 matrix2; // identity
	EXPECT_EQ(matrix2[0][0], 1);
	EXPECT_EQ(matrix2[1][1], 1);

	spatiumgl::Matrix3 matrix3; // identity
	EXPECT_EQ(matrix3[0][0], 1);
	EXPECT_EQ(matrix3[1][1], 1);
	EXPECT_EQ(matrix3[2][2], 1);

	spatiumgl::Matrix4 matrix4; // identity
	EXPECT_EQ(matrix4[0][0], 1);
	EXPECT_EQ(matrix4[1][1], 1);
	EXPECT_EQ(matrix4[2][2], 1);
	EXPECT_EQ(matrix4[3][3], 1);
}

TEST(Matrix, Matrix_data)
{
	spatiumgl::MatrixT<SPATIUMGL_PRECISION, size_t(3), size_t(3)> matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	spatiumgl::Matrix3 matrix2 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
	SPATIUMGL_PRECISION* ptr = matrix.data();
	EXPECT_EQ(*ptr, 1);
	EXPECT_EQ(*(ptr + 1), 2);
	EXPECT_EQ(*(ptr + 2), 3);
	EXPECT_EQ(*(ptr + 3), 4);
	EXPECT_EQ(*(ptr + 4), 5);
	EXPECT_EQ(*(ptr + 5), 6);
	EXPECT_EQ(*(ptr + 6), 7);
	EXPECT_EQ(*(ptr + 7), 8);
	EXPECT_EQ(*(ptr + 8), 9);
}

TEST(Matrix, Matrix_multiplyVector)
{
	spatiumgl::Vector3 vector;
	vector[0] = 1;
	vector[1] = 2;
	vector[2] = 3;

	spatiumgl::Matrix3 matrix;
	matrix[0][0] = 1;
	matrix[1][1] = 2;
	matrix[2][2] = 3;

	spatiumgl::Vector3 res = matrix * vector;
}