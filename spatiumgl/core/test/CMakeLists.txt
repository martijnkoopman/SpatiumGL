project(core_test LANGUAGES CXX)

add_executable(core_test test_Vector2.cpp test_Vector3.cpp test_Vector4.cpp test_Vector.cpp test_Matrix2.cpp test_Matrix3.cpp test_Matrix4.cpp test_Matrix.cpp test_Bounds.cpp)
set_target_properties(core_test PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_link_libraries(core_test PRIVATE spatiumgl GTest::gtest GTest::gtest_main)

add_test(NAME core_test COMMAND $<TARGET_FILE:core_test>)
