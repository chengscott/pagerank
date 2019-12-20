#pragma once
#include <vector>

class MatrixNaive {
public:
  using size_type = std::size_t;
  using value_type = double;

public:
  MatrixNaive(size_type nrow, size_type ncol)
      : nrow_(nrow), ncol_(ncol), data_(nrow * ncol) {}
  MatrixNaive(const MatrixNaive &) = default;
  MatrixNaive(MatrixNaive &&) noexcept = default;
  MatrixNaive &operator=(const MatrixNaive &) = default;
  MatrixNaive &operator=(MatrixNaive &&) noexcept = default;
  ~MatrixNaive() = default;

  value_type operator()(size_type i, size_type j) const {
    if (i >= nrow_ || j >= ncol_) {
      throw std::out_of_range("");
    }
    return data_[i * ncol_ + j];
  }
  value_type &operator()(size_type i, size_type j) {
    if (i >= nrow_ || j >= ncol_) {
      throw std::out_of_range("");
    }
    return data_[i * ncol_ + j];
  }

  constexpr size_type nrow() const { return nrow_; }
  constexpr size_type ncol() const { return ncol_; }

  constexpr bool operator==(const MatrixNaive &rhs) const {
    return nrow_ == rhs.nrow_ && ncol_ == rhs.ncol_ && data_ == rhs.data_;
  }
  constexpr bool operator!=(const MatrixNaive &rhs) const {
    return !(*this == rhs);
  }

  MatrixNaive operator*(const MatrixNaive &rhs) const {
    MatrixNaive ret(nrow_, rhs.ncol_);
    multiply(rhs, ret);
    return ret;
  }

private:
  void multiply(const MatrixNaive &rhs, MatrixNaive &result) const {
    // assert(ncol_ == result.nrow_);
    const size_type nrow = nrow_, nk = ncol_, ncol = rhs.ncol_;
    for (size_type i = 0; i < nrow; ++i) {
      for (size_type j = 0; j < ncol; ++j) {
        for (size_type k = 0; k < nk; ++k) {
          result(i, j) = operator()(i, k) * rhs(k, j);
        }
      }
    }
  }

private:
  size_type nrow_, ncol_;
  std::vector<value_type> data_;
};