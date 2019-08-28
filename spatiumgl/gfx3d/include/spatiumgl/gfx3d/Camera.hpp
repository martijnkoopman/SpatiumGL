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

#ifndef SPATIUMGL_CAMERA_H
#define SPATIUMGL_CAMERA_H

#include "spatiumglexport.hpp"
#include "SceneObject.hpp"

namespace spatiumgl {

	class SPATIUMGL_EXPORT Camera : public SceneObject
	{
	public:
		Camera(float fov, float near, float far);

		/// Destructor
		virtual ~Camera() = default;

		float fov() const;

		/// Get the distance to the near clipping plane in world space.
		///
		/// \return Near clipping plane distance.
		float near() const;

		/// Get the distance to the far clipping plane in world space.
		///
		/// \return Far clipping plane distance.
		float far() const;

		/// Set view direction towards target position.
		/// The resulting transformation matrix maps the reference point to the
		/// negative z axis and the eye point to the origin.
		///
		/// \param[in] target Target position
		/// \param[in] up Up vector
		///                May not be parallel with view direction vector
		void lookAt(const Vector3& target, const Vector3& up);

		/// Set camera position and set view direction towards target position.
		/// The resulting transformation matrix maps the reference point to the
		/// negative z axis and the eye point to the origin.
		///
		/// \param[in] eye Camera/eye position
		/// \param[in] target Target position
		/// \param[in] up Up vector
		///                May not be parallel with vector from eye to target
		void lookAt(const Vector3& eye, const Vector3& target,
			const Vector3& up);

		void orthogonalizeViewUp();

	protected:
		float m_fov;
		float m_near;
		float m_far;
	};

} // namespace spatiumgl

#endif // SPATIUMGL_CAMERA_H