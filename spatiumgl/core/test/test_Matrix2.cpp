#include <gtest/gtest.h>

#include <spatiumgl/Matrix2x2.hpp>

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

namespace spgl = spatiumgl;

TEST(Matrix2, constructor)
{
}

TEST(Matrix2, multiplyMatrix)
{
	// 1 2
	// 3 4
	spgl::Matrix2 m1 = {{ 1,3 }, { 2,4 }};

	// 5 6
	// 7 8
	spgl::Matrix2 m2 = { { 5,7 }, { 6,8 } };

	// Multiply
	const spatiumgl::Matrix2 result = m1 * m2;

	// Compare

	EXPECT_EQ(result[0][0], 19);
	EXPECT_EQ(result[0][1], 43);
	EXPECT_EQ(result[1][0], 22);
	EXPECT_EQ(result[1][1], 50);
}