/*
 * Program: Spatium Graphics Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef SPATIUMGL_IOLAS_LASOCTANT_H
#define SPATIUMGL_IOLAS_LASOCTANT_H

#include "lasreader.hpp" // LASlib
#include "laswriter.hpp" // LASlib

#include <array>         // std::array
#include <cmath>         // std::pow
#include <iostream>      // std::cout
#include <memory>        // std::unique_ptr
#include <string>        // std::string
#include <unordered_map> // std::unordered_map
#include <cstring>       // std::memset, std::memcpy

using Point = std::array<double, 3>;
using Extent = std::array<Point, 2>;

class LasOctant
{
public:
  /// Constructor.
  ///
  /// \param[in] fileIn Input LAS file
  /// \param[in] fileOut Output LAS file (optional. If empty, overwrite fileIn)
  LasOctant(const std::string& fileIn, const std::string& fileOut = "")
    : m_fileIn(fileIn)
    , m_fileOut(fileOut)
    , m_lasReader(nullptr)
    , m_open(false)
  {
    if (m_fileOut.empty()) {
      m_fileOut = fileIn;
    }

    // Open file for reading
    LASreadOpener lasReadOpener;
    lasReadOpener.set_file_name(m_fileIn.c_str());
    if (lasReadOpener.active()) {
      m_lasReader.reset(lasReadOpener.open());
      if (m_lasReader != nullptr) {
        m_open = true;
      }
    }
  }

  /// Destructor
  ~LasOctant() { close(); }

  /// Process octant.
  ///
  /// \param[in] extent Octant extent
  /// \param[in] spacing Octant grid cell size (spacing)
  /// \return Written point counts for each child (8)
  std::array<long long, 8> process(const Extent& extent,
                                   const double spacing)
  {
    if (!isOpen()) {
      return {};
    }

    std::cout << "Processing node " << m_fileIn << std::endl;
    std::cout << " - Extent = (" << extent[0][0] << ", " << extent[0][1] << ", "
              << extent[0][2] << ") - (" << extent[1][0] << "," << extent[1][1]
              << "," << extent[1][2] << ")" << std::endl;
    std::cout << " - Spacing = " << spacing << std::endl;

    std::unordered_map<std::string, LASpoint> grid;

    // Read points
    Point position;
    while (m_lasReader->read_point()) {
      position[0] = m_lasReader->point.get_x();
      position[1] = m_lasReader->point.get_y();
      position[2] = m_lasReader->point.get_z();

      // Compute cell index in grid
      std::array<int, 3> gridIndex{
        static_cast<int>((position[0] - extent[0][0]) / spacing),
        static_cast<int>((position[1] - extent[0][1]) / spacing),
        static_cast<int>((position[2] - extent[0][2]) / spacing)
      };
      std::string gridIndexKey = std::to_string(gridIndex[0]) + "|" +
                                 std::to_string(gridIndex[1]) + "|" +
                                 std::to_string(gridIndex[0]);

      // Get grid cell point (if existing)
      LASpoint& gridPoint = grid[gridIndexKey];
      if (gridPoint.point == nullptr) {
        // No point in grid cell -> insert first point
        gridPoint.init(&m_lasReader->header,
                       m_lasReader->header.point_data_format,
                       m_lasReader->header.point_data_record_length,
                       &m_lasReader->header);
        gridPoint = m_lasReader->point; // copy assignment
      } else {
        // Get center point of grid cell
        Point cellCenter = {
          gridIndex[0] * spacing + 0.5 * spacing + extent[0][0],
          gridIndex[1] * spacing + 0.5 * spacing + extent[0][1],
          gridIndex[2] * spacing + 0.5 * spacing + extent[0][2]
        };

        Point gridPointPosition{ gridPoint.get_x(),
                                 gridPoint.get_y(),
                                 gridPoint.get_z() };

        // Compute distance to grid cell center
        double distanceGridPoint =
          sqrt(std::pow(gridPointPosition[0] - cellCenter[0], 2) +
               pow(gridPointPosition[1] - cellCenter[1], 2) +
               pow(gridPointPosition[2] - cellCenter[2], 2));

        double distanceNewPoint = sqrt(pow(position[0] - cellCenter[0], 2) +
                                       pow(position[1] - cellCenter[1], 2) +
                                       pow(position[2] - cellCenter[2], 2));

        if (distanceNewPoint < distanceGridPoint) {
          // Write grid cell point to file
          writePointToFile(
            LasOctant::computeChildIndex(gridPointPosition, extent), gridPoint);

          // Replace point in grid cell
          grid[gridIndexKey] = m_lasReader->point; // copy assignment
        } else {
          // Write new point to file
          writePointToFile(LasOctant::computeChildIndex(position, extent),
                           m_lasReader->point);
        }
      }
    }

    // Write grid points to file
    LASwriteOpener lasWriteOpener;
    lasWriteOpener.set_file_name(m_fileOut.c_str());
    std::memset(m_lasReader->header.system_identifier, '\0', 32);
    std::memcpy(m_lasReader->header.system_identifier, "Desktop", 8);
    std::memset(m_lasReader->header.generating_software, '\0', 32);
    std::memcpy(m_lasReader->header.generating_software, "SpatiumGL", 10);
    std::unique_ptr<LASwriter> lasWriter(
      lasWriteOpener.open(&m_lasReader->header));
    for (const auto& gridCell : grid) {
      lasWriter->write_point(&gridCell.second);
      lasWriter->update_inventory(&gridCell.second);
    }
    lasWriter->update_header(&m_lasReader->header, TRUE);
    lasWriter->close();
    std::cout << " - Point count = " << std::to_string(grid.size())
              << std::endl;

    // Close writers
    std::array<long long, 8> writtenPointCounts;
    for (size_t i = 0; i < 8; i++) {
      std::unique_ptr<LASwriter>& lasWriter = m_lasWriters[i];
      if (lasWriter == nullptr) {
        writtenPointCounts[i] = 0;
      } else {
        lasWriter->update_header(&m_lasReader->header, TRUE);
        writtenPointCounts[i] = lasWriter->close();
      }
    }
    return writtenPointCounts;
  }

  void writePointToFile(unsigned char fileIndex, const LASpoint& point)
  {
    std::unique_ptr<LASwriter>& lasWriter = m_lasWriters[fileIndex];
    // Open file for writing if needed
    if (lasWriter == nullptr) {
      LASwriteOpener lasWriteOpener;
      lasWriteOpener.set_file_name(
        LasOctant::computeFilePath(m_fileOut, fileIndex).c_str());
      lasWriter.reset(lasWriteOpener.open(&m_lasReader->header));
    }

    // Write point
    lasWriter->write_point(&point);
    lasWriter->update_inventory(&point);
  }

  void close()
  {
    if (m_lasReader != nullptr) {
      m_lasReader->close();
      m_open = false;
    }
  }

  bool isOpen() const { return m_open; }

  std::string fileOut() const { return m_fileOut; }

  /// Determine child index (0-7) of node by point position.
  ///
  /// \param[in] position Point position
  /// \param[in] extent Node extent
  /// \return Child idex
  static unsigned char computeChildIndex(const Point& position,
                                         const Extent& extent)
  {
    const Point center = { (extent[1][0] + extent[0][0]) * 0.5,
                           (extent[1][1] + extent[0][1]) * 0.5,
                           (extent[1][2] + extent[0][2]) * 0.5 };
    if (position[2] < center[2]) {
      // Bottom
      if (position[1] < center[1]) {
        // Bottom front
        if (position[0] < center[0]) {
          // Bottom front left
          return 0;
        } else {
          // Bottom front right
          return 1;
        }
      } else {
        // Bottom back
        if (position[0] < center[0]) {
          // Bottom back left
          return 2;
        } else {
          // Bottom back right
          return 3;
        }
      }
    } else {
      // Top
      if (position[1] < center[1]) {
        // Top front
        if (position[0] < center[0]) {
          // Top front left
          return 4;
        } else {
          // Top front right
          return 5;
        }
      } else {
        // Top back
        if (position[0] < center[0]) {
          // Top back left
          return 6;
        } else {
          // Top back right
          return 7;
        }
      }
    }
  }

  static Extent computeChildExtent(const Extent& extent,
                                   unsigned char childIndex)
  {
    const Point min = extent[0];
    const Point max = extent[1];
    const double d = (max[0] - min[0]) * 0.5; // diameter
    switch (childIndex) {
      case 0:
        // Bottom front left
        return { Point{ min[0], min[1], min[2] },
                 Point{ min[0] + d, min[1] + d, min[2] + d } };
      case 1:
        // Bottom front right
        return { Point{ min[0] + d, min[1], min[2] },
                 Point{ max[0], min[1] + d, min[2] + d } };
      case 2:
        // Bottom back left
        return { Point{ min[0], min[1] + d, min[2] },
                 Point{ min[0] + d, max[1], min[2] + d } };
      case 3:
        // Bottom back right
        return { Point{ min[0] + d, min[1] + d, min[2] },
                 Point{ max[0], max[1], min[2] + d } };
      case 4:
        // Top front left
        return { Point{ min[0], min[1], min[2] + d },
                 Point{ min[0] + d, min[1] + d, max[2] } };
      case 5: //
        // Top front right
        return { Point{ min[0] + d, min[1], min[2] + d },
                 Point{ max[0], min[1] + d, max[2] } };
      case 6: //
        // Top back left
        return { Point{ min[0], min[1] + d, min[2] + d },
                 Point{ min[0] + d, max[1], max[2] } };
      case 7: //
        // Top back right
        return { Point{ min[0] + d, min[1] + d, min[2] + d },
                 Point{ max[0], max[1], max[2] } };
      default:
        return {};
    }
  }

  /// Compute file path.
  ///
  /// \param[in] file File path of octant
  /// \param[in] childIndex Child octant index (0-7)
  /// \return File path
  static std::string computeFilePath(std::string file, unsigned char childIndex)
  {
    file.pop_back(); // -S
    file.pop_back(); // -A
    file.pop_back(); // -L
    file.pop_back(); // -.
    file += std::to_string(childIndex) + ".las";
    return file;
  }

protected:
  std::string m_fileIn;
  std::string m_fileOut;
  std::unique_ptr<LASreader> m_lasReader;
  bool m_open;
  std::array<std::unique_ptr<LASwriter>, 8> m_lasWriters;
};

#endif // SPATIUMGL_IOLAS_LASOCTANT_H
