cmake_minimum_required(VERSION 3.2.0)

project(lasoctree)

# Create executable
add_executable(lasoctree lasoctree.cpp LasOctant.hpp LasOctree.hpp)
set_target_properties(lasoctree PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Link dependencies
target_link_libraries(lasoctree PRIVATE spatiumgl)

target_link_libraries(lasoctree PRIVATE LASlib)