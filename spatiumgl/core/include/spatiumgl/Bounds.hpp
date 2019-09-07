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

namespace spatiumgl {

	template<typename T, size_t N>
	struct SPATIUMGL_EXPORT BoundsCenter
	{
	public:
		/// Get center position (by reference)
		///
		/// \return Center position
		Vector<T, N>& center()
		{
			return m_center;
		}

		/// Get center position (by const reference)
		///
		/// \return Center position
		const Vector<T, N>& center() const
		{
			return m_center;
		}

	protected:
		/// Default constructor
		constexpr BoundsCenter()
			: m_center()
		{
		}

		/// Constructor
		///
		/// \param[in] center Center position
		constexpr BoundsCenter(const Vector<T, N>& center)
			: m_center(center)
		{
		}

		Vector<T, N> m_center;
	};

	template<typename T, size_t N>
	struct SPATIUMGL_EXPORT BoundsRadii
	{
	public:
		/// Get radii (by reference)
		///
		/// \return Radii
		Vector<T, N>& radii() 
		{
			return m_radii;
		}

		/// Get radii (by const reference)
		///
		/// \return Radii
		const Vector<T, N>& radii() const
		{
			return m_radii;
		}

		/// Get diameter for given dimension.
		///
		/// \param[in] dimension Dimension (should be < N)
		/// \return Diameter
		T diameter(size_t dimension) const
		{
			return m_radii[dimension] * 2;
		}

	protected:
		/// Default constructor
		constexpr BoundsRadii()
			: m_radii()
		{
		}

		/// Constructor
		///
		/// \param[in] center Center position
		constexpr BoundsRadii(const Vector<T, N>& radii)
			: m_radii(radii)
		{
		}

		Vector<T, N> m_radii;
	};

	template<typename T>
	struct SPATIUMGL_EXPORT BoundsRadii<T,1>
	{
	public:
		/// Get radius (by reference)
		///
		/// \return Radius
		T& radius()
		{
			return m_radius;
		}

		/// Get radius (by value)
		///
		/// \return Radius
		T radius() const
		{
			return m_radius;
		}

		/// Get diameter.
		///
		/// \return Diameter
		T diameter() const
		{
			return m_radius * 2;
		}

	protected:
		/// Default constructor
		constexpr BoundsRadii()
			: m_radius()
		{
		}

		/// Constructor
		///
		/// \param[in] center Center position
		constexpr BoundsRadii(T radius)
			: m_radius(radius)
		{
		}

		T m_radius;
	};

	template<typename T, size_t N>
	struct SPATIUMGL_EXPORT BoundsOrientation
	{
	public:
		/// Get orientation (by reference).
		///
		/// \return Center orientation
		Vector<T, N>& orientation()
		{
			return m_orientation;
		}

		/// Get orientation (by const reference).
		///
		/// \return Center orientation
		const Vector<T, N>& orientation() const
		{
			return m_orientation;
		}

	protected:
		/// Default constructor
		constexpr BoundsOrientation()
			: m_orientation()
		{
		}

		/// Constructor
		///
		/// \param[in] orientation ...n
		constexpr BoundsOrientation(const Vector<T, N>& orientation)
			: m_orientation(orientation)
		{
		}

		Vector<T, N> m_orientation;
	};

