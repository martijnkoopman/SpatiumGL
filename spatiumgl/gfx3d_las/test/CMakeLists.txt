project(gfx3d_las_test LANGUAGES CXX)

add_executable(${PROJECT_NAME} test_LasReader.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE spatiumgl GTest::GTest GTest::Main)

add_test(unit ${PROJECT_NAME})