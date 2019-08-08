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

#ifndef SPATIUMGL_GEOMETRY_H
#define SPATIUMGL_GEOMETRY_H

#include "Bounds.hpp"

namespace spatiumgl {
	namespace idx {

		///\class Geometry
		///\brief Geometry in D-dimensional space.
		///
		/// A geometry always has some kind of bounding volume. A single point is not
		/// considered geometry.
		template<typename T, size_t D>
		class Geometry
		{
			Bounds<T, D> bounds() const
			{
				return m_bounds;
			}

		protected:
			Bounds<T, D> m_bounds;
		};

	} // namespace idx
} // namespace spatiumgl

#endif // SPATIUMGL_GEOMETRY_H