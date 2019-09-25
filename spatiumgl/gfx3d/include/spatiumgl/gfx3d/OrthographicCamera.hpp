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

#ifndef SPATIUMGL_GFX3D_ORTHOGRAPHICCAMERA_H
#define SPATIUMGL_GFX3D_ORTHOGRAPHICCAMERA_H

#include "spatiumglexport.hpp"
#include "Camera.hpp"

namespace spatiumgl {
	namespace gfx3d {

		class SPATIUMGL_EXPORT OrthographicCamera : public Camera
		{
		public:
			/// Constructor
			///
			/// \param[in] size Orthographic size
			/// \param[in] near Distance to near clipping plane
			/// \param[in] far Distance to far clipping plane
			OrthographicCamera(double size, double near, double far);

			/// Destructor
			~OrthographicCamera() override = default;

			void setSize(double size);

			double size() const;

			/// Get the orthographic projection matrix.
			///
			/// \param[in] aspect Aspect ratio (w/h)
			/// \return Orthographic projection matrix
			Matrix4 projectionMatrix(double aspect) const override;

		protected:
			double m_size;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_ORTHOGRAPHICCAMERA_H