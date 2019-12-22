cmake_minimum_required(VERSION 3.0)
project(PageRank LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(TARGET_BIN pagerank)

# Main program
add_executable(${TARGET_BIN} pagerank.cpp)
target_include_directories(${TARGET_BIN} PRIVATE include)

# argparse library
# add_subdirectory(third_party/argparse)
target_include_directories(${TARGET_BIN} PRIVATE third_party/argparse)

# Warning flags
target_compile_options(${TARGET_BIN} PRIVATE -Wall
                                             -Wextra
                                             -Wshadow
                                             -Wnon-virtual-dtor
                                             -Wpedantic
                                             -Wunused
                                             -Wsign-conversion
                                             -Wdouble-promotion)

# Test program
add_subdirectory(third_party/googletest)
add_subdirectory(tests)

# clang-tidy
find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
    set_target_properties(${TARGET_BIN} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
else()
    message(FATAL_ERROR "clang-tidy is not found")
endif()