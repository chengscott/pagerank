cmake_minimum_required(VERSION 3.0)
project(PageRank LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(TARGET_BIN pagerank)

option(USE_CLANG_TIDY "use clang-tidy" OFF)

add_executable(${TARGET_BIN} pagerank.cpp)
target_include_directories(${TARGET_BIN} PRIVATE include)
target_compile_options(${TARGET_BIN} PRIVATE  -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic -Wunused -Wsign-conversion -Wdouble-promotion)

add_subdirectory(third_party/googletest)
add_subdirectory(tests)