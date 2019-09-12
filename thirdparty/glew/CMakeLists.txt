# This script builds, configures and installs GLEW in the build tree.
# Link afterwards against target GLEW::glew_s (static library)
# Do not use FindGLEW() because the required input variables vary between CMake versions.

message(STATUS "Configure dependency GLEW")

# Create build and install directories
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/install)

# Configure
configure_file(CMakeCache.txt.in cache.txt) # CMake bug: output name may not be 'CMakeCache.txt'

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" -C ${CMAKE_CURRENT_BINARY_DIR}/cache.txt ${CMAKE_CURRENT_SOURCE_DIR}/glew-src/build/cmake 
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
if(result)
  message(FATAL_ERROR "Configure dependency GLEW FAILED: ${result}")
endif()
  
message(STATUS "Build dependency GLEW (${CMAKE_BUILD_TYPE})")

# Build
execute_process(COMMAND ${CMAKE_COMMAND} --build . --target glew_s --config ${CMAKE_BUILD_TYPE}
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
if(result)
  message(FATAL_ERROR "Build dependency GLEW FAILED: ${result}")
endif()

# Install
execute_process(COMMAND ${CMAKE_COMMAND} --build . --target install --config ${CMAKE_BUILD_TYPE}
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
if(result)
  message(FATAL_ERROR "Install dependency GLEW FAILED: ${result}")
endif()

message(STATUS "Successfully built dependency GLEW")

# Expose configuration file
set(GLEW_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/install/lib/cmake/glew/glew-config.cmake PARENT_SCOPE)
