cmake_minimum_required(VERSION 3.1.0)

project(pcviewer)

# Create executable
add_executable(${PROJECT_NAME} pcviewer.cpp)

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE spatiumgl)

install(TARGETS ${PROJECT_NAME})
