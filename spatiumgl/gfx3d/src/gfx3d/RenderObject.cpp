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

#include "spatiumgl/gfx3d/RenderObject.hpp"

namespace spatiumgl {
	namespace gfx3d {

		RenderObject::RenderObject()
			: SceneObject()
			, m_bounds()
		{}

    BoundingBox<double> RenderObject::bounds() const
		{
			return m_bounds;
		}

	} // namespace gfx3d
} // namespace spatiumgl
