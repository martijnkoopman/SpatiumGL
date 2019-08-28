file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

set (spatiumgl_sources ${spatiumgl_sources} ${sources} PARENT_SCOPE) 
set (spatiumgl_headers ${spatiumgl_headers} ${headers} PARENT_SCOPE)
set (spatiumgl_includes $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> $<INSTALL_INTERFACE:include> PARENT_SCOPE)

if(BUILD_TESTING)
	add_subdirectory(test)
endif(BUILD_TESTING)