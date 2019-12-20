#pragma once
#include <cstddef>

class MatrixMKL {
public:
  MatrixMKL(size_t /*nrow*/, size_t /*ncol*/) {}

  double operator()(size_t /*i*/, size_t /*j*/) const { return dummy_; };
  double &operator()(size_t /*i*/, size_t /*j*/) { return dummy_; };

  size_t nrow() const { return 0; }
  size_t ncol() const { return 0; }

private:
  double dummy_;
};