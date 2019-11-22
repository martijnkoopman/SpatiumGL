#include <gtest/gtest.h>

#include <spatiumgl/io/LasReadTask.hpp>
#include <spatiumgl/io/LasWriter.hpp>

TEST(LasIO, writeReadPositions)
{
  // Construct points vector
  std::vector<spgl::Vector3> positions;
  positions.emplace_back(0, 0, 0);
  positions.emplace_back(100, 0, 0);
  positions.emplace_back(100, 100, 0);
  positions.emplace_back(0, 100, 0);

  // Construct point cloud header + data
  spgl::gfx3d::PointCloudData dataOut(std::move(positions));
  spgl::gfx3d::PointCloudHeader headerOut =
    spgl::gfx3d::PointCloudHeader::constructFromData(dataOut);

  // Construct point cloud
  const spgl::gfx3d::PointCloud pointCloudOut(headerOut, std::move(dataOut));

  // Create writer
  const std::string path("positions.las");
  spgl::io::LasWriter writer(path);
  EXPECT_TRUE(writer.isReady());

  // Write point cloud
  EXPECT_TRUE(writer.writePointCloud(pointCloudOut));

  // Create reader
  spgl::io::LasReadTask readTask(path);
  EXPECT_TRUE(readTask.isReady());
  EXPECT_TRUE(readTask.open());

  // Check header
  const auto readerCount = readTask.pointCount();
  const bool readerHasColor = readTask.hasColors();
  const auto readerExtent = readTask.extent();
  EXPECT_EQ(pointCloudOut.header().pointCount(), readerCount);
  EXPECT_EQ(pointCloudOut.header().hasColors(), readerHasColor);
  EXPECT_EQ(pointCloudOut.header().extent().min(), readerExtent.min());
  EXPECT_EQ(pointCloudOut.header().extent().max(), readerExtent.max());

  // Read point cloud
  readTask.start();
  readTask.join();

  // Get and check result
  std::shared_ptr<spgl::gfx3d::PointCloud> pointCloudIn = readTask.result();
  EXPECT_NE(pointCloudIn, nullptr);
  if (pointCloudIn == nullptr) {
    return;
  }

  // Check point cloud
  EXPECT_EQ(pointCloudOut.header().pointCount(), pointCloudIn->header().pointCount());
  EXPECT_EQ(pointCloudOut.header().hasColors(), pointCloudIn->header().hasColors());
  EXPECT_EQ(pointCloudOut.header().extent().min(), pointCloudIn->header().extent().min());
  EXPECT_EQ(pointCloudOut.header().extent().max(), pointCloudIn->header().extent().max());
}

TEST(LasIO, writeReadColorsCompressed)
{
  // Construct point cloud
  std::vector<spgl::Vector3> positions;
  positions.emplace_back(0, 0, 0);
  positions.emplace_back(100, 0, 0);
  positions.emplace_back(100, 100, 0);
  positions.emplace_back(0, 100, 0);

  std::vector<spgl::Vector3> colors;
  colors.emplace_back(1, 0, 0);
  colors.emplace_back(0, 1, 0);
  colors.emplace_back(0, 0, 1);
  colors.emplace_back(1, 1, 0);

  // Construct point cloud header + data
  spgl::gfx3d::PointCloudData dataOut(std::move(positions));
  spgl::gfx3d::PointCloudHeader headerOut =
    spgl::gfx3d::PointCloudHeader::constructFromData(dataOut);
  const spgl::gfx3d::PointCloud pointCloudOut(headerOut, std::move(dataOut));

  // Create writer
  const std::string path("colors.laz");
  spgl::io::LasWriter writer(path);
  EXPECT_TRUE(writer.isReady());

  // Write point cloud
  EXPECT_TRUE(writer.writePointCloud(pointCloudOut));

  // Create reader
  spgl::io::LasReadTask readTask(path);
  EXPECT_TRUE(readTask.isReady());
  EXPECT_TRUE(readTask.open());

  // Check header
  const auto readCount = readTask.pointCount();
  const bool readHasColor = readTask.hasColors();
  const auto readExent = readTask.extent();
  EXPECT_EQ(pointCloudOut.header().pointCount(), readCount);
  EXPECT_EQ(pointCloudOut.header().hasColors(), readHasColor);
  EXPECT_EQ(pointCloudOut.header().extent().min(), readExent.min());
  EXPECT_EQ(pointCloudOut.header().extent().max(), readExent.max());

  // Read point cloud
  readTask.start();
  readTask.join();

  // Get and check result
  std::shared_ptr<spgl::gfx3d::PointCloud> pointCloudIn = readTask.result();
  EXPECT_NE(pointCloudIn, nullptr);
  if (pointCloudIn == nullptr) {
    return;
  }

  // Check point cloud
  EXPECT_EQ(pointCloudOut.header().pointCount(), pointCloudIn->header().pointCount());
  EXPECT_EQ(pointCloudOut.header().hasColors(), pointCloudIn->header().hasColors());
  EXPECT_EQ(pointCloudOut.header().extent().min(), pointCloudIn->header().extent().min());
  EXPECT_EQ(pointCloudOut.header().extent().max(), pointCloudIn->header().extent().max());
}
