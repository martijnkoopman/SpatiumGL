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

#include "spatiumgl/PivotInteractor.hpp"
#include "spatiumgl/RenderWindow.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace spatiumgl {

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

			std::array<int, 2> framebufferSize = m_window->framebufferSize();
			Camera* camera = m_window->camera();
			if (framebufferSize[0] > 0 && framebufferSize[1] > 0 && camera != nullptr)
			{
				// Get rotation angles
				float angleX = deltaX * glm::pi<float>() / framebufferSize[0];
				float angleY = deltaY * glm::pi<float>() / framebufferSize[1];

				// Rotate
				glm::mat4 rotationX = glm::rotate(angleX, camera->transform().up());
				camera->transform().setMatrix(rotationX * camera->transform().matrix());
				glm::mat4 rotationY = glm::rotate(angleY, camera->transform().right());
				camera->transform().setMatrix(rotationY * camera->transform().matrix());
				//m_camera->orthogonalizeViewUp();
			}
		}
	}

} // namespace spatiumgl