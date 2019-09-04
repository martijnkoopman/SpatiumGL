cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Check testing
option(BUILD_TESTING "Build the testing tree." OFF)
if(BUILD_TESTING)
	enable_testing()
	find_package(GTest REQUIRED)
endif(BUILD_TESTING)

add_subdirectory(spatiumgl)
add_subdirectory(apps)

# Install CMake config file
#include(CMakePackageConfigHelpers)
#set(INSTALL_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include)
#message(${INSTALL_INCLUDE_DIRS})
#set(INSTALL_LIBRARIES ${CMAKE_INSTALL_PREFIX}/lib/spatiumgl.lib)
#message(${INSTALL_LIBRARIES})
#configure_package_config_file(cmake/SpatiumGLConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/SpatiumGLConfig.cmake
#                              INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/cmake
#                              PATH_VARS INSTALL_INCLUDE_DIRS INSTALL_LIBRARIES)
##write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/SpatiumGLConfigVersion.cmake
##                                 VERSION 0.1.0
##                                 COMPATIBILITY SameMajorVersion)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/SpatiumGLConfig.cmake 
#        DESTINATION cmake) #${CMAKE_CURRENT_BINARY_DIR}/SpatiumGLConfigVersion.cmake