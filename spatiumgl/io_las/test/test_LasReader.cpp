#include <gtest/gtest.h>

#include <spatiumgl/io/LasReader.hpp>

namespace spgl = spatiumgl;

TEST(LasReader, readAll)
{
	// Open file
	const std::string path("C:\\Users\\Martijn\\Downloads\\autzen2.laz");
	spgl::io::LasReader reader;
	reader.setPath(path);
	EXPECT_TRUE(reader.isActive());
	EXPECT_TRUE(reader.open());

	// Check header
	const auto readerCount = reader.pointCount();
	const bool readerHasColor = reader.hasColor();
	const auto readerBounds = reader.bounds();

	// Read all
	spgl::gfx3d::PointCloud pointCloud = reader.readAll();

	EXPECT_EQ(pointCloud.pointCount(), readerCount);
	EXPECT_EQ(pointCloud.hasColors(), readerHasColor);
	//EXPECT_EQ(pointCloud.bounds(), readerBounds);
	std::cout << "Bounds1: " << readerBounds << std::endl;
	std::cout << "Bounds2: " << pointCloud.bounds() << std::endl;
}