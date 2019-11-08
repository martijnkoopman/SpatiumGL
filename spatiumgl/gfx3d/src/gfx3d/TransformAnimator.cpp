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

#include "spatiumgl/gfx3d/TransformAnimator.hpp"

#include <iostream>

namespace spatiumgl {
	namespace gfx3d {

		TransformAnimator::TransformAnimator(RenderObject* renderObject, const Vector3& axis, const double speed, const bool local)
			: Animator(renderObject)
			, m_axis(axis)
			, m_speed(speed)
			, m_local(local)
		{
		}

		void TransformAnimator::animate(double deltaTime)
		{
			double angle = deltaTime; // TODO. Incorporate speed
			m_renderObject->transform().rotateAround(m_axis, angle);
			// TODO: Local rotation
		}

	} // namespace gfx3d
} // namespace spatiumgl
