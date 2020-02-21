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

// Vertex shaders 

const char* vertexShaderScreenSizeNoColor = R"(
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

const char* vertexShaderWorldSizeNoColor = R"(
#version 330 core 
layout (location = 0) in vec3 pos; 
uniform mat4 model; 
uniform mat4 view; 

uniform mat4 projection; 
uniform float distanceScreen; 
uniform float pointSize; 

void main() 
{ 
  gl_Position = view * model * vec4(pos.xyz, 1.0); 
  gl_PointSize = max(1, pointSize * distanceScreen / -gl_Position.z); 
  gl_Position = projection * gl_Position; 
}
)";

const char* vertexShaderScreenSizeScalar = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in float scalar; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out float vertexScalar;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  vertexScalar = scalar;
}
)";

const char* vertexShaderWorldSizeScalar = R"(
#version 330 core 
layout (location = 0) in vec3 pos;
layout(location = 1) in float scalar; 
uniform mat4 model; 
uniform mat4 view; 

uniform mat4 projection; 
uniform float distanceScreen; 
uniform float pointSize; 

out float vertexScalar;

void main() 
{ 
  gl_Position = view * model * vec4(pos.xyz, 1.0); 
  gl_PointSize = max(1, pointSize * distanceScreen / -gl_Position.z); 
  gl_Position = projection * gl_Position;

  vertexScalar = scalar;
}
)";

const char* vertexShaderScreenSizeRGB = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 color; 

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexColor;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  vertexColor = color;
}
)";

const char* vertexShaderWorldSizeRGB = R"(
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

// Fragment shaders

const char* fragmentShaderNoColor = R"(
#version 330 core
out vec4 FragColor;

void main()
{
  FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
)";

const char* fragmentShaderScalar = R"(
#version 330 core

in float vertexScalar;
out vec4 FragColor;

uniform float colorramp_range[2];
uniform vec4 colorramp_colors[32];

void main()
{
  int index = int(roundEven(((vertexScalar - colorramp_range[0]) / (colorramp_range[1] - colorramp_range[0])) * (32 - 1) )); 
  FragColor = colorramp_colors[index];
}
)";

const char* fragmentShaderRGB = R"(
#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

void main()
{
  FragColor = vec4(vertexColor, 1.0);
}
)";

} // namespace gfx3d
} // namespace spgl
