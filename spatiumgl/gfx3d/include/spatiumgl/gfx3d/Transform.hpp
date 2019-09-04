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

#ifndef SPATIUMGL_GFX3D_TRANSFORM_H
#define SPATIUMGL_GFX3D_TRANSFORM_H

#include "spatiumglexport.hpp"
#include "spatiumgl/Vector.hpp"
#include "spatiumgl/Matrix.hpp"

namespace spatiumgl {
	namespace gfx3d {

		/// \class Transform
		/// \brief Tranformation in 3D space.
		///
		/// Default transformation (identity).
		///
		/// 1 0 0 x
		/// 0 1 0 y
		/// 0 0 1 z
		/// 0 0 0 1
		///
		/// 1st column = right vector
		/// 2nd column = up vector
		/// 3rd column = back vector
		/// 4rd column = translation (position)
		class SPATIUMGL_EXPORT Transform
		{
		public:
			Transform();

			/// Get the vector pointing to the right (positive X axis)
			///
			/// \return Right vector
			Vector3 right() const;

			/// Get the vector pointing up (positive y axis)
			///
			/// \return Up vector
			Vector3 up() const;

			/// Get the vector pointing back (positive z axis)
			///
			/// \return Back vector
			Vector3 back() const;

			/// Get the position in world space (translation)
			///
			/// \return Position
			Vector3 position() const;

			/// Set the position in world space (translation)
			///
			/// \param[in] position Position
			void setPosition(const Vector3& position);
			/// Set the transformation matrix
			///
			/// \param[in] matrix Transformation matrix
			void setMatrix(const Matrix4x4& matrix);

			/// Get the transformation matrix
			///
			/// \return Transformation matrix
			Matrix4x4 matrix() const;

			/// Convert 3D Cartesian point coordinates from object space to world space.
			/// Object coordinates are defined with respect to the object's local
			/// coordinate system.
			/// World coordinates are defined with resect to the world's global
			/// cordinate system. (Origin = [0,0,0])
			///
			/// \param[in] point Point cordinates in object space
			/// \return Point coordinates in world space
			Vector3 objectPointToWorldPoint(const Vector3& point) const;

			/// Convert 3D Cartesian point coordinates from world space to object space.
			/// World coordinates are defined with resect to the world's global
			/// cordinate system. (Origin = [0,0,0])
			/// Object coordinates are defined with respect to the object's local
			/// coordinate system.
			///
			/// \param[in] point Point cordinates in world space
			/// \return Point coordinates in object space
			Vector3 worldPointToObjectPoint(const Vector3& point) const;

		protected:
			/// Transformation matrix
			Matrix4x4 m_matrix;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_TRANSFORM_H