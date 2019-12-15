#pragma once
#include "matrix.hpp"
#include <vector>

class MatrixNaive final : public Matrix {
public:
  MatrixNaive(size_t nrow, size_t ncol)
      : nrow_(nrow), ncol_(ncol), data_(nrow * ncol) {}
  MatrixNaive(const MatrixNaive &) = default;
  MatrixNaive(MatrixNaive &&) noexcept = default;
  MatrixNaive &operator=(const MatrixNaive &) = default;
  MatrixNaive &operator=(MatrixNaive &&) noexcept = default;
  ~MatrixNaive() override = default;

   double operator()(size_t i, size_t j) const override {
    if (i >= nrow_ || j >= ncol_) {
      throw std::out_of_range("");
    }
    return data_[i * ncol_ + j];
  }
   double &operator()(size_t i, size_t j) override {
    if (i >= nrow_ || j >= ncol_) {
      throw std::out_of_range("");
    }
    return data_[i * ncol_ + j];
  }

  constexpr bool operator==(const MatrixNaive &rhs) const {
    return nrow_ == rhs.nrow_ && ncol_ == rhs.ncol_ && data_ == rhs.data_;
  }
  constexpr bool operator!=(const MatrixNaive &rhs) const {
    return !(*this == rhs);
  }

private:
  size_t nrow_, ncol_;
  std::vector<double> data_;
};