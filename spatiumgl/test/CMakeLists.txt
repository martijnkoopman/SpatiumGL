cmake_minimum_required(VERSION 3.14)

PROJECT(unit_tests LANGUAGES CXX)

find_package(GTest REQUIRED)

# Create executable
add_executable(${PROJECT_NAME} test_Vector.cpp test_Matrix.cpp)

# Link dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE spatiumgl GTest::GTest GTest::Main)

add_test(unit ${PROJECT_NAME})