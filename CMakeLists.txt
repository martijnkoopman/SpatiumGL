cmake_minimum_required(VERSION 3.1.0)

# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

project(spatiumgl_all)

# Force single configuration build.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()
if (CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "")
endif()

# Check testing
option(BUILD_TESTING "Build the testing tree." OFF)
if(BUILD_TESTING)
  enable_testing()

  # Build dependencies for testing
  add_subdirectory(thirdparty/googletest)
  include(${GTEST_CONFIG_FILE})
endif()

# Build dependencies for GFX3D_OPENGL
if(SPATIUMGL_MODULE_GFX3D_OPENGL)
  add_subdirectory(thirdparty/glfw)
  include(${GLFW_CONFIG_FILE})
  add_subdirectory(thirdparty/glew)
  include(${GLEW_CONFIG_FILE})
endif()

if(SPATIUMGL_MODULE_IO_LAS)
  add_subdirectory(thirdparty/laslib)
  include(${LASLIB_CONFIG_FILE})
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

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
