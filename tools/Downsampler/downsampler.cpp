#include "lasreader.hpp"
#include "laswriter.hpp"

#include <array>
#include <unordered_map>
#include <functional> // std::hash
#include <algorithm> // std::max
#include <cassert> // assert
#include <cmath> // std::floor, std::nan, std::sqrt
#include <string> // std::to_string

#include <iostream>

/*
struct IndexHash : public std::hash<std::array<int, 3>>
{
	std::size_t operator()(std::array<int, 3 const& index) const noexcept
	{
		std::size_t h1 = std::hash<std::string>{}(s.first_name);
		std::size_t h2 = std::hash<std::string>{}(s.last_name);
		return h1 ^ (h2 << 1); // or use boost::hash_combine (see Discussion)
	}
};
*/



class Downsampler
{
public:

	Downsampler(const std::array<double, 6> extent, int division)
	  : m_extent(extent)
	  , m_division(division < 1 ? 1 : division)
	  , m_map()
	  , m_cellSize(1)
	{
		// Make extent cubic
		double max = std::max((extent[3] - extent[0]), std::max((extent[4] - extent[2]), (extent[5] - extent[3])));
		m_extent[3] = m_extent[0] + max;
		m_extent[4] = m_extent[1] + max;
		m_extent[5] = m_extent[2] + max;

		// Compute cell size
		m_cellSize = (m_extent[3] - m_extent[0]) / m_division;
	}

	void clear()
	{
		m_map.clear();
	}

	/// \param[out] outPoint Point not included it downsampled cloud
	/// \return True if point should be passed through
	bool processPoint(const std::array<double, 3> &point, std::array<double, 3> &outPoint)
	{
		// Check within extent
		if (point[0] < m_extent[0] || point[0] > m_extent[3] ||
			point[1] < m_extent[1] || point[1] > m_extent[4] ||
			point[2] < m_extent[2] || point[2] > m_extent[5])
		{
			return false;
		}

		// Compute index in grid
		std::array<double, 3> relative = { point[0] - m_extent[0], 
										   point[1] - m_extent[1], 
										   point[2] - m_extent[2] };
		std::array<int, 3> index = { static_cast<int>(std::floor(relative[0] / m_cellSize)),
									 static_cast<int>(std::floor(relative[1] / m_cellSize)),
									 static_cast<int>(std::floor(relative[2] / m_cellSize)) };

		// Check for existing entry in downsample map
		std::string key = std::to_string(index[0]) + std::to_string(index[1]) + std::to_string(index[2]);
		if (m_map.count(key) > 0)
		{
			// Existing point in cell
			std::array<double, 3> cellPoint = m_map[key];

			// Compute distance to cell center for both points
			std::array<double, 3> cellCenter = { (index[0] + 0.5) * m_cellSize,
												 (index[1] + 0.5) * m_cellSize,
												 (index[2] + 0.5) * m_cellSize };
			std::array<double, 3> delta = { cellCenter[0] - cellPoint[0], 
											cellCenter[1] - cellPoint[1], 
											cellCenter[1] - cellPoint[2] };
			double cellPointDistance = sqrt(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);
			delta = { cellCenter[0] - point[0],
				      cellCenter[1] - point[1],
					  cellCenter[1] - point[2] };
			double newPointDistance = sqrt(delta[0] * delta[0] + delta[1] * delta[1] + delta[2] * delta[2]);

			// Compare distances to cell center
			if (newPointDistance < cellPointDistance)
			{
				// New point is closer to cell center
				// Replace point in downsample cloud
				m_map[key] = point;

				// Output previous cell point
				outPoint = cellPoint;
				return true;
			}
			else
			{
				// New point is NOT closer to cell center
				// Output this point
				outPoint = point;
				return true;
			}
		}
		else
		{
			// First point in this cell
			m_map[key] = point;

			// Do not return any point. It is now part of the downsample cloud.
			return false;
		}

		return false; // unreachable code, unless an exception occurs
	}

	void print() const
	{
		for (auto it = m_map.cbegin(); it != m_map.cend(); ++it)
		{
			std::array<double, 3> point = it->second;
			std::cout << " " << it->first << ": " << point[0] << " " << point[1] << "  " << point[2] << std::endl;
		}
		std::cout << std::endl;
	}

protected:
	std::array<double, 6> m_extent;
	int m_division;
	std::unordered_map <std::string, std::array<double, 3>> m_map; //Key = index in bins, value = point coordinates
	double m_cellSize;
};

int main(int argc, char *argv[])
{
  LASreadOpener lasreadopener;
  lasreadopener.set_file_name("C:\\Users\\Martijn\\Downloads\\autzen.laz");
  LASreader* reader = lasreadopener.open();


  std::array<double, 6> extent = { reader->header.min_x, reader->header.min_y, reader->header.min_z, reader->header.max_x, reader->header.max_y, reader->header.max_z };
  std::cout << reader->header.number_of_point_records << std::endl;

  Downsampler downsampler(extent, 1024);

  //LASwriteOpener laswriteopener;
  //laswriteopener.set_file_name("C:\\Users\\Martijn\\Downloads\\autzen2.las");
  //LASwriter* laswriter = laswriteopener.open(&reader->header);

  long pointCount = 0;
  while (reader->read_point())
  {
	  pointCount++;
	  if (pointCount > reader->header.number_of_point_records / 10)
		  break;

	  std::array<double, 3> inPoint = { reader->point.get_x(), reader->point.get_y(), reader->point.get_z() };
	  std::array<double, 3> outPoint;
	  if (downsampler.processPoint(inPoint, outPoint))
	  {
		  //std::cout << "Write: " << outPoint[0] << " " << outPoint[1] << " " << outPoint[2] << std::endl;
	  }
  }

  downsampler.print();

  //laswriter->write_point(&lasreader->point);

  //laswriter->close();
  //delete laswriter;

  reader->close();
  delete reader;

  return 0;
}