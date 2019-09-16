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

#ifndef SPATIUMGL_GFX3D_PIVOTINTERACTOR_H
#define SPATIUMGL_GFX3D_PIVOTINTERACTOR_H

#include "spatiumglexport.hpp"
#include "RenderWindowInteractor.hpp"

namespace spatiumgl {
	namespace gfx3d {
		class SPATIUMGL_EXPORT PivotInteractor : public RenderWindowInteractor
		{
		public:
			PivotInteractor(RenderWindow* window);
      virtual ~PivotInteractor() override = default;
			virtual void OnMousePressed(MouseButton button, double x, double y) override;
			virtual void OnMouseReleased(MouseButton button, double x, double y) override;
			virtual void OnMouseMoved(double deltaX, double deltaY) override;

		protected:
			bool m_pressed;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_PIVOTINTERACTOR_H
