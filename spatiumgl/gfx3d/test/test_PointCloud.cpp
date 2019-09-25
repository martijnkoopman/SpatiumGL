#include <gtest/gtest.h>

#include <spatiumgl/gfx3d/PointCloud.hpp>

TEST(PointCloud, constructor)
{
	const spatiumgl::Vector3 point1(1, 2, 3);
	const spatiumgl::Vector3 point2(4, 5, 6);
	const spatiumgl::Vector3 point3(7, 8, 9);

	std::vector<spatiumgl::Vector3> positions;
	positions.push_back(point1);
	positions.push_back(point2);
	positions.push_back(point3);
	const spatiumgl::gfx3d::PointCloud pointcloud(std::move(positions));

	EXPECT_EQ(pointcloud.pointCount(), 3);
	EXPECT_EQ(pointcloud.translation(0), point1);
	EXPECT_EQ(pointcloud.translation(1), point2);
	EXPECT_EQ(pointcloud.translation(2), point3);
}

TEST(PointCloud, addPoint)
{
	const spatiumgl::Vector3 point1(1, 2, 3);
	const spatiumgl::Vector3 point2(4, 5, 6);
	const spatiumgl::Vector3 point3(7, 8, 9);

	spatiumgl::gfx3d::PointCloud pointcloud;
	pointcloud.addPoint(point1);
	pointcloud.addPoint(point2);
	pointcloud.addPoint(point3);

	EXPECT_EQ(pointcloud.pointCount(), 3);
	EXPECT_EQ(pointcloud.translation(0), point1);
	EXPECT_EQ(pointcloud.translation(1), point2);
	EXPECT_EQ(pointcloud.translation(2), point3);
}