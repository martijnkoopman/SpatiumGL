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

#include "spatiumgl/gfx3d/PointCloud.hpp"

namespace spatiumgl {
namespace gfx3d {

PointCloud::PointCloud()
  : RenderObject()
  , m_positions()
  , m_colors()
  , m_normals()
{}

PointCloud::PointCloud(const std::vector<Vector3>& positions,
                       const std::vector<Vector3>& colors,
                       const std::vector<Vector3>& normals)
  : RenderObject()
  , m_positions(positions)
  , m_colors(colors)
  , m_normals(normals)
{
  /// \todo std::move semantics for vectors

  // Update bounds
  if (m_positions.empty() == false) {
    // First point
    m_bounds.center() = m_positions[0];
    m_bounds.radii() = Vector3();

    for (size_t i = 1; i < m_positions.size(); i++) {
      // Second or later point
      m_bounds.include(m_positions[i]);
    }
  }
}

PointCloud::PointCloud(const size_t count,
                       const bool hasColors,
                       const bool hasNormals)
  : RenderObject()
  , m_positions()
  , m_colors()
  , m_normals()
{
  m_positions.reserve(count);
  if (hasColors) {
    m_colors.reserve(count);
  }
  if (hasNormals) {
    m_normals.reserve(count);
  }
}

size_t
PointCloud::pointCount() const
{
  return m_positions.size();
}

void
PointCloud::addPoint(const Vector3& position)
{
  if (m_positions.empty() == false) {
    // First point
    m_bounds.center() = position;
    m_bounds.radii() = Vector3();
  } else {
    // Second or later point
    m_bounds.include(position);
  }

  m_positions.push_back(position);
}

void
PointCloud::addPoint(const Vector3& position, const Vector3& color)
{
  addPoint(position);
  m_colors.push_back(color);
}

void
PointCloud::addPoint(const Vector3& position,
                     const Vector3& color,
                     const Vector3& normal)
{
  addPoint(position);
  m_colors.push_back(color);
  m_normals.push_back(normal);
}

// Positions

const Vector3&
PointCloud::position(size_t index) const
{
  // Check bounds?
  return m_positions[index];
}

const std::vector<Vector3>&
PointCloud::positions() const
{
  return m_positions;
}

// Colors

bool
PointCloud::hasColors() const
{
  return m_colors.empty() == false && m_colors.size() == m_positions.size();
}

Vector3&
PointCloud::color(size_t index)
{
  // Check bounds?
  return m_colors[index];
}

const Vector3&
PointCloud::color(size_t index) const
{
  // Check bounds?
  return m_colors[index];
}

const std::vector<Vector3>&
PointCloud::colors() const
{
  return m_colors;
}

// Normals

bool
PointCloud::hasNormals() const
{
  return m_normals.empty() == false && m_normals.size() == m_normals.size();
}

Vector3&
PointCloud::normal(size_t index)
{
  // Check bounds?
  return m_normals[index];
}

const Vector3&
PointCloud::normal(size_t index) const
{
  // Check bounds?
  return m_normals[index];
}

const std::vector<Vector3>&
PointCloud::normals() const
{
  return m_normals;
}

} // namespace gfx3d
} // namespace spatiumgl
