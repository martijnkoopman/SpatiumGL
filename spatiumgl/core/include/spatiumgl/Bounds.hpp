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

#ifndef SPATIUMGL_GFX3D_BOUNDS_H
#define SPATIUMGL_GFX3D_BOUNDS_H

#include "Vector.hpp"

#include <vector> // std::vector

namespace spgl {

/// \class BoundsCenter
/// \brief Boundaries with a center (all of them).
///
/// This class cannot be instantiated directly, it must be inherited.
template<typename T, size_t N>
struct SPATIUMGL_EXPORT BoundsCenter
{
public:
  /// Get center position (by reference)
  ///
  /// \return Center position
  Vector<T, N>& center() { return m_center; }

  /// Get center position (by const reference)
  ///
  /// \return Center position
  const Vector<T, N>& center() const { return m_center; }

protected:
  /// Default constructor
  constexpr BoundsCenter()
    : m_center()
  {}

  /// Constructor
  ///
  /// \param[in] center Center position
  constexpr BoundsCenter(const Vector<T, N>& center)
    : m_center(center)
  {}

  Vector<T, N> m_center;
};

/// \class BoundsRadii
/// \brief Boundaries with radii (all of them).
///
/// This class cannot be instantiated directly, it must be inherited.
template<typename T, size_t N>
struct SPATIUMGL_EXPORT BoundsRadii
{
public:
  /// Get radii (by reference)
  ///
  /// \return Radii
  Vector<T, N>& radii() { return m_radii; }

  /// Get radii (by const reference)
  ///
  /// \return Radii
  const Vector<T, N>& radii() const { return m_radii; }

  /// Get diameter for given dimension.
  ///
  /// \param[in] dimension Dimension (should be < N)
  /// \return Diameter
  T diameter(size_t dimension) const { return m_radii[dimension] * 2; }

protected:
  /// Default constructor
  constexpr BoundsRadii()
    : m_radii()
  {}

  /// Constructor
  ///
  /// \param[in] center Center position
  constexpr BoundsRadii(const Vector<T, N>& radii)
    : m_radii(radii)
  {}

  Vector<T, N> m_radii;
};

/// \class BoundsRadii<T,1>
/// \brief Boundaries with 1 radius.
///
/// Examples: circle, square, square, cube, etc.
///
/// This class cannot be instantiated directly, it must be inherited.
template<typename T>
struct SPATIUMGL_EXPORT BoundsRadii<T, 1>
{
public:
  /// Get radius (by reference)
  ///
  /// \return Radius
  T& radius() { return m_radius; }

  /// Get radius (by value)
  ///
  /// \return Radius
  T radius() const { return m_radius; }

  /// Get diameter.
  ///
  /// \return Diameter
  T diameter() const { return m_radius * 2; }

protected:
  /// Default constructor
  constexpr BoundsRadii()
    : m_radius()
  {}

  /// Constructor
  ///
  /// \param[in] center Center position
  constexpr BoundsRadii(T radius)
    : m_radius(radius)
  {}

  T m_radius;
};

/// \class BoundsOrientation
/// \brief Boundaries with orientation
///
/// This class cannot be instantiated directly, it must be inherited.
template<typename T, size_t N>
struct SPATIUMGL_EXPORT BoundsOrientation
{
public:
  /// Get orientation (by reference).
  ///
  /// \return Center orientation
  Vector<T, N>& orientation() { return m_orientation; }

  /// Get orientation (by const reference).
  ///
  /// \return Center orientation
  const Vector<T, N>& orientation() const { return m_orientation; }

protected:
  /// Default constructor
  constexpr BoundsOrientation()
    : m_orientation()
  {}

  /// Constructor
  ///
  /// \param[in] orientation ...n
  constexpr BoundsOrientation(const Vector<T, N>& orientation)
    : m_orientation(orientation)
  {}

