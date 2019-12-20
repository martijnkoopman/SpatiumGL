file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE private_headers ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

add_library(gfx3d_opengl STATIC ${sources} ${headers} ${private_headers})
set_target_properties(gfx3d_opengl PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)
target_compile_definitions(gfx3d_opengl PRIVATE FOO_LIBRARY=1)

target_include_directories(gfx3d_opengl PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>)
	
target_link_libraries(gfx3d_opengl PRIVATE core gfx3d idx)
 
find_package(OpenGL REQUIRED)

target_include_directories(gfx3d_opengl PRIVATE ${OPENGL_INCLUDE_DIR})

target_link_libraries(gfx3d_opengl PRIVATE ${GLEW_LIBRARIES} ${OPENGL_gl_LIBRARY} glfw GLEW::glew_s)
