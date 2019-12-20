#pragma once
#include "matrix_naive.hpp"
#include <fstream>
#include <iostream>

class Solver {
public:
  using size_type = std::size_t;

public:
  explicit Solver(size_type nodes) : nodes_(nodes) {
    matrix_ = std::make_unique<MatrixNaive>(nodes, nodes);
    rank_ = std::make_unique<MatrixNaive>(nodes, 1);
    // initialize rank vector
    auto &rank = *rank_;
    const double rank_init = 1. / nodes;
    for (size_type i = 0; i < nodes; ++i) {
      rank(i, 0) = rank_init;
    }
  }
  Solver(Solver const &) = delete;
  Solver(Solver &&) noexcept = default;
  Solver &operator=(Solver const &) = delete;
  Solver &operator=(Solver &&) noexcept = default;
  ~Solver() = default;

public:
  void inputGraph(bool isFromFile, const std::string &filename) {
    std::ifstream fin(filename);
    std::istream &input = isFromFile ? fin : std::cin;
    auto &matrix = *matrix_;
    std::unique_ptr<size_type[]> out_degree(new size_type[nodes_]);
    // if i -> j, then matrix(j, i) = 1 / out_degree[i]
    size_type i, j;
    while (input >> i >> j) {
      matrix(j, i) = 1.;
      ++out_degree[i];
    }
    for (j = 0; j < nodes_; ++j) {
      for (i = 0; i < nodes_; ++i) {
        matrix(j, i) /= out_degree[i];
      }
    }
  }

  void calculate(size_type iters) {
    auto &matrix = *matrix_, &rank = *rank_;
    for (size_type it = 0; it < iters; ++it) {
      rank = matrix * rank;
    }
  }

  void outputPageRank(bool /*isToFile*/, const std::string & /*filename*/) {
    ;
    ;
  }

private:
  std::unique_ptr<MatrixNaive> matrix_, rank_;
  size_type nodes_;
};
