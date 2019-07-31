#include "spatiumgl/Camera.hpp"

#include <glm/gtc/matrix_access.hpp> // glm::column
//#include <glm/gtc/matrix_transform.hpp> // glm::lookat

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
		void Camera::lookAt(const glm::vec3& target, const glm::vec3& up)
		{
			// Compute vector from target to eye
			glm::vec3 back = glm::normalize(m_transform.position() - target);

			// Normalize and orthogonalize view up vector
			glm::vec3 right = glm::cross(glm::normalize(up), back);
			glm::vec3 upOrtho = glm::cross(back, right);

			// Set rotation of transformation matrix based on view direction and view
			// up vector.
			glm::mat4 M = m_transform.matrix();

			// First COLUMN is right vector
			M = glm::column(M, 0, glm::vec4(right, 0.0f));

			// Second COLUMN is up vector
			M = glm::column(M, 1, glm::vec4(upOrtho, 0.0f));

			// Third COLUMN is back vector
			M = glm::column(M, 2, glm::vec4(back, 0.0f));

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
		void Camera::lookAt(const glm::vec3& eye, const glm::vec3& target,
			const glm::vec3& up)
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
			glm::vec3 upOrtho = glm::cross(m_transform.back(), m_transform.right());

			glm::mat4 M = m_transform.matrix();

			// Second COLUMN is up vector
			glm::column(M, 1, glm::vec4(upOrtho, 0.0f));

			m_transform.setMatrix(M);
		}

} // namespace spatiumgl