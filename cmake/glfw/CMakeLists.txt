# Download and unpack glfw at configure time
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/glfw-src OR NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/glfw-build)
  configure_file(CMakeLists.txt.in glfw-download/CMakeLists.txt)
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glfw-download )
  if(result)
    message(FATAL_ERROR "CMake step for glfw failed: ${result}")
  endif()
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glfw-download )
  if(result)
    message(FATAL_ERROR "Build step for glfw failed: ${result}")
  endif()
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add glfw directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/glfw-src
                 ${CMAKE_CURRENT_BINARY_DIR}/glfw-build
                 EXCLUDE_FROM_ALL)


