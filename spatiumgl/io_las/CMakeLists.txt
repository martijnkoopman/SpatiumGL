file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(io_las STATIC ${sources} ${headers})
set_target_properties(io_las PROPERTIES CXX_STANDARD 11 LINKER_LANGUAGE CXX)
target_compile_definitions(io_las PRIVATE FOO_LIBRARY=1)

target_include_directories(io_las PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>)
	
target_link_libraries(io_las PRIVATE core gfx3d)

find_package(LASlib REQUIRED)
target_link_libraries(io_las PRIVATE LASlib)