  Vector<T, N> m_orientation;
};

/// \class BoundingCircle
/// \brief Minimum bounding circle (2D)
template<typename T>
struct BoundingCircle
  : public BoundsCenter<T, 2>
  , public BoundsRadii<T, 1>
{};

/// \class BoundingEllipse
/// \brief Minimum bounding ellipse (2D)
template<typename T>
struct BoundingEllipse
  : public BoundsCenter<T, 2>
  , public BoundsRadii<T, 2>
{};

/// \class BoundingSquare
/// \brief Minimum bounding square (2D)
template<typename T>
struct BoundingSquare
  : public BoundsCenter<T, 2>
  , public BoundsRadii<T, 1>
{};

/// \class BoundingRectangle
/// \brief Minimum bounding rectangle (2D)
template<typename T>
struct BoundingRectangle
  : public BoundsCenter<T, 2>
  , public BoundsRadii<T, 2>
{};

/// \class OrientedBoundingEllipse
/// \brief Minimum bounding oriented ellipse (2D)
template<typename T>
struct OrientedBoundingEllipse
  : public BoundsCenter<T, 2>
  , public BoundsRadii<T, 2>
  , public BoundsOrientation<T, 2>
{};

/// \class OrientedBoundingSquare
/// \brief Minimum bounding oriented square (2D)
template<typename T>
struct OrientedBoundingSquare
  : public BoundsCenter<T, 2>
  , public BoundsRadii<T, 1>
  , public BoundsOrientation<T, 2>
{};

/// \class OrientedBoundingRectangle
/// \brief Minimum bounding oriented rectangle (2D)
template<typename T>
struct OrientedBoundingRectangle
  : public BoundsCenter<T, 2>
  , public BoundsRadii<T, 2>
  , public BoundsOrientation<T, 2>
{};

/// \class BoundingSphere
/// \brief Minimum bounding sphere (3D)
template<typename T>
struct BoundingSphere
  : public BoundsCenter<T, 3>
  , public BoundsRadii<T, 1>
{};

/// \class BoundingEllipsoid
/// \brief Minimum bounding ellipsoid (3D)
template<typename T>
struct BoundingEllipsoid
  : public BoundsCenter<T, 3>
  , public BoundsRadii<T, 3>
{};

/// \class BoundingCube
/// \brief Minimum bounding cube (3D)
template<typename T>
struct BoundingCube
  : public BoundsCenter<T, 3>
  , public BoundsRadii<T, 1>
{};

/// \class BoundingBox
/// \brief Minimum bounding box (3D)
template<typename T>
struct BoundingBox
  : public BoundsCenter<T, 3>
  , public BoundsRadii<T, 3>
{
  /// Default onstructor
  BoundingBox() = default;

  /// Constructor
  ///
  /// \param[in] center Center position
  /// \param[in] radii Radii for each axis
  BoundingBox(const Vector<T, 3>& center, const Vector<T, 3>& radii)
    : BoundsCenter<T, 3>(center)
    , BoundsRadii<T, 3>(radii)
  {}

  /// Construct from points.
  ///
  /// The bounding box will encapsulate all points.
  ///
  /// \param[in] points Points in N-dimensional space.
  /// \return Bounding box
  static BoundingBox<T> fromPoints(const std::vector<Vector<T, 3>>& points)
  {
    if (points.size() == 0) {
      return {};
    }

    // Set initial bounds
    Vector<T, 3> minVal(points[0][0], points[0][1], points[0][2]);
    Vector<T, 3> maxVal(points[0][0], points[0][1], points[0][2]);

    // Iterate points and update bounds
    for (size_t i = 1; i < points.size(); i++) {
      Vector<T, 3> point = points[i];

      // Update min and max
      for (size_t i = 0; i < 3; i++) {
        if (point[i] < minVal[i]) {
          minVal[i] = point[i];
        } else if (point[i] > maxVal[i]) {
          maxVal[i] = point[i];
        }
      }
    }

    return BoundingBox::fromMinMax(minVal, maxVal);
  }

  /// Construct from minimum and maximum coordinates.
  ///
  /// \param[in] min Minimum coordinates
  /// \param[in] max Maximum coordinates
  /// \return Bounding box
  static BoundingBox fromMinMax(const Vector<T, 3>& min,
                                const Vector<T, 3>& max)
  {
    // Compute center and radii
    Vector<T, 3> center(max[0] / static_cast<T>(2) + min[0] / static_cast<T>(2),
                        max[1] / static_cast<T>(2) + min[1] / static_cast<T>(2),
                        max[2] / static_cast<T>(2) +
                          min[2] / static_cast<T>(2));

    Vector<T, 3> radii(max[0] / static_cast<T>(2) - min[0] / static_cast<T>(2),
                       max[1] / static_cast<T>(2) - min[1] / static_cast<T>(2),
                       max[2] / static_cast<T>(2) - min[2] / static_cast<T>(2));

    return {center, radii};
  }

  // Compare operators

  /// Compare operator. Is equal.
  ///
  /// \param[in] other Other bounding box
  /// \return True if equal, otherwise false
  bool operator==(const BoundingBox<T> &other) const
  {
    if (this->m_center != other.m_center ||
        this->m_radii != other.m_radii) {
      return false;
    } else {
      return true;
    }
  }

  /// Compare operator. Is unequal.
  ///
  /// \param[in] other Other bounding box
  /// \return True if unequal, otherwise false
  bool operator!=(const BoundingBox<T> & other) const
  {
    return !(operator==(other));
  }

  /// Get minimum coordinates.
  ///
  /// \return Minimum coordinates.
  Vector<T, 3> min() const
  {
    return { this->m_center[0] - this->m_radii[0],
             this->m_center[1] - this->m_radii[1],
             this->m_center[2] - this->m_radii[2] };
  }

  /// Get maxmimum coordinates.
  ///
  /// \return Maximum coordinates.
  Vector<T, 3> max() const
  {
    return { this->m_center[0] + this->m_radii[0],
             this->m_center[1] + this->m_radii[1],
             this->m_center[2] + this->m_radii[2] };
  }

  /// Check wheter a point is within the bounding box.
  ///
  /// A point exactly on the boundary is not considered inside.
  ///
  /// \param[in] point Point
  /// \return True if inside, false outside.
  bool isInside(const Vector<T, 3>& point) const
  {
    for (size_t i = 0; i < 3; i++) {
      if (point[i] < this->m_center[i] - this->m_radii[i]) {
        return false;
      } else if (point[i] > this->m_center[i] + this->m_radii[i]) {
        return false;
      }
    }

    return true;
  }

  /// Extend bounding box to include point.
  ///
  /// \param[in] point Point
  void include(const Vector<T, 3>& point)
  {
    // Get min and max values
    Vector<T, 3> minVal = min();
    Vector<T, 3> maxVal = max();

    // Update min and max
    for (size_t i = 0; i < 3; i++) {
      if (point[i] < minVal[i]) {
        minVal[i] = point[i];
      } else if (point[i] > maxVal[i]) {
        maxVal[i] = point[i];
      }
    }

    // Construct new box
    const auto box = BoundingBox<T>::fromMinMax(minVal, maxVal);

    // Update values
    this->m_center = box.center();
    this->m_radii = box.radii();
  }

  /// Extend bounding box to include other bounding box.
  ///
  /// \param[in] bounds Bounding box
  void include(const BoundingBox& bounds)
  {
    // Get min and max values
    Vector<T, 3> minVal = min();
    Vector<T, 3> maxVal = max();

    // Get min and max of other bounding box
    const Vector<T, 3> otherMinVal = bounds.min();
    const Vector<T, 3> otherMaxVal = bounds.max();

    // Update min and max
    for (size_t i = 0; i < 3; i++) {
      if (otherMinVal[i] < minVal[i]) {
        minVal[i] = otherMinVal[i];
      } else if (otherMaxVal[i] > maxVal[i]) {
        maxVal[i] = otherMaxVal[i];
      }
    }

    // Construct new box
    const auto box = BoundingBox<T>::fromMinMax(minVal, maxVal);

    // Update values
    this->m_center = box.center();
    this->m_radii = box.radii();
  }

  /// Output to ostream
  friend std::ostream& operator<<(std::ostream& os, const BoundingBox& bounds)
  {
    os << "(" << bounds.min() << ", " << bounds.max() << ")";
    return os;
  }
};

/// \class OrientedBoundingEllipsoid
/// \brief Minimum bounding oriented ellipsoid (3D)
template<typename T>
struct OrientedBoundingEllipsoid
  : public BoundsCenter<T, 3>
  , public BoundsRadii<T, 3>
  , public BoundsOrientation<T, 3>
{};

/// \class OrientedBoundingCube
/// \brief Minimum bounding oriented cube (3D)
template<typename T>
struct OrientedBoundingCube
  : public BoundsCenter<T, 3>
  , public BoundsRadii<T, 1>
  , public BoundsOrientation<T, 3>
{};

/// \class OrientedBoundingBox
/// \brief Minimum bounding oriented box (3D)
template<typename T>
struct OrientedBoundingBox
  : public BoundsCenter<T, 3>
  , public BoundsRadii<T, 3>
  , public BoundsOrientation<T, 3>
{};

} // namespace spgl

#endif // SPATIUMGL_GFX3D_BOUNDS_H
