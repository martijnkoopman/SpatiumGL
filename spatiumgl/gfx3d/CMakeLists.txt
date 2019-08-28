# List header and source files
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Create target
add_library(spatiumgl_gfx3d OBJECT ${sources} ${headers})

# Set export compile definition
target_compile_definitions(spatiumgl_gfx3d PRIVATE SPATIUMGL_LIBRARY=1)

# Set include directories for target
target_include_directories(spatiumgl_gfx3d 
  PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include> 
  PRIVATE
  ${spatiumgl_includes})

# Link target to spatiumgl
#target_link_libraries(spatiumgl PUBLIC spatiumgl_gfx3d)

# Link spatiumgl to target
#target_link_libraries(spatiumgl_gfx3d spatiumgl)

set (spatiumgl_includes ${spatiumgl_includes} $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PARENT_SCOPE)

target_sources(spatiumgl PUBLIC $<TARGET_OBJECTS:spatiumgl_gfx3d>)

if(BUILD_TESTING)
	add_subdirectory(test)
endif(BUILD_TESTING)