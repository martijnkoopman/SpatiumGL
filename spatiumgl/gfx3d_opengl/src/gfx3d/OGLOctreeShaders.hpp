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

namespace spgl {
namespace gfx3d {

// Shader 
// layout(location = 2) in float aRadius;
const char* octreeVertexShader = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aOffset;
layout(location = 2) in float aRadius;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  vec3 scaled = aPos * aRadius;
  gl_Position = projection * view * model * vec4(scaled + aOffset, 1.0);
}
)";

const char* octreeFragmentShader = R"(
#version 330 core
out vec4 FragColor;

void main()
{
  FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);
}
)";

} // namespace gfx3d
} // namespace spgl
