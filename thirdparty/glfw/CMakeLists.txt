# This script builds, configures and installs GLFW in the build tree.
# Link afterwards against target ????(static library)
# Do not use FindGLFW() because the required input variables vary between CMake versions.

message(STATUS "Configure dependency GLFW")

# Create build and install directories
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/install)

# Configure
configure_file(CMakeCache.txt.in cache.txt) # CMake bug: output name may not be 'CMakeCache.txt'

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" -C ${CMAKE_CURRENT_BINARY_DIR}/cache.txt ${CMAKE_CURRENT_SOURCE_DIR}/glfw-src 
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
if(result)
  message(FATAL_ERROR "Configure dependency GLFW FAILED: ${result}")
endif()
  
message(STATUS "Build dependency GLFW (${CMAKE_BUILD_TYPE})")

# Build
execute_process(COMMAND ${CMAKE_COMMAND} --build . --target glfw --config ${CMAKE_BUILD_TYPE}
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
if(result)
  message(FATAL_ERROR "Build dependency GLFW FAILED: ${result}")
endif()

# Install
execute_process(COMMAND ${CMAKE_COMMAND} --build . --target install --config ${CMAKE_BUILD_TYPE}
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/build)
if(result)
  message(FATAL_ERROR "Install dependency GLFW FAILED: ${result}")
endif()

message(STATUS "Successfully built dependency GLFW")

# Expose configuration file
set(GLFW_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/install/lib/cmake/glfw3/glfw3Config.cmake PARENT_SCOPE)
