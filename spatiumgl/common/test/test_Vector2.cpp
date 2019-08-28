#include <gtest/gtest.h>

#include <spatiumgl/Vector.hpp>

// constructor 
// constructorEmpty
// constructorInitializerList
// add
// subtract
// multiplyScalar
// divideScalar
// length
// normalize
// normalized
// dot
// angle
// project
// output

TEST(Vector2, constructor)
{
	spatiumgl::Vector2 v(1, 2);
	EXPECT_EQ(v.x(), 1);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v.y(), 2);
	EXPECT_EQ(v[1], 2);
}

TEST(Vector2, constructorEmpty)
{
	spatiumgl::Vector2 v;
	EXPECT_EQ(v[0], 0);
	EXPECT_EQ(v[1], 0);
}

TEST(Vector2, constructorInitializerList)
{
	spatiumgl::Vector2 v1({ 1, 2 });
	EXPECT_EQ(v1[0], 1);
	EXPECT_EQ(v1[1], 2);

	spatiumgl::Vector2 v2 = { 1, 2 };
	EXPECT_EQ(v2[0], 1);
	EXPECT_EQ(v2[1], 2);
}

TEST(Vector2, accessValue)
{
	spatiumgl::Vector2 v(1, 2);

	// X
	double x = v[0];
	EXPECT_EQ(x, 1);
	x = v.x();
	EXPECT_EQ(x, 1);

	// Y
	double y = v[1];
	EXPECT_EQ(y, 2);
	y = v.y();
	EXPECT_EQ(y, 2);
}

TEST(Vector2, accessReference)
{
	spatiumgl::Vector2 v(1, 2);

	// X
	v[0] = 3;
	EXPECT_EQ(v[0], 3);
	v.x() = 5;
	EXPECT_EQ(v[0], 5);

	// Y
	v[1] = 4;
	EXPECT_EQ(v[1], 4);
	v.y() = 6;
	EXPECT_EQ(v[1], 6);
}

TEST(Vector2, add)
{
	spatiumgl::Vector2 v1(1, 2);
	spatiumgl::Vector2 v2(2, 3);
	spatiumgl::Vector2 v3 = v1 + v2;
	EXPECT_EQ(v3[0], 3);
	EXPECT_EQ(v3[1], 5);
}

TEST(Vector2, subtract)
{
	spatiumgl::Vector2 v1(1, 2);
	spatiumgl::Vector2 v2(2, 3);
	spatiumgl::Vector2 v3 = v1 - v2;
	EXPECT_EQ(v3[0], -1);
	EXPECT_EQ(v3[1], -1);
}

TEST(Vector2, multiplyScalar)
{
	spatiumgl::Vector2 v1(1, 2);
	spatiumgl::Vector2 v2 = v1 * 3;
	EXPECT_EQ(v2[0], 3);
	EXPECT_EQ(v2[1], 6);
}

TEST(Vector2, divideScalar)
{
	spatiumgl::Vector2 v1(3, 6);
	spatiumgl::Vector2 v2 = v1 / 3;
	EXPECT_EQ(v2[0], 1);
	EXPECT_EQ(v2[1], 2);
}

TEST(Vector2, length)
{
	spatiumgl::Vector2 v1(10, 0);
	EXPECT_EQ(v1.length(), 10);
	spatiumgl::Vector2 v2(0, 5);
	EXPECT_EQ(v2.length(), 5);
}

TEST(Vector2, normalize)
{
	spatiumgl::Vector2 v(10, 0);
	v.normalize();
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 0);
}

TEST(Vector2, normalized)
{
	spatiumgl::Vector2 v1(10, 0);
	spatiumgl::Vector2 v2 = v1.normalized();
	EXPECT_EQ(v2[0], 1);
	EXPECT_EQ(v2[1], 0);
}

TEST(Vector2, dot)
{
	spatiumgl::Vector2 v1(1, 0);
	spatiumgl::Vector2 v2(0, 1); // perpendicular
	spatiumgl::Vector2 v3(-1, 0); // parallel
	EXPECT_EQ(v1.dot(v2), 1);
	EXPECT_EQ(v1.dot(v3), 0);
}

TEST(Vector2, cross)
{
	ASSERT_TRUE(false);
}

TEST(Vector2, angle)
{
	ASSERT_TRUE(false);
}

TEST(Vector2, project)
{
	ASSERT_TRUE(false);
}

TEST(Vector2, output)
{
	spatiumgl::Vector2 v(1, 2);
	std::ostringstream ss;
	ss << v;
	EXPECT_EQ(ss.str(), "(1, 2)");
}
