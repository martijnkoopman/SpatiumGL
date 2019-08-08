//#define SPATIUMGL_SINGLE_PRECISION
#include <spatiumgl/io/PointCloudReader.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
	spatiumgl::PointCloudReader reader;
	reader.setPath("C:\\Users\\Martijn\\Downloads\\autzen.laz");
	reader.open();
	auto b = reader.bounds();

	return 0;
}