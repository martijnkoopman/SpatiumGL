cmake_minimum_required(VERSION 3.1.0)

project(lasviewer)

# Create executable
add_executable(lasviewer lasviewer.cpp)
set_target_properties(lasviewer PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Link dependencies
target_link_libraries(lasviewer PRIVATE spatiumgl)

#install(TARGETS ${PROJECT_NAME})
