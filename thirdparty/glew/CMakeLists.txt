# Download and unpack GLEW at configure time
if(NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/glew-src 
  OR NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/glew-build
  OR NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/glew-install)

  message(STATUS "Configuring to build dependency: GLEW")

  # Confiure CMakeLists.txt for target that builds GLEW
  configure_file(CMakeLists.txt.in glew-download/CMakeLists.txt)

  # Configure GLEW
  execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glew-download )
  if(result)
    message(FATAL_ERROR "Download + configure step for GLEW failed: ${result}")
  endif()

  message(STATUS "Building dependency: GLEW")

  # Build GLEW
  execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/glew-download )
  if(result)
    message(FATAL_ERROR "Build step for GLEW failed: ${result}")
  endif()
endif()

message("Dependency 'GLEW' available in directory: " ${CMAKE_CURRENT_BINARY_DIR}/glew-install)
