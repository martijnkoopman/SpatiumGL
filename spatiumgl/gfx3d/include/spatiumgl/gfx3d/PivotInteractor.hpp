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

#ifndef SPATIUMGL_PIVOTINTERACTOR_H
#define SPATIUMGL_PIVOTINTERACTOR_H

#include "spatiumglexport.hpp"
#include "RenderWindowInteractor.hpp"

namespace spatiumgl {
	class SPATIUMGL_EXPORT PivotInteractor : public RenderWindowInteractor
	{
	public:
		PivotInteractor(RenderWindow* window);
		virtual void OnMousePressed(MouseButton button, double x, double y) override;
		virtual void OnMouseReleased(MouseButton button, double x, double y) override;
		virtual void OnMouseMoved(double deltaX, double deltaY) override;

	protected:
		bool m_pressed;
	};

} // namespace spatiumgl

#endif // SPATIUMGL_PIVOTINTERACTOR_H