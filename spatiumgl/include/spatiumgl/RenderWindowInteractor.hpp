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

#ifndef SPATIUMGL_RENDERWINDOWINTERACTOR_H
#define SPATIUMGL_RENDERWINDOWINTERACTOR_H

#include "spatiumglexport.hpp"

namespace spatiumgl {

	// Forward declare
	class RenderWindow;

	class SPATIUMGL_EXPORT RenderWindowInteractor
	{
	public:
		enum MouseButton
		{
			MOUSE_BUTTON_LEFT,
			MOUSE_BUTTON_MIDDLE,
			MOUSE_BUTTON_RIGHT
		};

		/// Constructor
		///
		/// \param[in] window Render window
		RenderWindowInteractor(RenderWindow* window)
			: m_window(window)
		{}

		virtual void OnMousePressed(MouseButton button, double x, double y) = 0;
		virtual void OnMouseReleased(MouseButton button, double x, double y) = 0;
		virtual void OnMouseMoved(double deltaX, double deltaY) = 0;

	protected:
		RenderWindow* m_window;
	};

} // namespace spatiumgl

#endif // SPATIUMGL_RENDERWINDOWINTERACTOR_H