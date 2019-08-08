cmake_minimum_required(VERSION 3.14)

PROJECT(pcviewer LANGUAGES CXX)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE sources ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB_RECURSE headers ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)

# Create executable
add_executable(${PROJECT_NAME} ${sources} ${headers})

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE spatiumgl)# ${GLEW_LIBRARIES} ${GLFW3_LIBRARY} ${OPENGL_gl_LIBRARY})

