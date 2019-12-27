cmake_minimum_required(VERSION 3.2.0)

project(lasgrid)

# Create executable
add_executable(lasgrid lasgrid.cpp)
set_target_properties(lasgrid PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Link dependencies
target_link_libraries(lasgrid PRIVATE spatiumgl)

target_link_libraries(lasgrid PRIVATE LASlib)
