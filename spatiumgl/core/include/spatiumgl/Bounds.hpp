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

	/// \class Bounds
	/// \brief Boundaries in N-dimensional space.
	template<typename T, size_t N>
	class BoundsT
	{
	public:
		/// Default constructor
		BoundsT()
			: m_center()
		{
		}

		/// Constructor
		BoundsT(const Vector<T, N>& center)
			: m_center(center)
		{
		}

		Vector<T, N> center() const
		{
			return m_center;
		}

	protected:
		Vector<T, N> m_center;
	};

	/// \class BoundingBox
	/// \brief Axis-aligned bounding box (AABB) in N-dimensional space.
	template<typename T, size_t N>
	class BoundingBoxT : public BoundsT<T, N>
	{
	public:
		/// Default onstructor
		BoundingBoxT()
			: BoundsT<T, N>()
			, m_radii()
		{
		}

		/// Constructor
		BoundingBoxT(const Vector<T, N>& center, const Vector<T, N>& radii)
			: BoundsT<T, N>(center)
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

		T diameter(size_t dimension) const
		{
			return m_radii[dimension] * 2;
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
	class OrientedBoundingBoxT : BoundingBoxT<T, N>
	{
	public:

	protected:
		Vector<T, N> m_orientation;
	};

	using OrientedBoundingBox = OrientedBoundingBoxT<SPATIUMGL_PRECISION, size_t(3)>;
	using OrientedBoundingRectangle = OrientedBoundingBoxT<SPATIUMGL_PRECISION, size_t(2)>;

} // namespace spatium

#endif // SPATIUMGL_GFX3D_BOUNDS_H