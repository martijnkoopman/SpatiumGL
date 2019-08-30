project(gfx3d_test LANGUAGES CXX)

add_executable(gfx3d_test test_PointCloud.cpp)

find_package(GTest REQUIRED)

target_link_libraries(gfx3d_test PRIVATE spatiumgl GTest::GTest GTest::Main)

add_test(NAME gfx3d_test COMMAND $<TARGET_FILE:gfx3d_test>)