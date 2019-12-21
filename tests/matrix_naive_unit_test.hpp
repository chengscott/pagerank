#pragma once
#include "gtest/gtest.h"

#include "matrix_naive.hpp"

namespace {

using size_type = MatrixNaive::size_type;

TEST(MatrixNaiveZero, CtorZero) {
  const MatrixNaive large(1000, 1000);
  for (size_type i = 0; i < 3; ++i) {
    for (size_type j = 0; j < 3; ++j) {
      ASSERT_DOUBLE_EQ(0., large(i, j));
    }
  }
}

TEST(MatrixNaiveZero, CopyCtorZero) {
  const MatrixNaive large(1000, 1000);
  const MatrixNaive another_large(large);
  for (size_type i = 0; i < 3; ++i) {
    for (size_type j = 0; j < 3; ++j) {
      ASSERT_DOUBLE_EQ(0., another_large(i, j));
    }
  }
}

TEST(MatrixNaiveSizeTest, SquareMatrix) {
  const MatrixNaive one_one(1, 1);
  EXPECT_EQ(one_one.nrow(), 1);
  EXPECT_EQ(one_one.ncol(), 1);
  MatrixNaive two_two(2, 2);
  EXPECT_EQ(two_two.nrow(), 2);
  EXPECT_EQ(two_two.ncol(), 2);
  const MatrixNaive large(1000, 1000);
  EXPECT_EQ(large.nrow(), 1000);
  EXPECT_EQ(large.ncol(), 1000);
}

TEST(MatrixNaiveSizeTest, ColVector) {
  MatrixNaive two_two(3, 1);
  EXPECT_EQ(two_two.nrow(), 3);
  EXPECT_EQ(two_two.ncol(), 1);
  const MatrixNaive large(1000, 1);
  EXPECT_EQ(large.nrow(), 1000);
  EXPECT_EQ(large.ncol(), 1);
}

TEST(MatrixNaiveDistance, ExactEqual) {
  MatrixNaive small(3, 3);
  small(0, 0) = small(0, 1) = small(0, 2) = 0.;
  // EXPECT_EQ(small.nrow(), 1000);

  // EXPECT_EQ(small.nrow(), 1000);
  ;
  ;
}

} // namespace