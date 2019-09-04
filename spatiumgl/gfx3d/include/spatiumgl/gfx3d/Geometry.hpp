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

#ifndef SPATIUMGL_GFX3D_GEOMETRY_H
#define SPATIUMGL_GFX3D_GEOMETRY_H

#include "spatiumgl/Bounds.hpp"

namespace spatiumgl {
	namespace gfx3d {

		///\class Geometry
		///\brief Geometry in D-dimensional space.
		///
		/// A geometry always has some kind of bounding volume. A single point is not
		/// considered geometry.
		template<typename T, size_t N>
		class Geometry
		{
			BoundsT<T, D> bounds() const
			{
				return m_bounds;
			}

		protected:
			BoundsT<T, D> m_bounds;
		};
	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_GEOMETRY_H