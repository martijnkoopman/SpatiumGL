cmake_minimum_required(VERSION 3.1.0)

project(spatiumgl VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build ${PROJECT_NAME} as shared library." ON)

find_package(LASlib REQUIRED)

# Create library target
file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR}/include *.hpp)

message(${sources})

add_library(${PROJECT_NAME} ${sources} ${headers})

# Set preprocessor definition for library import/export
target_compile_definitions(${PROJECT_NAME} PRIVATE SPATIUMGL_LIBRARY=1)

# Set include directories for target
target_include_directories(${PROJECT_NAME} PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  ${OPENGL_INCLUDE_DIR}
  ${GLM_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIRS}
  ${GLFW3_INCLUDE_DIR}
  ${LASlib_INCLUDE_DIRS})
  
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11 LINKER_LANGUAGE CXX)

# Link dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC ${GLEW_LIBRARIES} ${GLFW3_LIBRARY} ${OPENGL_gl_LIBRARY} PRIVATE LASlib)

install(TARGETS ${PROJECT_NAME})
install(DIRECTORY include/spatiumgl DESTINATION include
        FILES_MATCHING PATTERN "*.hpp")
		
# Unit tests for spatiumlib
enable_testing()
add_subdirectory(test)