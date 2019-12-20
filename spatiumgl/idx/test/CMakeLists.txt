project(idx_test LANGUAGES CXX)

add_executable(idx_test test_Tree.cpp)
set_target_properties(idx_test PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_link_libraries(idx_test PRIVATE spatiumgl GTest::gtest GTest::gtest_main)

add_test(NAME idx_test COMMAND $<TARGET_FILE:idx_test>)
