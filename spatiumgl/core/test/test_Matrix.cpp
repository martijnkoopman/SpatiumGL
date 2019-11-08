#include <gtest/gtest.h>

#include <spatiumgl/Matrix.hpp>

namespace spgl = spatiumgl;

// constructor
// constructorEmpty
// constructorDiagonal
// constructorInitializerList
// accessValue
// accessReference
// rows
// cols
// data
// clear
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

TEST(Matrix, constructor)
{
	spgl::Matrix<double, 2, 4> matrix;

	// Check dimensions
	EXPECT_EQ(matrix.cols(), 2);
	EXPECT_EQ(matrix.rows(), 4);

	// Check default empty values
	EXPECT_EQ(matrix[0][0], 0);
	EXPECT_EQ(matrix[0][1], 0);
	EXPECT_EQ(matrix[0][2], 0);
	EXPECT_EQ(matrix[0][3], 0);
	EXPECT_EQ(matrix[0][0], 0);
	EXPECT_EQ(matrix[0][1], 0);
	EXPECT_EQ(matrix[0][2], 0);
	EXPECT_EQ(matrix[0][3], 0);
}

//TEST(Matrix, Matrix_data)
//{
//	spatiumgl::Matrix<SPATIUMGL_PRECISION, size_t(3), size_t(3)> matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
//	spatiumgl::Matrix3 matrix2 = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
//	SPATIUMGL_PRECISION* ptr = matrix.data();
//	EXPECT_EQ(*ptr, 1);
//	EXPECT_EQ(*(ptr + 1), 2);
//	EXPECT_EQ(*(ptr + 2), 3);
//	EXPECT_EQ(*(ptr + 3), 4);
//	EXPECT_EQ(*(ptr + 4), 5);
//	EXPECT_EQ(*(ptr + 5), 6);
//	EXPECT_EQ(*(ptr + 6), 7);
//	EXPECT_EQ(*(ptr + 7), 8);
//	EXPECT_EQ(*(ptr + 8), 9);
//}
//
//TEST(Matrix, transpose)
//{
//	spatiumgl::Matrix<double, 2, 3> m1;
//	m1[0][0] = 1;
//	m1[1][2] = 6;
//
//	spatiumgl::Matrix<double, 3, 2> m2 = m1.transposed();
//	EXPECT_EQ(m2[0][0], 1);
//	EXPECT_EQ(m2[2][1], 6);
//}
//
//TEST(Matrix, multiplyMatrix)
//{
//	spatiumgl::Matrix<double, 3, 2> m1 = { { 1,4 }, {2,5}, {3,6} };
//	spatiumgl::Matrix<double, 2, 3> m2 = m1.transposed();
//	//spatiumgl::MatrixT<double, 3, 3> m3 = m1 * m2;
//
//	//QCOMPARE(m3(0, 0), 14);
//	//QCOMPARE(m3(0, 1), 32);
//	//QCOMPARE(m3(1, 0), 32);
//	//QCOMPARE(m3(1, 1), 77);
//}

/*
TEST(Matrix, determinant)
{
	Matrix matrix = {
	  {6,  1, 1},
	  {4, -2, 5},
	  {2,  8, 7}
	};

	double det = matrix.determinant();

	QCOMPARE(det, -306);
}

TEST(Matrix, determinantNonSquare)
{
	Matrix matrix = {
	  {6,  1, 1},
	  {4, -2, 5}
	};

	QVERIFY_EXCEPTION_THROWN(matrix.determinant(), std::out_of_range);
}

TEST(Matrix, inverse)
{
	Matrix matrix1 = {
	  {3  , 3.2},
	  {3.5, 3.6}
	};

	Matrix matrix2 = matrix1.inverse();

	QCOMPARE(matrix2.rows(), 2);
	QCOMPARE(matrix2.cols(), 2);
	QVERIFY(qFuzzyCompare(matrix2(0, 0), -9));
	QVERIFY(qFuzzyCompare(matrix2(0, 1), 8));
	QVERIFY(qFuzzyCompare(matrix2(1, 0), 8.75));
	QVERIFY(qFuzzyCompare(matrix2(1, 1), -7.5));
}

TEST(Matrix, inverseNonSquare)
{
	Matrix matrix = {
	  {3  , 3.2, 3},
	  {3.5, 3.6, 3}
	};

	QVERIFY_EXCEPTION_THROWN(matrix.inverse(), std::out_of_range);
}

TEST(Matrix, inverseSingular)
{
	Matrix matrix = {
	  {3, 4},
	  {6, 8}
	};

	QVERIFY_EXCEPTION_THROWN(matrix.inverse(), std::out_of_range);
}

TEST(Matrix, solveSystemOfEquations)
{
	Matrix A =
	{
	  {1, 1,  1},
	  {0, 2,  5},
	  {2, 5, -1}
	};

	Vector b = { 6, -4, 27 };

	Vector x = A.inverse() * b;

	QVERIFY(qFuzzyCompare(x(0), 5));
	QVERIFY(qFuzzyCompare(x(1), 3));
	QVERIFY(qFuzzyCompare(x(2), -2));
}

TEST(Matrix, leastSquares)
{
	// Least squares
	// Suppose we have 5 points given by X and Y coordinates (2, 20), (6, 18), (20, 10), (30, 6), (40, 2) and want to fit a line through these points.
	// Line equation: y = ax + b
	// Compute a (slope) and b (y-intercept)

	// Create matrix with coefficients of line equation
	Matrix A =
	{ {2,  1},
	  {6,  1},
	  {20, 1},
	  {30, 1},
	  {40, 1} };

	Vector b = { 20, 18, 10, 6, 2 };

	// Compute x
	Vector x = (A.transposed() * A).inverse() * A.transposed() * b;
	// Slope = x(0)
	// Y-intercept = x(1)

	// Compute residuals (error vector)
	//Vector e = b - (A * x);

	QCOMPARE(x(0), -0.480376766091052); // Fuzzy compare?
	QCOMPARE(x(1), 20.61538461538461);  // Fuzzy compare?
}
*/