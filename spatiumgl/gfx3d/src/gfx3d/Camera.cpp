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

#include "spatiumgl/gfx3d/Camera.hpp"

namespace spatiumgl {

Camera::Camera(float fov, float near, float far)
			: SceneObject()
			, m_fov(fov)
			, m_near(near)
			, m_far(far)
		{
		}

		float Camera::fov() const
		{
			return m_fov;
		}

		/// Get the distance to the near clipping plane in world space.
		///
		/// \return Near clipping plane distance.
		float Camera::near() const
		{
			return m_near;
		}

		/// Get the distance to the far clipping plane in world space.
		///
		/// \return Far clipping plane distance.
		float Camera::far() const
		{
			return m_far;
		}

		/// Set view direction towards target position.
		/// The resulting transformation matrix maps the reference point to the
		/// negative z axis and the eye point to the origin.
		///
		/// \param[in] target Target position
		/// \param[in] up Up vector
		///                May not be parallel with view direction vector
		void Camera::lookAt(const Vector3& target, const Vector3& up)
		{
			// Compute vector from target to eye
			Vector3 back = (m_transform.position() - target).normalized();

			// Normalize and orthogonalize view up vector
			Vector3 right = Vector3(up.normalized()).cross(back);
			Vector3 upOrtho = back.cross(right);

			// Set rotation of transformation matrix based on view direction and view
			// up vector.
			Matrix4x4 M = m_transform.matrix();

			// First COLUMN is right vector
			M[0] = Vector4(right, 0.0);

			// Second COLUMN is up vector
			M[1] = Vector4(upOrtho, 0.0);

			// Third COLUMN is back vector
			M[2] = Vector4(back, 0.0);

			m_transform.setMatrix(M);
		}

		/// Set camera position and set view direction towards target position.
		/// The resulting transformation matrix maps the reference point to the
		/// negative z axis and the eye point to the origin.
		///
		/// \param[in] eye Camera/eye position
		/// \param[in] target Target position
		/// \param[in] up Up vector
		///                May not be parallel with vector from eye to target
		void Camera::lookAt(const Vector3& eye, const Vector3& target,
			const Vector3& up)
		{
			m_transform.setPosition(eye);
			lookAt(target, up);
		}

		/*
		/// Set camera position and set view direction towards target position.
		/// The resulting transformation matrix maps the reference point to the
		/// negative z axis and the eye point to the origin.
		///
		/// \param[in] eye Camera/eye position
		/// \param[in] target Target position
		/// \param[in] up Up vector
		///                May not be parallel with vector from eye to target
		void lookAt(const glm::vec3& eye, const glm::vec3& target, 
			const glm::vec3& up)
		{
			// Normalize and orthogonalize view up vector
			//glm::vec3 back = glm::normalize(eye - target);
			//glm::vec3 right = glm::cross(glm::normalize(up), back);
			//glm::vec3 upOrtho = glm::cross(back, right);

			m_transform.setMatrix(glm::lookAt(eye, target, up));
		}
		*/

		void Camera::orthogonalizeViewUp()
		{
			Vector3 upOrtho = m_transform.back().cross(m_transform.right());

			Matrix4x4 M = m_transform.matrix();

			// Second COLUMN is up vector
			M[1] = Vector4(upOrtho, 0.0);

			m_transform.setMatrix(M);
		}

} // namespace spatiumgl