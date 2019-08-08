//#define SPATIUMGL_SINGLE_PRECISION
#include <spatiumgl/io/PointCloudReader.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
	// Get path from command line arguments
	if (argc != 2)
	{
		std::cerr << "usage:" << std::endl;
		std::cerr << "pcinfo file.las" << std::endl;
		return 1;
	}
	std::string path = argv[1];

	spatiumgl::PointCloudReader reader;
	reader.setPath(path);
	bool active = reader.isActive();
	reader.open();
	bool open = reader.isOpen();
	long long int pointCount = reader.pointCount();
	bool hasColor = reader.hasColor();
	auto b = reader.bounds();

	return 0;
}