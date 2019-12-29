#pragma once
#include "gtest/gtest.h"

#include "matrix.hpp"

namespace {

using size_type = Matrix::size_type;

TEST(MatrixZero, CtorZero) {
  const Matrix large(1000, 1000);
  for (size_type i = 0; i < 3; ++i) {
    for (size_type j = 0; j < 3; ++j) {
      ASSERT_DOUBLE_EQ(0., large(i, j));
    }
  }
}

TEST(MatrixZero, CopyCtorZero) {
  const Matrix large(1000, 1000);
  const Matrix another_large(large);
  for (size_type i = 0; i < 3; ++i) {
    for (size_type j = 0; j < 3; ++j) {
      ASSERT_DOUBLE_EQ(0., another_large(i, j));
    }
  }
}

TEST(MatrixSizeTest, SquareMatrix) {
  const Matrix one_one(1, 1);
  EXPECT_EQ(one_one.nrow(), 1);
  EXPECT_EQ(one_one.ncol(), 1);
  Matrix two_two(2, 2);
  EXPECT_EQ(two_two.nrow(), 2);
  EXPECT_EQ(two_two.ncol(), 2);
  const Matrix large(1000, 1000);
  EXPECT_EQ(large.nrow(), 1000);
  EXPECT_EQ(large.ncol(), 1000);
}

TEST(MatrixSizeTest, ColVector) {
  Matrix two_two(3, 1);
  EXPECT_EQ(two_two.nrow(), 3);
  EXPECT_EQ(two_two.ncol(), 1);
  const Matrix large(1000, 1);
  EXPECT_EQ(large.nrow(), 1000);
  EXPECT_EQ(large.ncol(), 1);
}

TEST(MatrixDistance, ExactEqual) {
  Matrix id(3, 3), small(3, 3);
  id(0, 0) = id(1, 1) = id(2, 2) = 1.;
  small(0, 0) = 1.;
  small(0, 1) = 2.;
  small(0, 2) = 3.;
  small(1, 0) = 4.;
  small(1, 1) = 5.;
  small(1, 2) = 6.;
  small(2, 0) = 7.;
  small(2, 1) = 8.;
  small(2, 2) = 9.;
  ASSERT_DOUBLE_EQ(distance(small, small), 0.);
  ASSERT_DOUBLE_EQ(distance(id, id), 0.);
}

TEST(MatrixMultiply, Identity) {
  Matrix id(3, 3), small(3, 3);
  id(0, 0) = id(1, 1) = id(2, 2) = 1.;
  small(0, 0) = 1.;
  small(0, 1) = 2.;
  small(0, 2) = 3.;
  small(1, 0) = 4.;
  small(1, 1) = 5.;
  small(1, 2) = 6.;
  small(1, 0) = 7.;
  small(1, 1) = 8.;
  small(1, 2) = 9.;
  ASSERT_DOUBLE_EQ(distance(small, small * id), 0.);
  ASSERT_DOUBLE_EQ(distance(small, small * id * id * id), 0.);
  ASSERT_DOUBLE_EQ(distance(small, id * small), 0.);
  ASSERT_DOUBLE_EQ(distance(small * id, id * small), 0.);
}

TEST(MatrixMultiply, Square) {
  Matrix ma(3, 3), mb(3, 3), result(3, 3);
  ma(0, 0) = mb(2, 2) = 1.;
  ma(0, 1) = mb(2, 1) = 2.;
  ma(0, 2) = mb(2, 0) = 3.;
  ma(1, 0) = mb(1, 2) = 4.;
  ma(1, 1) = mb(1, 1) = 5.;
  ma(1, 2) = mb(1, 0) = 6.;
  ma(2, 0) = mb(0, 2) = 7.;
  ma(2, 1) = mb(0, 1) = 8.;
  ma(2, 2) = mb(0, 0) = 9.;
  result(0, 0) = 30.;
  result(0, 1) = 24.;
  result(0, 2) = 18.;
  result(1, 0) = 84.;
  result(1, 1) = 69.;
  result(1, 2) = 54.;
  result(2, 0) = 138.;
  result(2, 1) = 114.;
  result(2, 2) = 90.;
  ASSERT_DOUBLE_EQ(distance(ma * mb, result), 0.);
}

TEST(MatrixMultiply, MatrixVector) {
  Matrix small(3, 3), vec(3, 1), result(3, 1);
  small(0, 0) = 1.;
  small(0, 1) = 2.;
  small(0, 2) = 3.;
  small(1, 0) = 4.;
  small(1, 1) = 5.;
  small(1, 2) = 6.;
  small(2, 0) = 7.;
  small(2, 1) = 8.;
  small(2, 2) = 9.;
  vec(0, 0) = 10.;
  vec(1, 0) = 11.;
  vec(2, 0) = 12.;
  result(0, 0) = 68.;
  result(1, 0) = 167.;
  result(2, 0) = 266.;
  ASSERT_DOUBLE_EQ(distance(small * vec, result), 0.);
}

} // namespace