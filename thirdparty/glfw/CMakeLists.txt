# Download and unpack glfw at configure time
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/glfw-src 
  OR NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/glfw-build
  OR NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/glfw-install)

  message(STATUS "Configuring to build dependency: GLFW")

  # Confiure CMakeLists.txt for target that builds GLFW
  configure_file(CMakeLists.txt.in glfw-download/CMakeLists.txt)

  # Configure GLFW
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glfw-download )
  if(result)
    message(FATAL_ERROR "Download + configure step for glfw failed: ${result}")
  endif()

  message(STATUS "Building dependency: GLFW")

  # Build GLFW
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glfw-download )
  if(result)
    message(FATAL_ERROR "Build step for glfw failed: ${result}")
  endif()
endif()

message("Dependency 'GLFW' available in directory: " ${CMAKE_CURRENT_BINARY_DIR}/glfw-install)

# Expose GLFW install directory
set(glfw3_DIR "${CMAKE_CURRENT_BINARY_DIR}/glfw-install/lib/cmake/glfw3" PARENT_SCOPE)
