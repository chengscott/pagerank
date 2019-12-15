#pragma once
#include "matrix.hpp"

class MatrixMKL final : public Matrix {
public:
  MatrixMKL(size_t /*nrow*/, size_t /*ncol*/) {}

  double operator()(size_t /*i*/, size_t /*j*/) const override {
    return dummy_;
  };
  double &operator()(size_t /*i*/, size_t /*j*/) override { return dummy_; };

private:
  double dummy_;
};