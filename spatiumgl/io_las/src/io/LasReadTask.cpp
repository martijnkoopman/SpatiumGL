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

namespace spgl {
namespace io {

LasReadTask::LasReadTask(const std::string& path, const bool shiftToOrigin)
  : m_pimpl{ std::unique_ptr<LasReadTaskImpl>(
      new LasReadTaskImpl(path, shiftToOrigin)) }
{}

LasReadTask::~LasReadTask() = default;

void
LasReadTask::run()
{
  RunningGaurd gaurd(running());

  // Check file is ready (Apparently not?)
  //if (!m_pimpl->isReady()) {
  //  setProgressMessage("Failed to activate LAS/LAZ reader.");
  //  return;
  //}

  // Open file (if it isn't yet)
  if (!m_pimpl->isOpen()) {
    if (!m_pimpl->open()) {
      setProgressMessage("Failed to open LAS/LAZ file.");
      return;
    }
  }

  // Read point cloud metrics
  const bool hasColors = m_pimpl->hasColors();
  const size_t pointCount = static_cast<const size_t>(
    m_pimpl->pointCount()); // warning cast: long long to size_t (unsigned long)
  Vector3 originShift = m_pimpl->originShift();
  BoundingBox<double> extent;

  // Allocate memory for points positions
  std::vector<Vector3> pointPositions;
  pointPositions.reserve(pointCount);

  // Allocate memory for points colors
  std::vector<Vector3> pointColors;
  if (hasColors)
  {
    pointColors.reserve(pointCount);
  }

  // Keep track of progress
  const size_t onePercent = pointCount / 100;
  int progressPercentage = 0;

  // Read first point and set initial extent
  size_t pointIndex = 0;
  if (m_pimpl->readPoint()) {
    // Add to position vector
    const Vector3 pos = m_pimpl->lastReadPointPosition();
    pointPositions[pointIndex] = pos;

    // Add to color vector
    if (hasColors) {
      pointColors[pointIndex] = m_pimpl->lastReadPointColor();
    }

    // Set initial extent
    extent.center() = pos;
    extent.radii() = {};

    pointIndex++;
  }

  // Read points from file
  while (m_pimpl->readPoint()) {
    // Add to position vector
    const Vector3 pos = m_pimpl->lastReadPointPosition();
    pointPositions[pointIndex] = pos;

    // Add to color vector
    if (hasColors) {
      pointColors[pointIndex] = m_pimpl->lastReadPointColor();
    }

    // Second or later point
    extent.include(pos);

    pointIndex++;

    // Update progress percentage
    if (onePercent > 0 && pointIndex > progressPercentage * onePercent) {
      progressPercentage = pointIndex / onePercent;
      setProgressPercentage(progressPercentage);
    }
  }

  // Construct point cloud header
  gfx3d::PointCloudHeader header(
    pointCount, hasColors, false, originShift, extent);
  gfx3d::PointCloudData data(std::move(pointPositions), std::move(pointColors));
  std::shared_ptr<gfx3d::PointCloud> pointCloud =
    std::make_shared<gfx3d::PointCloud>(header, std::move(data));

  // Expose result
  setResult(pointCloud);
}

bool
LasReadTask::isReady() const
{
  return m_pimpl->isReady();
}

bool
LasReadTask::open()
{
  return m_pimpl->open();
}

bool
LasReadTask::isOpen()
{
  return m_pimpl->isOpen();
}

void
LasReadTask::close()
{
  m_pimpl->close();
}

long long int
LasReadTask::pointCount() const
{
  return m_pimpl->pointCount();
}

bool
LasReadTask::hasColors() const
{
  return m_pimpl->hasColors();
}

BoundingBox<double>
LasReadTask::extent() const
{
  return m_pimpl->extent();
}
} // namespace io
} // namespace spgl
