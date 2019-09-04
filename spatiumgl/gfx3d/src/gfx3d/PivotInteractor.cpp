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

#include "spatiumgl/gfx3d/PivotInteractor.hpp"
#include "spatiumgl/gfx3d/RenderWindow.hpp"

namespace spatiumgl {
	namespace gfx3d {

		PivotInteractor::PivotInteractor(RenderWindow* window)
			: RenderWindowInteractor(window)
			, m_pressed(false)
		{

		}

		void PivotInteractor::OnMousePressed(MouseButton button, double x, double y)
		{
			if (button == MouseButton::MOUSE_BUTTON_LEFT)
			{
				m_pressed = true;
			}
		}

		void PivotInteractor::OnMouseReleased(MouseButton button, double x, double y)
		{
			if (button == MouseButton::MOUSE_BUTTON_LEFT)
			{
				m_pressed = false;
			}
		}

		void PivotInteractor::OnMouseMoved(double deltaX, double deltaY)
		{
			if (m_pressed)
			{
				// Get viewport size
				//int viewport[4];
				//glGetIntegerv(GL_VIEWPORT, viewport);

				Vector2i framebufferSize = m_window->framebufferSize();
				Camera* camera = m_window->camera();
				if (framebufferSize[0] > 0 && framebufferSize[1] > 0 && camera != nullptr)
				{
					//// Get rotation angles
					//float angleX = deltaX * spatiumgl::pi<float>() / framebufferSize[0];
					//float angleY = deltaY * spatiumgl::pi<float>() / framebufferSize[1];

					//// Rotate
					//spatiumgl::Matrix4x4 rotationX = spatiumgl::Matrix4x4::rotation(angleX, camera->transform().up());
					//camera->transform().setMatrix(rotationX * camera->transform().matrix());
					//spatiumgl::Matrix4x4 rotationY = spatiumgl::Matrix4x4::rotation(angleY, camera->transform().right());
					//camera->transform().setMatrix(rotationY * camera->transform().matrix());
					////m_camera->orthogonalizeViewUp();
				}
			}
		}

	} // namespace gfx3d
} // namespace spatiumgl