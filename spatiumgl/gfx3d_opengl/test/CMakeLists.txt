project(gfx3d_opengl_test LANGUAGES CXX)

add_executable(gfx3d_opengl_test test_PointCloudRenderer.cpp)

target_link_libraries(gfx3d_opengl_test PRIVATE spatiumgl gtest_main)

add_test(NAME gfx3d_opengl_test COMMAND $<TARGET_FILE:gfx3d_opengl_test>)
