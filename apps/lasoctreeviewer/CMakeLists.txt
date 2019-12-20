cmake_minimum_required(VERSION 3.2.0)

project(lasoctreeviewer)

# Create executable
add_executable(lasoctreeviewer lasoctreeviewer.cpp)
set_target_properties(lasoctreeviewer PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Link dependencies
target_link_libraries(lasoctreeviewer PRIVATE spatiumgl)