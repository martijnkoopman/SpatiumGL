project(io_las_test LANGUAGES CXX)

add_executable(io_las_test test_LasReader.cpp)

target_link_libraries(io_las_test PRIVATE spatiumgl GTest::gtest GTest::gtest_main)

add_test(NAME io_las_test COMMAND $<TARGET_FILE:io_las_test>)
