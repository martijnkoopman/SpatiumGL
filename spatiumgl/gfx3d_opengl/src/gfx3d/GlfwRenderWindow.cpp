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

#include "spatiumgl/gfx3d/GlfwRenderWindow.hpp" 
#include "GlfwRenderWindowImpl.hpp"

namespace spatiumgl {
	namespace gfx3d {
		GlfwRenderWindow::GlfwRenderWindow(bool debug)
			: RenderWindow(debug)
			, m_pimpl(new GlfwRenderWindowImpl(this, debug))
		{
		}

		// Destructor body must be defined in CPP file because otherwise type 
		// GlfwRenderWindowImpl is incomplete and cannot be deleted.
		GlfwRenderWindow::~GlfwRenderWindow()
		{
		}

		bool GlfwRenderWindow::init()
		{
			return m_pimpl->init();
		}

		bool GlfwRenderWindow::createWindow(int width, int height)
		{
			return m_pimpl->createWindow(width, height);
		}

		void GlfwRenderWindow::destroyWindow()
		{
			m_pimpl->destroyWindow();
		}

		void GlfwRenderWindow::terminate() const
		{
			m_pimpl->terminate();
		}

		void GlfwRenderWindow::show()
		{
			m_pimpl->show();
		}
	} // namespace gfx3d
} // namespace spatiumgl
