cmake_minimum_required(VERSION 3.1.0)

project(spatiumgl VERSION 0.1.0 LANGUAGES CXX)

add_subdirectory(common)

# Create library target
option(BUILD_SHARED_LIBS "Build spatiumgl as shared library." ON)
add_library(spatiumgl ${spatiumgl_sources} ${spatiumgl_headers})
target_compile_definitions(spatiumgl PRIVATE SPATIUMGL_LIBRARY=1)
target_include_directories(spatiumgl PUBLIC ${spatiumgl_includes})
set_target_properties(spatiumgl PROPERTIES CXX_STANDARD 11 LINKER_LANGUAGE CXX)
cmake_policy(SET CMP0079 NEW) # Allow linking dependencies from subdirectories

# Add modules

# GFX LAS module
option(SPATIUMGL_MODULE_GFX3D "Build ${PROJECT_NAME} with 3D graphics module." OFF)
if(SPATIUMGL_MODULE_GFX3D)
    add_subdirectory(gfx3d)
endif(SPATIUMGL_MODULE_GFX3D)

# GFX LAS module
option(SPATIUMGL_MODULE_GFX3D_LAS "Build ${PROJECT_NAME} with LAS read/write support." OFF)
if(SPATIUMGL_MODULE_GFX3D_LAS)
    add_subdirectory(gfx3d_las)
endif(SPATIUMGL_MODULE_GFX3D_LAS)

# GFX OpenGL module
option(SPATIUMGL_MODULE_GFX3D_OPENGL "Build ${PROJECT_NAME} with OpenGL rendering." OFF)
if(SPATIUMGL_MODULE_GFX3D_OPENGL)
    add_subdirectory(gfx3d_opengl)
endif(SPATIUMGL_MODULE_GFX3D_OPENGL)

# CV module
option(SPATIUMGL_MODULE_CV_OPENGL "Build ${PROJECT_NAME} with OpenGL image processing." OFF)
if(SPATIUMGL_MODULE_CV_OPENGL)
    add_subdirectory(cv_opengl)
endif(SPATIUMGL_MODULE_CV_OPENGL)

target_include_directories(spatiumgl PUBLIC ${spatiumgl_includes})

# Install target
install(TARGETS spatiumgl)
install(DIRECTORY common/include/spatiumgl DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")
