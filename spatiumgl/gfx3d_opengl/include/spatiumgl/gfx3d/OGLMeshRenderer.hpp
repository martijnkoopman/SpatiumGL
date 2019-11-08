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

#ifndef SPATIUMGL_GFX3D_OGLMESHRENDERER_H
#define SPATIUMGL_GFX3D_OGLMESHRENDERER_H

#include "spatiumglexport.hpp"
#include "OGLRenderer.hpp"
#include "spatiumgl/gfx3d/Mesh.hpp"
#include "spatiumgl/gfx3d/Material.hpp"

namespace spatiumgl {
	namespace gfx3d {

		class SPATIUMGL_EXPORT OGLMeshRenderer : public OGLRenderer
		{
		public:
			/// Constructor
			///
			/// \param[in] mesh Mesh
			OGLMeshRenderer(const Mesh* mesh, const Material &material);

			/// Destructor
			virtual ~OGLMeshRenderer() override;

			/// Get the mesh.
			///
			/// \returnMesh
			const Mesh* mesh() const;

			void render(Camera* camera, double aspect) override;

		protected:
			unsigned int m_ebo; // Element Buffer Object (GLuint)
			Material m_material;
		};

	} // namespace gfx3d
} // namespace spatiumgl

#endif // SPATIUMGL_GFX3D_OGLMESHRENDERER_H
