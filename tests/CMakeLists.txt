cmake_minimum_required(VERSION 3.0)
project(PageRankTests LANGUAGES CXX)

set(TEST_BIN test_runner)

add_executable(${TEST_BIN} test_runner.cpp)
target_include_directories(${TEST_BIN} PRIVATE ../include)
target_link_libraries(${TEST_BIN} gtest gtest_main)