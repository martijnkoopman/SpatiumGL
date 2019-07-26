cmake_minimum_required(VERSION 3.6)
project(PDALReader)

find_package(PDAL 1.6.0 REQUIRED CONFIG)

add_executable(pdalreader pdalreader.cpp)

target_link_libraries(pdalreader PRIVATE ${PDAL_LIBRARIES})
target_include_directories(pdalreader PRIVATE
    ${PDAL_INCLUDE_DIRS}
    ${PDAL_INCLUDE_DIRS}/pdal)