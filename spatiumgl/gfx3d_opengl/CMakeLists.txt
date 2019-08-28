# Find dependencies
find_package(GLEW REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)

# List header and source files
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Create target
add_library(spatiumgl_gfx3d_opengl STATIC ${sources} ${headers})

# Set defition for export
target_compile_definitions(spatiumgl_gfx3d_opengl PRIVATE SPATIUMGL_LIBRARY=1)

target_include_directories(spatiumgl_gfx3d_opengl 
  PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include> 
  PRIVATE
  ${spatiumgl_includes}
  ${OPENGL_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIRS})

# Link dependencies to target
target_link_libraries(spatiumgl_gfx3d_opengl PUBLIC ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY} glfw spatiumgl spatiumgl_gfx3d)

# Link target to spatiumgl
target_link_libraries(spatiumgl PUBLIC spatiumgl_gfx3d_opengl)

if(BUILD_TESTING)
	add_subdirectory(test)
endif(BUILD_TESTING)