	/*
	/// \class Bounds
	/// \brief Boundaries in N-dimensional space.
	template<typename T, size_t N>
	struct SPATIUMGL_EXPORT Bounds : public BoundsBase<T, N>
	{
		/// Default constructor
		constexpr Bounds() = default;

	protected:
		Vector<T, N> m_radii;
	};

	/// \class BoundingBox
	/// \brief Axis-aligned bounding box (AABB) in N-dimensional space.
	template<typename T, size_t N>
	struct SPATIUMGL_EXPORT BoundingBoxT : public BoundsBase<T, N>
	{
	public:
		/// Default onstructor
		BoundingBoxT()
			: BoundsBase<T, N>()
			, m_radii()
		{
		}

		/// Constructor
		///
		/// \param[in] center Center position
		/// \param[in] radii Radii for each axis
		BoundingBoxT(const Vector<T, N>& center, const Vector<T, N>& radii)
			: BoundsBase<T, N>(center)
			, m_radii(radii)
		{
		}

		/// Build from points
		///
		/// \param[in] points Points in N-dimensional space.
		static BoundingBoxT<T, N> fromPoints(const std::vector<Vector<T, N>>& points)
		{
			if (points.size() == 0)
			{
				return BoundingBoxT();
			}

			// Set initial bounds
			Vector<T, N> minVal, maxVal;
			for (size_t i = 0; i < N; i++)
			{
				minVal[i] = maxVal[i] = points[0][i];
			}

			// Iterate points and update bounds
			for (size_t i = 1; i < points.size(); i++)
			{
				Vector<T, N> point = points[i];

				// Iterate dimensions
				for (size_t i = 0; i < N; i++)
				{
					if (point[i] < minVal[i]) {
						minVal[i] = point[i];
					}
					else if (point[i] > maxVal[i]) {
						maxVal[i] = point[i];
					}
				}
			}

			return BoundingBoxT<T, N>::fromMinMax(minVal, maxVal);
		}

		static BoundingBoxT<T, N> fromMinMax(const Vector<T, N>& min, const Vector<T, N>& max)
		{
			// Compute center and radii
			Vector<T, N> centerVal, radiiVal;
			for (size_t i = 0; i < N; i++)
			{
				centerVal[i] = max[i] * 0.5 + min[i] * 0.5;
				radiiVal[i] = max[i] * 0.5 - min[i] * 0.5;
			}

			return BoundingBoxT(centerVal, radiiVal);
		}

		bool isInside(const Vector<T, N>& point) const
		{
			for (size_t i = 0; i < N; i++)
			{
				if (point[i] < this->m_center[i] - m_radii[i])
				{
					return false;
				}
				else if (point[i] > this->m_center[i] + m_radii[i])
				{
					return false;
				}
			}

			return true;
		}

		Vector<T, N> min() const
		{
			Vector<T, N> res;
			for (size_t i = 0; i < N; i++)
			{
				res[i] = this->m_center[i] - m_radii[i];
			}
			return res;
		}

		Vector<T, N> max() const
		{
			Vector<T, N> res;
			for (size_t i = 0; i < N; i++)
			{
				res[i] = this->m_center[i] + m_radii[i];
			}
			return res;
		}



		/// Output to ostream
		friend std::ostream& operator<<(std::ostream& os, const BoundingBoxT<T, N>& bounds)
		{
			os << "(" << bounds.min() << ", " << bounds.max() << ")";
			return os;
		}

	protected:
		Vector<T, N> m_radii;
	};

	using BoundingBox = BoundingBoxT<SPATIUMGL_PRECISION, size_t(3)>;
	using BoundingRectangle = BoundingBoxT<SPATIUMGL_PRECISION, size_t(2)>;

	/// \class OrientedBoundingBox
	/// \brief Oriented bounding box in N-dimensional space.
	template<typename T, size_t N>
	struct SPATIUMGL_EXPORT OrientedBoundingBoxT : BoundingBoxT<T, N>
	{
	public:

	protected:
		Vector<T, N> m_orientation;
	};

	using OrientedBoundingBox = OrientedBoundingBoxT<SPATIUMGL_PRECISION, size_t(3)>;
	using OrientedBoundingRectangle = OrientedBoundingBoxT<SPATIUMGL_PRECISION, size_t(2)>;
	*/

	template<typename T>
	struct BoundingCircle : public BoundsCenter<T, 2>, public BoundsRadii<T, 1>
	{};

	template<typename T>
	struct BoundingEllipse : public BoundsCenter<T, 2>, public BoundsRadii<T, 2>
	{};

	template<typename T>
	struct BoundingSquare : public BoundsCenter<T, 2>, public BoundsRadii<T, 1>
	{};

	template<typename T>
	struct BoundingRectangle : public BoundsCenter<T, 2>, public BoundsRadii<T, 2>
	{};

	template<typename T>
	struct OrientedBoundingEllipse : public BoundsCenter<T, 2>, public BoundsRadii<T, 2>, public BoundsOrientation<T, 2>
	{};

	template<typename T>
	struct OrientedBoundingSquare : public BoundsCenter<T, 2>, public BoundsRadii<T, 1>, public BoundsOrientation<T, 2>
	{};

