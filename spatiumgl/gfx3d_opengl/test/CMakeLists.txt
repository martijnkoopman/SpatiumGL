project(gfx3d_opengl_test LANGUAGES CXX)

add_executable(gfx3d_opengl_test test_Renderers.cpp)
set_target_properties(gfx3d_opengl_test PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_link_libraries(gfx3d_opengl_test PRIVATE spatiumgl GTest::gtest GTest::gtest_main)

add_test(NAME gfx3d_opengl_test COMMAND $<TARGET_FILE:gfx3d_opengl_test>)
