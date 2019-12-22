#include "gtest/gtest.h"

#include "logger_test.hpp"
#include "matrix_mkl_test.hpp"
#include "matrix_naive_test.hpp"
#include "solver_test.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}