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

#include "spatiumgl/gfx3d/OrthographicCamera.hpp"

namespace spatiumgl {
	namespace gfx3d {
		OrthographicCamera::OrthographicCamera(double size, double near, double far)
			: Camera(near, far)
			, m_size(size)
		{
		}

		void OrthographicCamera::setSize(double size)
		{
			m_size = size;
		}

		double OrthographicCamera::size() const
		{
			return m_size;
		}

		Matrix4 OrthographicCamera::projectionMatrix(double aspect) const
		{
			return Matrix4::ortho(m_size, aspect, m_near, m_far);
		}

	} // namespace gfx3d
} // namespace spatiumgl