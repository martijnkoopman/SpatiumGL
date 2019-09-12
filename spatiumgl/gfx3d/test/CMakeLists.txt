project(gfx3d_test LANGUAGES CXX)

add_executable(gfx3d_test test_PointCloud.cpp)

target_link_libraries(gfx3d_test PRIVATE spatiumgl GTest::gtest GTest::gtest_main)

add_test(NAME gfx3d_test COMMAND $<TARGET_FILE:gfx3d_test>)
