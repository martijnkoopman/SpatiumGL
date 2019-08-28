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

#include "spatiumgl/gfx3d/RenderWindow.hpp"

namespace spatiumgl {

	RenderWindow::RenderWindow(bool debug)
		: m_interactor(new PivotInteractor(this))
		, m_camera(nullptr)
		, m_renderer(nullptr)
		, m_framebufferSize{ 0, 0 }
		, m_debug(debug)
	{}

	RenderWindow::~RenderWindow()
	{
		delete m_interactor;
	}
	
	void RenderWindow::setInteractor(RenderWindowInteractor* interactor)
	{
		m_interactor = interactor;
	}

	RenderWindowInteractor* RenderWindow::interactor() const
	{
		return m_interactor;
	}

	void RenderWindow::setCamera(Camera* camera)
	{
		m_camera = camera;
	}

	Camera* RenderWindow::camera() const
	{
		return m_camera;
	}

	void RenderWindow::setRenderer(Renderer* renderer)
	{
		m_renderer = renderer;
	}

	Vector2i RenderWindow::framebufferSize() const
	{
		return m_framebufferSize;
	}

} // namespace spatiumgl
