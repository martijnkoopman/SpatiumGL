#include <gtest/gtest.h>

#include <spatiumgl/Bounds.hpp>
#include <spatiumgl/gfx3d/PointCloud.hpp>

TEST(PointCloud, constructor)
{
  const spgl::Vector3f point1(1, 2, 3);
  const spgl::Vector3f point2(4, 5, 6);
  const spgl::Vector3f point3(7, 8, 9);

  std::vector<spgl::Vector3f> positions;
  positions.push_back(point1);
  positions.push_back(point2);
  positions.push_back(point3);

  // Construct point cloud data
  spgl::gfx3d::PointCloudData data(std::move(positions));

  // Positions should be moved
  EXPECT_EQ(positions.size(), 0);
  EXPECT_EQ(data.positions().size(), 3);

  // Construct point cloud header
  spgl::gfx3d::PointCloudHeader header =
    spgl::gfx3d::PointCloudHeader::constructFromData(data);

  EXPECT_EQ(header.pointCount(), 3);
  EXPECT_EQ(header.hasColors(), false);
  EXPECT_EQ(header.hasScalars(), false);
  EXPECT_EQ(header.extent(), spgl::BoundingBox({ 4, 5, 6 }, { 3, 3, 3 }));

  const spgl::gfx3d::PointCloud pointcloud(header, std::move(data));

  // Point cloud data should be moved
  EXPECT_EQ(data.positions().size(), 0);
  EXPECT_EQ(pointcloud.data().positions().size(), 3);
  EXPECT_EQ(pointcloud.data().positions()[0], point1);
  EXPECT_EQ(pointcloud.data().positions()[1], point2);
  EXPECT_EQ(pointcloud.data().positions()[2], point3);

  // Point cloud header should not be moved
  EXPECT_EQ(header.pointCount(), 3);
  EXPECT_EQ(header.hasColors(), false);
  EXPECT_EQ(header.hasScalars(), false);
  EXPECT_EQ(header.extent(), spgl::BoundingBox({ 4, 5, 6 }, { 3, 3, 3 }));
}

TEST(PointCloud, copy)
{
  // Construct point cloud
  std::vector<spgl::Vector3f> positions;
  positions.emplace_back(1, 2, 3);
  positions.emplace_back(4, 5, 6);
  positions.emplace_back(7, 8, 9);
  spgl::gfx3d::PointCloudData data(std::move(positions));
  spgl::gfx3d::PointCloudHeader header =
    spgl::gfx3d::PointCloudHeader::constructFromData(data);
  spgl::gfx3d::PointCloud pointCloud(header, std::move(data));

  // Copy via copy constructor
  spgl::gfx3d::PointCloud pointCloudCopy1(pointCloud);
  EXPECT_EQ(pointCloud.header(), pointCloudCopy1.header());
  EXPECT_EQ(pointCloud.data().positions(), pointCloudCopy1.data().positions());

  // Copy via copy assignment operator
  spgl::gfx3d::PointCloud pointCloudCopy2 = pointCloud;
  EXPECT_EQ(pointCloud.header(), pointCloudCopy2.header());
  EXPECT_EQ(pointCloud.data().positions(), pointCloudCopy2.data().positions());
}

TEST(PointCloud, moveConstructor)
{
  // Construct point cloud
  std::vector<spgl::Vector3f> positions;
  positions.emplace_back(1, 2, 3);
  positions.emplace_back(4, 5, 6);
  positions.emplace_back(7, 8, 9);
  spgl::gfx3d::PointCloudData data(std::move(positions));
  spgl::gfx3d::PointCloudHeader header =
    spgl::gfx3d::PointCloudHeader::constructFromData(data);
  spgl::gfx3d::PointCloud pointCloud(header, std::move(data));

  // Move via move constructor
  spgl::gfx3d::PointCloud pointCloudMoved(std::move(pointCloud));

  // Header should be copied
  EXPECT_EQ(pointCloud.header(), pointCloudMoved.header());

  // Data shoule be moved
  EXPECT_EQ(pointCloud.data().positions().size(), 0);
  EXPECT_EQ(pointCloudMoved.data().positions().size(), 3);
}

TEST(PointCloud, moveAssignment)
{
  // Construct point cloud
  std::vector<spgl::Vector3f> positions;
  positions.emplace_back(1, 2, 3);
  positions.emplace_back(4, 5, 6);
  positions.emplace_back(7, 8, 9);
  spgl::gfx3d::PointCloudData data(std::move(positions));
  spgl::gfx3d::PointCloudHeader header =
    spgl::gfx3d::PointCloudHeader::constructFromData(data);
  spgl::gfx3d::PointCloud pointCloud(header, std::move(data));

  // Move via move assignment
  spgl::gfx3d::PointCloud pointCloudMoved = std::move(pointCloud);

  // Header should be copied
  EXPECT_EQ(pointCloud.header(), pointCloudMoved.header());

  // Data shoule be moved
  EXPECT_EQ(pointCloud.data().positions().size(), 0);
  EXPECT_EQ(pointCloudMoved.data().positions().size(), 3);
}
