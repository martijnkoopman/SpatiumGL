cmake_minimum_required(VERSION 3.14)

PROJECT(pcgridsampler LANGUAGES CXX)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create executable
add_executable(${PROJECT_NAME} pcgridsampler.cpp)

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE spatiumgl)

install(TARGETS ${PROJECT_NAME})