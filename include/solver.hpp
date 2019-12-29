#pragma once
#include "matrix.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

class Solver {
public:
  using size_type = Matrix::size_type;
  using value_type = Matrix::value_type;

public:
  explicit Solver(size_type nodes) : nodes_(nodes) {
    matrix_ = std::make_unique<Matrix>(nodes, nodes);
    rank_ = std::make_unique<Matrix>(nodes, 1);
    // initialize rank vector
    auto &rank = *rank_;
    const value_type rank_init = 1. / nodes;
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
    for (i = 0; i < nodes_; ++i) {
      out_degree[i] = 0;
    }
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

  void calculate_iters(size_type iters) {
    auto &matrix = *matrix_, &rank = *rank_;
    for (size_type it = 0; it < iters; ++it) {
      rank = matrix * rank;
    }
  }

  void calculate_eps(value_type eps = 1e-8) {
    auto &matrix = *matrix_, &rank = *rank_;
    size_type iters = 0;
    for (value_type cur_eps = 1.; cur_eps > eps; ++iters) {
      const auto &next_rank = matrix * rank;
      cur_eps = distance(rank, next_rank);
      std::cerr << std::scientific << cur_eps << std::endl;
      rank = next_rank;
    }
    std::cerr << iters << std::endl;
  }

  void outputPageRank(bool isToFile, const std::string &filename) {
    std::ofstream fout(filename);
    std::ostream &output = isToFile ? fout : std::cout;
    auto &rank = *rank_;
    output << std::fixed << std::setprecision(5) << std::endl;
    for (size_type i = 0; i < nodes_; ++i) {
      output << i << '\t' << rank(i, 0) << std::endl;
    }
  }

private:
  std::unique_ptr<Matrix> matrix_, rank_;
  size_type nodes_;
};
