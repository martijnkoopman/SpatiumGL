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

#ifndef SPATIUMGL_GFX3D_MATERIAL_H
#define SPATIUMGL_GFX3D_MATERIAL_H

#include "spatiumglexport.hpp"
#include "spatiumgl/Vector4.hpp"

namespace spatiumgl {
	namespace gfx3d {

	/// \class Material
	class SPATIUMGL_EXPORT Material
	{
		public:
			/// Constructor
			///
			/// \param[in] color Color RGB
			Material(const Vector4& color)
				: m_color(color)
			{				
			}

			Vector4 color() const
			{
				return m_color;
			}

		protected:
			Vector4 m_color;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_MATERIAL_H