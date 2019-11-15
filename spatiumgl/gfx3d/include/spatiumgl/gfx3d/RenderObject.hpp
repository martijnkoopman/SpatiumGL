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

#ifndef SPATIUMGL_GFX3D_RENDEROBJECT_H
#define SPATIUMGL_GFX3D_RENDEROBJECT_H

#include "spatiumglexport.hpp"
#include "SceneObject.hpp"
#include "spatiumgl/Bounds.hpp"

namespace spatiumgl {
	namespace gfx3d {

		/// \class RenderObject
		/// \brief Scene object that can be rendered.
		///
		/// A RenderObject has a certain size (boundaries). It is up to the derived 
		/// class to keep these updated.
		class SPATIUMGL_EXPORT RenderObject : public SceneObject
		{
		public:
			/// Default constrcutor
			RenderObject();

			/// Get boundaries of the object (axis aligned bounding box).
			///
			/// \return Boundaries
      BoundingBox<double> bounds() const;

		protected:
      BoundingBox<double> m_bounds;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_RENDEROBJECT_H
