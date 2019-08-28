#include <gtest/gtest.h>

#include <spatiumgl/Vector.hpp>
#include <spatiumgl/Matrix.hpp>
#include <spatiumgl/Image.hpp>

// accessValue
// accessReference

TEST(Vector, constructor)
{
	spatiumgl::Image<unsigned char, 3> img(640, 480);
	img[5][10][2] = 255;

	spatiumgl::Matrix3x3 m = { {1,2,3}, {4,5,6}, {7,8,9} };
	spatiumgl::Vector3 v2 = { 5, 2, 3 };
	spatiumgl::Vector3 res = m * v2;
	double val = m[1][2];
	EXPECT_EQ(m[1][2], 5);

	spatiumgl::Vector<double,3> v4 = { 1, 2, 3 };
	spatiumgl::Vector<double, 3> v1 = { 1, 2, 3 };
	spatiumgl::Vector3 v3 = v1 + v2;

	//bool equalNot = (v1 == v2);
	//bool equal = (v1 == v4);

	double x = v3.x();
}