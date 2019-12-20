cmake_minimum_required(VERSION 3.2.0)

project(lasinfo)

# Create executable
add_executable(lasinfo lasinfo.cpp)
set_target_properties(lasinfo PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Link dependencies
target_link_libraries(lasinfo PRIVATE spatiumgl)

target_link_libraries(lasinfo PRIVATE LASlib)