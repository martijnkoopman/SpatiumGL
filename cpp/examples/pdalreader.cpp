#include <pdal/Options.hpp>
#include <pdal/PointView.hpp>
#include <io/LasReader.hpp>

int main(int argc, char* argv[])
{
	using namespace pdal;

	Options ops;
	ops.add(std::string("filename"), std::string("C:\\Users\\Martijn\\Downloads\\autzen.laz")); // file name
	//ops.add("count", 1000); // read 1000 points at a time

	LasReader reader;
	reader.setOptions(ops);

	PointTable table;
	reader.prepare(table);

	// Check file header
	LasHeader h = reader.header();
	//h.pointCount()
	//h.maxX()
	//h.maxY()
	//h.maxZ()
	//h.minX()
	//h.minY()
	//h.minZ()

	// Read points
	PointViewSet viewSet = reader.execute(table);


	return 0;
}