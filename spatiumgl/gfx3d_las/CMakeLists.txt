# Find dependencies
find_package(LASlib REQUIRED)

# List header and source files
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Create target
add_library(spatiumgl_gfx3d_las STATIC ${sources} ${headers})

# Set defition for export
target_compile_definitions(spatiumgl_gfx3d_las PRIVATE SPATIUMGL_LIBRARY=1)

target_include_directories(spatiumgl_gfx3d_las 
  PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include> 
  PRIVATE
  ${spatiumgl_includes})

# Link dependencies to target
target_link_libraries(spatiumgl_gfx3d_las PRIVATE LASlib)

# Link target to spatiumgl
target_link_libraries(spatiumgl PUBLIC spatiumgl_gfx3d_las)

if(BUILD_TESTING)
	add_subdirectory(test)
endif(BUILD_TESTING)