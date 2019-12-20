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

// Point cloud vertex shader for:
// - Point size in world space
// - Point color by RGB scalars
const char* vertexShaderColorFixedSize = R"(
#version 330 core 
layout (location = 0) in vec3 pos; 
layout (location = 1) in vec3 color; 
uniform mat4 model; 
uniform mat4 view; 

uniform mat4 projection; 
uniform float distanceScreen; 
uniform float pointSize; 

out vec3 vertexColor; 

void main() 
{ 
  gl_Position = view * model * vec4(pos.xyz, 1.0); 
  gl_PointSize = max(1, pointSize * distanceScreen / -gl_Position.z); 
  gl_Position = projection * gl_Position; 
  vertexColor = color; 
}
)";

// Point cloud fragment shader for:
// - Point color by RGB scalars
const char* fragmentShaderColor = R"(
#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

void main()
{
  FragColor = vec4(vertexColor, 1.0);
}
)";

// Shader
const char* vertexShaderNoPointSize = R"(
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSingleColor = R"(
#version 330 core
out vec4 FragColor;

void main()
{
  FragColor = vec4(1.0f, 0.5f, 0.5f, 1.0f);
}
)";

} // namespace gfx3d
} // namespace spgl
