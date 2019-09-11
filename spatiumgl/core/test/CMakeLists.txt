project(core_test LANGUAGES CXX)

add_executable(core_test test_Vector2.cpp test_Vector3.cpp test_Vector4.cpp test_Vector.cpp test_Matrix2.cpp test_Matrix3.cpp test_Matrix4.cpp test_Matrix.cpp test_Bounds.cpp)

#find_package(GTest REQUIRED)

target_link_libraries(core_test PRIVATE spatiumgl GTest::gtest GTest::gtest_main)

add_test(NAME core_test COMMAND $<TARGET_FILE:core_test>)