	template<typename T>
	struct OrientedBoundingRectangle : public BoundsCenter<T, 2>, public BoundsRadii<T, 2>, public BoundsOrientation<T, 2>
	{};

	template<typename T>
	struct BoundingSphere : public BoundsCenter<T, 3>, public BoundsRadii<T, 1>
	{};

	template<typename T>
	struct BoundingEllipsoid : public BoundsCenter<T, 3>, public BoundsRadii<T, 3>
	{};

	template<typename T>
	struct BoundingCube : public BoundsCenter<T, 3>, public BoundsRadii<T, 1>
	{};

	template<typename T>
	struct BoundingBox : public BoundsCenter<T, 3>, public BoundsRadii<T, 3>
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
		{
		}

		/// Build from points
		///
		/// \param[in] points Points in N-dimensional space.
		/// \return Bounding box
		static BoundingBox fromPoints(const std::vector<Vector<T, 3>>& points)
		{
			if (points.size() == 0)
			{
				return BoundingBox();
			}

			// Set initial bounds
			Vector<T, 3> minVal(points[0][0], points[0][1], points[0][2]);
			Vector<T, 3> maxVal(points[0][0], points[0][1], points[0][2]);

			// Iterate points and update bounds
			for (size_t i = 1; i < points.size(); i++)
			{
				Vector<T, 3> point = points[i];

				// Update min and max
				for (size_t i = 0; i < 3; i++)
				{
					if (point[i] < minVal[i]) {
						minVal[i] = point[i];
					}
					else if (point[i] > maxVal[i]) {
						maxVal[i] = point[i];
					}
				}
			}

			return BoundingBox::fromMinMax(minVal, maxVal);
		}

		static BoundingBox fromMinMax(const Vector<T, 3>& min, const Vector<T, 3>& max)
		{
			// Compute center and radii
			Vector<T, 3> center(
				max[0] * 0.5 + min[0] * 0.5,
				max[1] * 0.5 + min[1] * 0.5,
				max[2] * 0.5 + min[2] * 0.5
			);
			
			Vector<T, 3> radii(
				max[0] * 0.5 - min[0] * 0.5,
				max[1] * 0.5 - min[1] * 0.5,
				max[2] * 0.5 - min[2] * 0.5);

			return BoundingBox(center, radii);
		}

		Vector<T, 3> min() const
		{
      return Vector<T, 3>(this->m_center[0] - this->m_radii[0],
        this->m_center[1] - this->m_radii[1],
        this->m_center[2] - this->m_radii[2]);
		}

		Vector<T, 3> max() const
		{
      return Vector<T, 3>(this->m_center[0] + this->m_radii[0],
        this->m_center[1] + this->m_radii[1],
        this->m_center[2] + this->m_radii[2]);
		}

		bool isInside(const Vector<T, 3>& point) const
		{
			for (size_t i = 0; i < 3; i++)
			{
        if (point[i] < this->m_center[i] - this->m_radii[i])
				{
					return false;
				}
        else if (point[i] > this->m_center[i] + this->m_radii[i])
				{
					return false;
				}
			}

			return true;
		}

		void include(const Vector<T, 3> & point)
		{
			Vector3 minVal = min();
			Vector3 maxVal = max();

			// Update min and max
			for (size_t i = 0; i < 3; i++)
			{
				if (point[i] < minVal[i]) {
					minVal[i] = point[i];
				}
				else if (point[i] > maxVal[i]) {
					maxVal[i] = point[i];
				}
			}

			const auto box = BoundingBox<T>::fromMinMax(minVal, maxVal);
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

	template<typename T>
	struct OrientedBoundingEllipsoid : public BoundsCenter<T, 3>, public BoundsRadii<T, 3>, public BoundsOrientation<T, 3>
	{};

	template<typename T>
	struct OrientedBoundingCube : public BoundsCenter<T, 3>, public BoundsRadii<T, 1>, public BoundsOrientation<T, 3>
	{};

	template<typename T>
	struct OrientedBoundingBox : public BoundsCenter<T, 3>, public BoundsRadii<T, 3>, public BoundsOrientation<T, 3>
	{};

} // namespace spatium

#endif // SPATIUMGL_GFX3D_BOUNDS_H