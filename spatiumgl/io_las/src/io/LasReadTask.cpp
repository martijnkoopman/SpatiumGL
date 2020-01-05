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

#include "spatiumgl/io/LasReadTask.hpp"
#include "LasReadTaskImpl.hpp"
#include "spatiumgl/io/LasUtils.hpp"

namespace spgl {
namespace io {

LasReadTask::LasReadTask(const std::string& path,
                         bool readRgb,
                         LasScalars readScalars)
  : m_lasReader(path)
  , m_readRgb(readRgb)
  , m_readScalars(readScalars)
{}

std::string
LasReadTask::validate()
{
  // Validate able to open file
  if (!m_lasReader.isOpen()) {
    if (!m_lasReader.open()) {
      return "Unable to open LAS/LAZ file.";
    }
  }

  // Validate scalars to read based on LAS point data format
  const unsigned char point_data_format =
    m_lasReader.lasHeader().point_data_format;

  m_lasReader.close();

  if (m_readRgb && !LasUtils::formatHasRgb(point_data_format)) {
    return "Requested to read RGB color, but point data format " +
           std::to_string(point_data_format) +
           " doesn't support RGB. Color will be empty";
  }

  if (m_readScalars == LasScalars::GpsTime &&
      !LasUtils::formatHasGpsTime(point_data_format)) {
    return "Requested to read GPS Time, but point data format " +
           std::to_string(point_data_format) +
           " doesn't support GPS Time. Scalars will be empty.";
  }

  if (m_readScalars == LasScalars::Nir &&
      !LasUtils::formatHasNir(point_data_format)) {
    return "Requested to read NIR, but point data format " +
           std::to_string(point_data_format) +
           " doesn't support NIR. Scalars will be empty.";
  }

  return {};
}

void
LasReadTask::run()
{
  RunningGaurd gaurd(running());

  // Check file is ready (Apparently not?)
  //if (!m_reader->isReady()) {
  //  setProgressMessage("Failed to activate LAS/LAZ reader.");
  //  return;
  //}

  // Open file (if it isn't yet)
  if (!m_lasReader.isOpen()) {
    if (!m_lasReader.open()) {
      setProgressMessage("Failed to open LAS/LAZ file.");
      return;
    }
  }

  // Read point cloud metrics from file header
  const LasHeader &lasHeader = m_lasReader.lasHeader();
  const bool hasColors =
    LasUtils::formatHasRgb(lasHeader.point_data_format) && m_readRgb;

  if (m_readScalars == LasScalars::GpsTime &&
      LasUtils::formatHasGpsTime(lasHeader.point_data_format)) {
    m_readScalars = LasScalars::None;
  }
  if (m_readScalars == LasScalars::Nir &&
      LasUtils::formatHasNir(lasHeader.point_data_format)) {
    m_readScalars = LasScalars::None;
  }
  const bool hasScalars = (m_readScalars != LasScalars::None);

  const size_t pointCount = static_cast<const size_t>(
    lasHeader.number_of_point_records); // warning cast: long long to size_t

  // Allocate memory for points positions
  std::vector<Vector3f> pointPositions;
  pointPositions.reserve(pointCount);

  // Allocate memory for points colors
  std::vector<Vector3f> pointColors;
  if (hasColors)
  {
    pointColors.reserve(pointCount);
  }

  // Allocate memory for point scalars
  gfx3d::Scalars<float> pointScalars;
  if (hasScalars)
  {
    pointScalars.reserve(pointCount);
  }

  // Keep track of progress
  const size_t onePercent = pointCount / 100;
  int progress = 0;
  size_t pointIndex = 0;

  // Read points from file
  while (m_lasReader.readLasPoint()) {

    const LasPoint& lasPoint = m_lasReader.lasPoint();

    // Add to position vector
    pointPositions.push_back(lasPoint.xyz.staticCast<float>());

    // Add to color vector
    if (hasColors) {
      // TODO: Unsigned short to float
      //pointColors.emplace_back(lasPoint.rgb[0], );
    }

    // Add scalar vector
    if (hasScalars) {
      pointScalars.addValue(lasPoint.scalarValue(m_readScalars));
    }

    // Update progress percentage
    if (onePercent > 0) {
      pointIndex++;
      const int curProgress = static_cast<int>(pointIndex / onePercent);
      if (curProgress > progress) {
        progress = curProgress;
        setProgressPercentage(progress);
      }
    }
  }

  // Compute extent from point statistics
  const LasPointStatistics& pointStatistics = m_lasReader.lasPointStatistics();
  const BoundingBox extent = BoundingBox::fromMinMax(
    Vector3(pointStatistics.min().xyz) + lasHeader.extent.min(),
    Vector3(pointStatistics.max().xyz) + lasHeader.extent.min());

  // Construct point cloud header
  gfx3d::PointCloudHeader header(
    pointCount, hasColors, hasScalars, extent);
  gfx3d::PointCloudData data(std::move(pointPositions), std::move(pointColors));
  std::shared_ptr<gfx3d::PointCloud> pointCloud =
    std::make_shared<gfx3d::PointCloud>(header, std::move(data));

  // Expose result
  setResult(pointCloud);
}

} // namespace io
} // namespace spgl
