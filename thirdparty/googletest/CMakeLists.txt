# Download and unpack googletest at configure time
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/googletest-src
  OR NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
  OR NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/googletest-install)

  message(STATUS "Configuring to build dependency: googletest")

  # Confiure CMakeLists.txt for target that builds googletest
  configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)

  # Configure googletest
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
  endif()

  message(STATUS "Building dependency: googletest")

  # Build googletest
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
  if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
  endif()
endif()

message("Dependency 'googletest' available in directory: " ${CMAKE_CURRENT_BINARY_DIR}/googletest-install)

# Expose googletest install directory
set(GTEST_ROOT "${CMAKE_CURRENT_BINARY_DIR}/googletest-install" PARENT_SCOPE)

# /lib/cmake/GTest
