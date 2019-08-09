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
	if (!reader.isActive())
	{
		std::cerr << "Invalid input file: " << path << std::endl;
		return 1;
	}

	if (!reader.open())
	{
		std::cerr << "Unable to open file: " << path << std::endl;
		return 1;
	}

	std::cout << "Point count: " << reader.pointCount() << std::endl;
	std::cout << "Has color: " << (reader.hasColor() ? "true" : "false") << std::endl;
	std::cout << "Bounds: " << reader.bounds() << std::endl;

	return 0;
}