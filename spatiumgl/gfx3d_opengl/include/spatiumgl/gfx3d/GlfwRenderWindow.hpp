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

#ifndef SPATIUMGL_GFX3D_GLFWRENDERWINDOW_H
#define SPATIUMGL_GFX3D_GLFWRENDERWINDOW_H

#include "spatiumglexport.hpp"
#include "spatiumgl/gfx3d/RenderWindow.hpp"

#include <memory> // std::unique_ptr

namespace spatiumgl {
	namespace gfx3d {
		/// \class GlfwRenderWindow
		/// \brief GLFW implementation of RenderWindow
		class SPATIUMGL_EXPORT GlfwRenderWindow : public RenderWindow
		{
		public:
      /// Constructor
			GlfwRenderWindow(bool debug = false);

      /// Destructor
      virtual ~GlfwRenderWindow() override = default;

			bool init() override;
			bool createWindow(int width, int height) override;
			void destroyWindow() override;
			void terminate() const override;
			void show() override;

		private:
			class impl;
			std::unique_ptr<impl> m_pimpl;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_GLFWRENDERWINDOW_H
