#pragma once
#include <cstddef>

class Matrix {
public:
  virtual ~Matrix() = default;
  virtual double operator()(size_t i, size_t j) const = 0;
  virtual double &operator()(size_t i, size_t j) = 0;

public:
  friend Matrix multiply_naive(const Matrix &, const Matrix &);
  friend Matrix multiply_mkl(const Matrix &, const Matrix &);
};