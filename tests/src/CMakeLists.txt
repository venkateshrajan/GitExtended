cmake_minimum_required (VERSION 3.22)

include_directories(${GitExtended_SOURCE_DIR})
include_directories(${GitExtended_SOURCE_DIR}/libgitex/inc)

include (CTest)
find_package(GTest CONFIG REQUIRED)
add_executable(gitex_test ${SOURCES} tests.cpp)

target_link_libraries(gitex_test PRIVATE libgitex GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(gitex_test)
