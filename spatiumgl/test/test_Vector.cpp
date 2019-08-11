#include <gtest/gtest.h>

#include <spatiumgl/Vector.hpp>

TEST(Vector, Vector2_constructor)
{
	spatiumgl::Vector2 vector(1, 2);
	EXPECT_EQ(vector.x(), 1);
	EXPECT_EQ(vector[0], 1);
	EXPECT_EQ(vector.y(), 2);
	EXPECT_EQ(vector[1], 2);
}

TEST(Vector, Vector3_constructor)
{
	spatiumgl::Vector3 vector(1, 2, 3);
	EXPECT_EQ(vector.x(), 1);
	EXPECT_EQ(vector[0], 1);
	EXPECT_EQ(vector.y(), 2);
	EXPECT_EQ(vector[1], 2);
	EXPECT_EQ(vector.z(), 3);
	EXPECT_EQ(vector[2], 3);
}

TEST(Vector, Vector4_constructor)
{
	spatiumgl::Vector4 vector(1, 2, 3, 4);
	EXPECT_EQ(vector.x(), 1);
	EXPECT_EQ(vector[0], 1);
	EXPECT_EQ(vector.y(), 2);
	EXPECT_EQ(vector[1], 2);
	EXPECT_EQ(vector.z(), 3);
	EXPECT_EQ(vector[2], 3);
	EXPECT_EQ(vector.w(), 4);
	EXPECT_EQ(vector[3], 4);
}

TEST(Vector, Vector_data)
{
	spatiumgl::Vector3 vector = { 1, 2, 3 };
	SPATIUMGL_PRECISION* ptr = vector.data();
	EXPECT_EQ(*ptr, 1);
	EXPECT_EQ(*(ptr + 1), 2);
	EXPECT_EQ(*(ptr + 2), 3);
}

TEST(Vector, Vector3_multiplyScalar)
{
	spatiumgl::Vector3 vector1(1, 2, 3);
	const double scalar = 2;
	spatiumgl::Vector3 vector2 = vector1 * scalar;
	EXPECT_EQ(vector2.x(), 2);
	EXPECT_EQ(vector2.y(), 4);
	EXPECT_EQ(vector2.z(), 6);
}