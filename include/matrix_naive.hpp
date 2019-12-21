#pragma once
#include <iomanip>
#include <iostream>
#include <vector>

class MatrixNaive {
public:
  using size_type = std::size_t;
  using value_type = double;

public:
  MatrixNaive(size_type nrow, size_type ncol)
      : nrow_(nrow), ncol_(ncol), data_(nrow * ncol) {
    data_.assign(data_.size(), 0.);
  }
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

  friend value_type distance(const MatrixNaive &lhs, const MatrixNaive &rhs) {
    // assert(lhs.nrow_ == rhs.nrow_ && lhs.ncol_ == rhs.ncol_);
    value_type ret = 0.;
    const auto nrow = lhs.nrow_, ncol = rhs.ncol_;
    for (size_type i = 0; i < nrow; ++i) {
      for (size_type j = 0; j < ncol; ++j) {
        auto dx = lhs(i, j) - rhs(i, j);
        ret += dx * dx;
      }
    }
    return ret;
  }

  friend std::ostream &operator<<(std::ostream &out, const MatrixNaive &rhs) {
    const auto nrow = rhs.nrow_, ncol = rhs.ncol_;
    out << std::fixed << std::setprecision(5);
    for (size_type i = 0; i < nrow; ++i) {
      out << rhs(i, 0);
      for (size_type j = 1; j < ncol; ++j) {
        out << ' ' << rhs(i, j);
      }
      out << std::endl;
    }
    return out;
  }

private:
  void multiply(const MatrixNaive &rhs, MatrixNaive &result) const {
    // assert(ncol_ == result.nrow_);
    const size_type nrow = nrow_, nk = ncol_, ncol = rhs.ncol_;
    for (size_type i = 0; i < nrow; ++i) {
      for (size_type j = 0; j < ncol; ++j) {
        for (size_type k = 0; k < nk; ++k) {
          result(i, j) += operator()(i, k) * rhs(k, j);
        }
      }
    }
  }

private:
  size_type nrow_, ncol_;
  std::vector<value_type> data_;
};