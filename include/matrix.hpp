#pragma once
#include "option.hpp"
#include <iomanip>
#include <iostream>
#include <vector>
#ifdef USE_MKL
#include <mkl.h>
#include <mkl_lapacke.h>
#endif

class Matrix {
public:
  using size_type = std::size_t;
  using value_type = double;

public:
  Matrix(size_type nrow, size_type ncol)
      : nrow_(nrow), ncol_(ncol), data_(nrow * ncol) {
    data_.assign(data_.size(), 0.);
  }
  Matrix(const Matrix &) = default;
  Matrix(Matrix &&) noexcept = default;
  Matrix &operator=(const Matrix &) = default;
  Matrix &operator=(Matrix &&) noexcept = default;
  ~Matrix() = default;

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

  constexpr bool operator==(const Matrix &rhs) const {
    return nrow_ == rhs.nrow_ && ncol_ == rhs.ncol_ && data_ == rhs.data_;
  }
  constexpr bool operator!=(const Matrix &rhs) const { return !(*this == rhs); }

  Matrix operator*(const Matrix &rhs) const {
    Matrix ret(nrow_, rhs.ncol_);
    if constexpr (BuildOption::MatrixGemm ==
                  BuildOption::MatrixGemmType::Naive) {
      multiply_naive(rhs, ret);
    } else if constexpr (BuildOption::MatrixGemm ==
                         BuildOption::MatrixGemmType::NaiveTiling) {
      multiply_naive_tiling(rhs, ret);
    } else if constexpr (BuildOption::MatrixGemm ==
                         BuildOption::MatrixGemmType::MKL) {
      multiply_mkl(rhs, ret);
    }
    return ret;
  }

  friend value_type distance(const Matrix &lhs, const Matrix &rhs) {
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

  friend std::ostream &operator<<(std::ostream &out, const Matrix &rhs) {
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
  void multiply_naive(const Matrix &rhs, Matrix &result) const {
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

  void multiply_naive_tiling(const Matrix &rhs, Matrix &result) const {
    const constexpr size_t tile = 16;
    const size_t m = nrow_, n = ncol_, l = rhs.ncol_;
    for (size_t it = 0; it < m; it += tile) {
      for (size_t jt = 0; jt < l; jt += tile) {
        for (size_t kt = 0; kt < n; kt += tile) {
          const size_t ti = std::min(it + tile, m), tj = std::min(jt + tile, l),
                       tk = std::min(kt + tile, n);
          // block multiplication
          for (size_t i = it; i < ti; ++i) {
            for (size_t j = jt; j < tj; ++j) {
              double sum = 0;
              for (size_t k = kt; k < tk; ++k) {
                sum += operator()(i, k) * rhs(k, j);
              }
              result(i, j) += sum;
            }
          }
        }
      }
    }
  }

  void multiply_mkl(const Matrix &rhs, Matrix &result) const {
#ifdef USE_MKL
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, nrow_, rhs.ncol(),
                ncol_, 1., data_.data(), ncol_, rhs.data_.data(), rhs.ncol(),
                1., result.data_.data(), result.ncol());
#endif
  }

private:
  size_type nrow_, ncol_;
  std::vector<value_type> data_;
};