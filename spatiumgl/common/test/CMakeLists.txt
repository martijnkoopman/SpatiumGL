project(common_test LANGUAGES CXX)

add_executable(${PROJECT_NAME} test_Vector2.cpp test_Vector3.cpp test_Vector4.cpp test_Vector.cpp test_Matrix2.cpp test_Matrix3.cpp test_Matrix4.cpp test_Matrix.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE spatiumgl GTest::GTest GTest::Main)

add_test(unit ${PROJECT_NAME})