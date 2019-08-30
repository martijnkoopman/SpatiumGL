cmake_minimum_required(VERSION 3.1.0)

project(spatiumgl VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build spatiumgl as shared library." ON)

# Present SPATIUMGL_MODULE_* options for user
option(SPATIUMGL_MODULE_GFX3D "" OFF)
option(SPATIUMGL_MODULE_GFX3D_OPENGL "" OFF)
option(SPATIUMGL_MODULE_IO_LAS "" OFF)

# Enable dependent modules if needed
if(SPATIUMGL_MODULE_GFX3D_OPENGL)
	set(SPATIUMGL_MODULE_GFX3D ON CACHE BOOL "" FORCE)
endif()
if(SPATIUMGL_MODULE_IO_LAS)
	set(SPATIUMGL_MODULE_GFX3D ON CACHE BOOL "" FORCE)
endif()

# Process modules by subdirectories
add_subdirectory(core)
if(SPATIUMGL_MODULE_GFX3D)
	add_subdirectory(gfx3d)
endif()
if(SPATIUMGL_MODULE_GFX3D_OPENGL)
	add_subdirectory(gfx3d_opengl)
endif()
if(SPATIUMGL_MODULE_IO_LAS)
	add_subdirectory(io_las)
endif()

# Create library
add_library(spatiumgl spatiumgl.cpp)
set_target_properties(spatiumgl PROPERTIES LINKER_LANGUAGE CXX)

# Set compile definitions to export symbols
target_compile_definitions(spatiumgl PRIVATE SPATIUMGL_LIBRARY=1)
if (BUILD_SHARED_LIBS)
	target_compile_definitions(spatiumgl PRIVATE SPATIUMGL_SHARED=1)
endif()

# Link modules
target_link_libraries(spatiumgl PUBLIC core)
if(SPATIUMGL_MODULE_GFX3D)
	target_link_libraries(spatiumgl PUBLIC gfx3d)
endif()
if(SPATIUMGL_MODULE_GFX3D_OPENGL)
	target_link_libraries(spatiumgl PUBLIC gfx3d_opengl)
endif()
if(SPATIUMGL_MODULE_IO_LAS)
	target_link_libraries(spatiumgl PUBLIC io_las)
endif()

# Install library
install(TARGETS spatiumgl DESTINATION lib)
install(DIRECTORY core/include/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")
if(SPATIUMGL_MODULE_GFX3D)
	install(DIRECTORY gfx3d/include/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")
endif()
if(SPATIUMGL_MODULE_GFX3D_OPENGL)
	install(DIRECTORY gfx3d_opengl/include/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")
endif()
if(SPATIUMGL_MODULE_IO_LAS)
	install(DIRECTORY io_las/include/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")
endif()

# Unit testing
if(BUILD_TESTING)
	add_subdirectory(core/test)
	if(SPATIUMGL_MODULE_GFX3D)
		add_subdirectory(gfx3d/test)
	endif()
	if(SPATIUMGL_MODULE_GFX3D_OPENGL)
		add_subdirectory(gfx3d_opengl/test)
	endif()
	if(SPATIUMGL_MODULE_IO_LAS)
		add_subdirectory(io_las/test)
	endif()
endif()