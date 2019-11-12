cmake_minimum_required(VERSION 3.1.0)

project(pcviewer)

# Create executable
add_executable(pcviewer pcviewer.cpp)
set_target_properties(pcviewer PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Link dependencies
target_link_libraries(pcviewer PRIVATE spatiumgl)

#install(TARGETS ${PROJECT_NAME})
