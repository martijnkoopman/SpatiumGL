project(gfx3d_opengl_test LANGUAGES CXX)

add_executable(${PROJECT_NAME} test_PointCloudRenderer.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE spatiumgl GTest::GTest GTest::Main)

add_test(unit ${PROJECT_NAME})