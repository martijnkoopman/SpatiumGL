#include <gtest/gtest.h>

#include <spatiumgl/gfx3d/Transform.hpp>

TEST(Transform, defaultConstructor)
{
	const spatiumgl::gfx3d::Transform transform;

	EXPECT_EQ(transform.right(), spatiumgl::Vector3(1, 0, 0));
	EXPECT_EQ(transform.up(), spatiumgl::Vector3(0, 1, 0));
	EXPECT_EQ(transform.back(), spatiumgl::Vector3(0, 0, 1));
	EXPECT_EQ(transform.translation(), spatiumgl::Vector3(0, 0, 0));
}

TEST(Transform, position)
{
	const spatiumgl::Vector3 position(1, 2, 3);

	spatiumgl::gfx3d::Transform transform;
	transform.setTranslation(position);
	EXPECT_EQ(transform.translation(), position);
}

TEST(Transform, rotation)
{
	//const spatiumgl::Vector3 rotationZ(0, 0, 90 * spatiumgl::);
	//spatiumgl::gfx3d::Transform transform;
	//transform.setTranslation(rotationZ);
}