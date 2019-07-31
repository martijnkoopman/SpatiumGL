cmake_minimum_required(VERSION 3.6)
project(downsampler CXX)

#find_package(SpatiumGL REQUIRED)
find_package(LASlib REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/include/)
add_executable(downsampler downsampler.cpp)

target_link_libraries(downsampler PRIVATE SpatiumGL LASlib)
target_include_directories(downsampler PRIVATE
    ${LASlib_INCLUDE_DIRS})