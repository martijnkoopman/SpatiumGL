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

#ifndef SPATIUMGL_GFX3D_OGLSHADERPROGRAM_H
#define SPATIUMGL_GFX3D_OGLSHADERPROGRAM_H

#include "spatiumglexport.hpp"

#include <string> // std::string

namespace spgl {
namespace gfx3d {

class SPATIUMGL_EXPORT OGLShaderProgram
{
public:
  /// Default constructor
  OGLShaderProgram();

  /// Constructor
  ///
  /// \param[in] vertexShaderSource Vertex shader source
  /// \param[in] fragmentShaderSource Fragment shader source
  OGLShaderProgram(const std::string& vertexShaderSource,
                   const std::string& fragmentShaderSource);

  /// Destructor
  ~OGLShaderProgram();

  /// Set shader sources
  ///
  /// \param[in] vertexShaderSource Vertex shader source
  /// \param[in] fragmentShaderSource Fragment shader source
  void setShaderSources(const std::string& vertexShaderSource,
                        const std::string& fragmentShaderSource);

  /// Validate vertex shader, fragment shader and shader program.
  ///
  /// \param[out] errorMessage Error message (if any)
  /// \return True on valid, false otherwise
  bool validate(std::string& errorMessage);

  /// Use the shader program.
  void use();

  /// Free the shader program (delete).
  void free();

  /// Get the vertex shader ID.
  ///
  /// \return vertex shader ID
  unsigned int vertexShaderId() const { return m_vertexShaderId; }

  /// Get the fragment shader ID.
  ///
  /// \return fragment shader ID
  unsigned int fragmentShaderId() const { return m_fragmentShaderId; }

  /// Get the shader program ID.
  ///
  /// \return shader program ID
  unsigned int shaderProgamId() const { return m_shaderProgramId; }

protected:
  /// Create shader program from shader sources.
  ///
  /// \param[in] vertexShaderSource Vertex shader source
  /// \param[in] fragmentShaderSource Fragment shader source
  void createShaderProgram(const std::string& vertexShaderSource,
                           const std::string& fragmentShaderSource);

  unsigned int m_vertexShaderId;
  unsigned int m_fragmentShaderId;
  unsigned int m_shaderProgramId;
};

} // namespace gfx3d
} // namespace spgl

#endif // SPATIUMGL_GFX3D_OGLSHADERPROGRAM_H