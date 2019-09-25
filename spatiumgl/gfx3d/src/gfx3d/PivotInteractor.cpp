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

#include <iostream>

namespace spatiumgl {
	namespace gfx3d {

		PivotInteractor::PivotInteractor(RenderWindow* window)
			: RenderWindowInteractor(window)
			, m_pressed(false)
			, m_pivotPoint()
		{
		}

		void PivotInteractor::setPivotPoint(const Vector3& pivotPoint)
		{
			m_pivotPoint = pivotPoint;
		}

		Vector3 PivotInteractor::pivotPoint() const
		{
			return m_pivotPoint;
		}

		void PivotInteractor::OnMouseButtonPressed(MouseButton button, double x, double y)
		{
			if (button == MouseButton::MOUSE_BUTTON_LEFT)
			{
				m_pressed = true;
			}
		}

		void PivotInteractor::OnMouseButtonReleased(MouseButton button, double x, double y)
		{
			if (button == MouseButton::MOUSE_BUTTON_LEFT)
			{
				m_pressed = false;
			}
		}

		void PivotInteractor::OnMouseWheelScrolled(double scroll)
		{
			Camera* camera = m_window->camera();
			if (camera != nullptr)
			{
				Vector3 directionOfProjection = camera->transform().translation() - m_pivotPoint;
				Vector3 translation = directionOfProjection / (scroll * 2);

				std::cout << "Pivot: " << m_pivotPoint << std::endl;
				std::cout << "Camera: " << camera->transform().translation() << std::endl;
				std::cout << "Vector: " << directionOfProjection << std::endl;
				std::cout << "Scroll: " << scroll << std::endl;
				std::cout << "Translation: " << translation << std::endl;

				camera->transform().applyTranslation(translation);
			}
		}

		void PivotInteractor::OnMouseMoved(double deltaX, double deltaY)
		{
			if (m_pressed)
			{
				std::cout << deltaX << " " << deltaY << std::endl;

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
					//spatiumgl::Matrix4 rotationX = spatiumgl::Matrix4::rotation(angleX, camera->transform().up());
					//camera->transform().setMatrix(rotationX * camera->transform().matrix());
					//spatiumgl::Matrix4 rotationY = spatiumgl::Matrix4::rotation(angleY, camera->transform().right());
					//camera->transform().setMatrix(rotationY * camera->transform().matrix());
					////m_camera->orthogonalizeViewUp();
				}
			}
		}

	} // namespace gfx3d
} // namespace spatiumgl