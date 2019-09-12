# This script builds, configures and installs GTest in the build tree.
# Afterwards link against target GTest::gtest and GTest::gtest_main (static library)
# Do not use FindGTest() because the required input variables vary between CMake versions.

message(STATUS "Configure dependency GTest")

# Create build and install directories
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/install)

# Configure
configure_file(CMakeCache.txt.in cache.txt) # CMake bug: output name may not be 'CMakeCache.txt'

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" -C ${CMAKE_CURRENT_BINARY_DIR}/cache.txt ${CMAKE_CURRENT_SOURCE_DIR}/googletest-src
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
if(result)
  message(FATAL_ERROR "Configure dependency GTest FAILED: ${result}")
endif()
  
message(STATUS "Build dependency GTest (${CMAKE_BUILD_TYPE})")

# Build
execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${CMAKE_BUILD_TYPE} --target install
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
if(result)
  message(FATAL_ERROR "Build dependency GTest FAILED: ${result}")
endif()

message(STATUS "Successfully built dependency GTest")

# Expose configuration file
set(GTEST_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/install/lib/cmake/GTest/GTestConfig.cmake PARENT_SCOPE)
