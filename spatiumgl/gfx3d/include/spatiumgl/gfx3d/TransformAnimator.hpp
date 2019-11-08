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

#ifndef SPATIUMGL_GFX3D_TRANSFORMANIMATOR_H
#define SPATIUMGL_GFX3D_TRANSFORMANIMATOR_H

#include "spatiumglexport.hpp"
#include "Animator.hpp"

namespace spatiumgl {
	namespace gfx3d {

		class SPATIUMGL_EXPORT TransformAnimator : public Animator
		{
		public:
			/// Constructor
			///
			/// \param[in] renderObject Render object to rotate
			/// \param[in] axis Axis to rotate around
			/// \param[in] speed Rotation speed (radians/second)
			/// \param[in] local Indicator to rotate around local origin (default=false)
			TransformAnimator(RenderObject* renderObject, const Vector3& axis, const double speed, const bool local=false);

			/// Destructor
			virtual ~TransformAnimator() override = default;

			void animate(double deltaTime) override;

		protected:
			Vector3 m_axis;
			double m_speed;
			bool m_local;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_TRANSFORMANIMATOR_H
