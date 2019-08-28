#include <gtest/gtest.h>

#include <spatiumgl/gfx3d/PointCloud.hpp>

TEST(PointCloud, constructor)
{
	std::vector<spatiumgl::Vector3> positions;
	positions.push_back({ 1,2,3 });
	positions.push_back({ 4,5,6 });
	positions.push_back({ 7,8,9 });
	spatiumgl::PointCloud pointcloud(positions);

	EXPECT_EQ(pointcloud.pointCount(), 3);
	EXPECT_EQ(pointcloud.positions()[0], spatiumgl::Vector3(1,2,3));
	EXPECT_EQ(pointcloud.positions()[0], spatiumgl::Vector3(1, 2, 3));
	EXPECT_EQ(pointcloud.positions()[0], spatiumgl::Vector3(4, 5, 6));
	EXPECT_EQ(pointcloud.positions()[0], spatiumgl::Vector3(7, 8, 9));
}