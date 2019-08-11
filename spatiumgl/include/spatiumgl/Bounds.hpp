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

#ifndef SPATIUMGL_BOUNDS_H
#define SPATIUMGL_BOUNDS_H

#include "Vector.hpp"

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
		BoundsT(const VectorT<T, N>& center)
			: m_center(center)
		{
		}

		VectorT<T, N> center() const
		{
			return m_center;
		}

	protected:
		VectorT<T, N> m_center;
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
		BoundingBoxT(const VectorT<T, N>& center, const VectorT<T, N>& radii)
			: BoundsT<T, N>(center)
			, m_radii(radii)
		{
		}

		/// Build from points
		///
		/// \param[in] points Points in N-dimensional space.
		static BoundingBoxT<T, N> fromPoints(const std::vector<VectorT<T, N>>& points)
		{
			if (points.size() == 0)
			{
				return BoundingBoxT();
			}

			// Set initial bounds
			VectorT<T, N> minVal, maxVal;
			for (size_t i = 0; i < N; i++)
			{
				minVal[i] = maxVal[i] = points[0][i];
			}

			// Iterate points and update bounds
			for (size_t i = 1; i < points.size(); i++)
			{
				VectorT<T, N> point = points[i];

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

		static BoundingBoxT<T, N> fromMinMax(const VectorT<T, N>& min, const VectorT<T, N>& max)
		{
			// Compute center and radii
			VectorT<T, N> centerVal, radiiVal;
			for (size_t i = 0; i < N; i++)
			{
				centerVal[i] = max[i] * 0.5 + min[i] * 0.5;
				radiiVal[i] = max[i] * 0.5 - min[i] * 0.5;
			}

			return BoundingBoxT(centerVal, radiiVal);
		}

		bool isInside(const VectorT<T, N>& point) const
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

		VectorT<T, N> min() const
		{
			VectorT<T, N> res;
			for (size_t i = 0; i < N; i++)
			{
				res[i] = this->m_center[i] - m_radii[i];
			}
			return res;
		}

		VectorT<T, N> max() const
		{
			VectorT<T, N> res;
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
		VectorT<T, N> m_radii;
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
		VectorT<T, N> m_orientation;
	};

	using OrientedBoundingBox = OrientedBoundingBoxT<SPATIUMGL_PRECISION, size_t(3)>;
	using OrientedBoundingRectangle = OrientedBoundingBoxT<SPATIUMGL_PRECISION, size_t(2)>;

} // namespace spatium

#endif // SPATIUMGL_BOUNDS_H