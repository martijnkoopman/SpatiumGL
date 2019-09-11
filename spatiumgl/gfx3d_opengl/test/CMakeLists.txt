project(gfx3d_opengl_test LANGUAGES CXX)

add_executable(gfx3d_opengl_test test_PointCloudRenderer.cpp)

find_package(GTest REQUIRED)

target_link_libraries(gfx3d_opengl_test PRIVATE spatiumgl GTest::GTest GTest::Main)

add_test(NAME gfx3d_opengl_test COMMAND $<TARGET_FILE:gfx3d_opengl_test>)
