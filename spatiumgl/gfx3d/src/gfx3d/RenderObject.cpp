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

	RenderObject::RenderObject()
		: SceneObject()
		, m_bounds()
	{}

	BoundingBox<SPATIUMGL_PRECISION> RenderObject::bounds() const
	{
		return m_bounds;
	}

} // namespace spatiumgl
