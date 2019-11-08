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
#include "spatiumgl/Vector3.hpp"

namespace spatiumgl {
	namespace gfx3d {
		class SPATIUMGL_EXPORT PivotInteractor : public RenderWindowInteractor
		{
		public:
			PivotInteractor(RenderWindow* window);

			/// Set the pivot point.
			///
			/// This is the point around which the view rotates.
			///
			/// \param[in] pivotPoint Pivot point
			void setPivotPoint(const Vector3& pivotPoint);

			/// Get pivot point.
			///
			/// \return Pivot point
			Vector3 pivotPoint() const;

			virtual void OnMouseButtonPressed(MouseButton button, double x, double y) override;
			virtual void OnMouseButtonReleased(MouseButton button, double x, double y) override;
			virtual void OnMouseWheelScrolled(double scroll) override;
			virtual void OnMouseMoved(double deltaX, double deltaY) override;

			virtual void resetCamera() override;
			virtual void resetCameraClipping() override;

		protected:
			bool m_pressed;
			Vector3 m_pivotPoint;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_PIVOTINTERACTOR_H