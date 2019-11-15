#include <gtest/gtest.h>

#include <spatiumgl/io/LasReader.hpp>
#include <spatiumgl/io/LasWriter.hpp>

namespace spgl = spatiumgl;

TEST(LasIO, writeReadPositions)
{
  // Construct point cloud
  std::vector<spgl::Vector3> positions;
  positions.emplace_back(0, 0, 0);
  positions.emplace_back(100, 0, 0);
  positions.emplace_back(100, 100, 0);
  positions.emplace_back(0, 100, 0);
  const spgl::gfx3d::PointCloud pointCloudOut(positions);

  // Create writer
  const std::string path("positions.las");
  spgl::io::LasWriter writer(path);
  EXPECT_TRUE(writer.isReady());

  // Write point cloud
  EXPECT_TRUE(writer.writePointCloud(pointCloudOut));

  // Create reader
  spgl::io::LasReader reader(path);
  EXPECT_TRUE(reader.isReady());
  EXPECT_TRUE(reader.open());

  // Check header
  const auto readerCount = reader.pointCount();
  const bool readerHasColor = reader.hasColors();
  const auto readerBounds = reader.bounds();
  EXPECT_EQ(pointCloudOut.pointCount(), readerCount);
  EXPECT_EQ(pointCloudOut.hasColors(), readerHasColor);
  EXPECT_EQ(pointCloudOut.bounds().min(), readerBounds.min());
  EXPECT_EQ(pointCloudOut.bounds().max(), readerBounds.max());

  // Read point cloud
  spgl::gfx3d::PointCloud pointCloudIn = reader.readAllPoints();

  // Check point cloud
  EXPECT_EQ(pointCloudOut.pointCount(), pointCloudIn.pointCount());
  EXPECT_EQ(pointCloudOut.hasColors(), pointCloudIn.hasColors());
  EXPECT_EQ(pointCloudOut.bounds().min(), pointCloudIn.bounds().min());
  EXPECT_EQ(pointCloudOut.bounds().max(), pointCloudIn.bounds().max());
}

TEST(LasIO, writeReadColors)
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

  const spgl::gfx3d::PointCloud pointCloudOut(positions, colors);

  // Create writer
  const std::string path("colors.las");
  spgl::io::LasWriter writer(path);
  EXPECT_TRUE(writer.isReady());

  // Write point cloud
  EXPECT_TRUE(writer.writePointCloud(pointCloudOut));

  // Create reader
  spgl::io::LasReader reader(path);
  EXPECT_TRUE(reader.isReady());
  EXPECT_TRUE(reader.open());

  // Check header
  const auto readerCount = reader.pointCount();
  const bool readerHasColor = reader.hasColors();
  const auto readerBounds = reader.bounds();
  EXPECT_EQ(pointCloudOut.pointCount(), readerCount);
  EXPECT_EQ(pointCloudOut.hasColors(), readerHasColor);
  EXPECT_EQ(pointCloudOut.bounds().min(), readerBounds.min());
  EXPECT_EQ(pointCloudOut.bounds().max(), readerBounds.max());

  // Read point cloud
  spgl::gfx3d::PointCloud pointCloudIn = reader.readAllPoints();

  // Check point cloud
  EXPECT_EQ(pointCloudOut.pointCount(), pointCloudIn.pointCount());
  EXPECT_EQ(pointCloudOut.hasColors(), pointCloudIn.hasColors());
  EXPECT_EQ(pointCloudOut.bounds().min(), pointCloudIn.bounds().min());
  EXPECT_EQ(pointCloudOut.bounds().max(), pointCloudIn.bounds().max());
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

  const spgl::gfx3d::PointCloud pointCloudOut(positions, colors);

  // Create writer
  const std::string path("colors.laz");
  spgl::io::LasWriter writer(path);
  EXPECT_TRUE(writer.isReady());

  // Write point cloud
  EXPECT_TRUE(writer.writePointCloud(pointCloudOut));

  // Create reader
  spgl::io::LasReader reader(path);
  EXPECT_TRUE(reader.isReady());
  EXPECT_TRUE(reader.open());

  // Check header
  const auto readerCount = reader.pointCount();
  const bool readerHasColor = reader.hasColors();
  const auto readerBounds = reader.bounds();
  EXPECT_EQ(pointCloudOut.pointCount(), readerCount);
  EXPECT_EQ(pointCloudOut.hasColors(), readerHasColor);
  EXPECT_EQ(pointCloudOut.bounds().min(), readerBounds.min());
  EXPECT_EQ(pointCloudOut.bounds().max(), readerBounds.max());

  // Read point cloud
  spgl::gfx3d::PointCloud pointCloudIn = reader.readAllPoints();

  // Check point cloud
  EXPECT_EQ(pointCloudOut.pointCount(), pointCloudIn.pointCount());
  EXPECT_EQ(pointCloudOut.hasColors(), pointCloudIn.hasColors());
  EXPECT_EQ(pointCloudOut.bounds().min(), pointCloudIn.bounds().min());
  EXPECT_EQ(pointCloudOut.bounds().max(), pointCloudIn.bounds().max());
}