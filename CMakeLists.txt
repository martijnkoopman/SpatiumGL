cmake_minimum_required(VERSION 3.1.0)

project (SpatiumGLAll)

# Set module path with FindXXX.cmake files
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# Find dependencies
find_package(GLM MODULE REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(spatiumgl)
add_subdirectory(tools)
