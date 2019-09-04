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

#ifndef SPATIUMGL_GFX3D_SCENEOBJECT_H
#define SPATIUMGL_GFX3D_SCENEOBJECT_H

#include "spatiumglexport.hpp"
#include "Transform.hpp"

namespace spatiumgl {
	namespace gfx3d {

		/// \class SceneObject
		/// \brief Object in a 3D scene
		///
		/// A SceneObject is transformable in world space.
		class SPATIUMGL_EXPORT SceneObject
		{
		public:
			SceneObject();

			/// Get the transformation
			///
			/// \return transformation
			Transform& transform();

		protected:
			Transform m_transform;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_SCENEOBJECT_H