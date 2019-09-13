# This script builds, configures and installs LASlib in the build tree.
# Link afterwards against target LASlib (static library)
# Do not use find_package(LASlib) because the required input variables vary between CMake versions.

message(STATUS "Configure dependency LASlib")

# Create build and install directories
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/install)

# Configure
configure_file(CMakeCache.txt.in cache.txt) # CMake bug: output name may not be 'CMakeCache.txt'

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" -C ${CMAKE_CURRENT_BINARY_DIR}/cache.txt ${CMAKE_CURRENT_SOURCE_DIR}/laslib-src 
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
if(result)
  message(FATAL_ERROR "Configure dependency LASlib FAILED: ${result}")
endif()
  
message(STATUS "Build dependency LASlib (${CMAKE_BUILD_TYPE})")

# Build
execute_process(COMMAND ${CMAKE_COMMAND} --build . --target LASlib --config ${CMAKE_BUILD_TYPE}
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
if(result)
  message(FATAL_ERROR "Build dependency LASlib FAILED: ${result}")
endif()

# Install
execute_process(COMMAND ${CMAKE_COMMAND} --build . --target install --config ${CMAKE_BUILD_TYPE}
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
if(result)
  message(FATAL_ERROR "Install dependency LASlib FAILED: ${result}")
endif()

message(STATUS "Successfully built dependency LASlib")

# Expose configuration file
set(LASLIB_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/install/lib/cmake/LASlib/LASlib-config.cmake PARENT_SCOPE)
