#pragma once
#include "matrix.hpp"
#include <fstream>
#include <iostream>

class Solver {
public:
  Solver() = delete;
  Solver(std::unique_ptr<Matrix> matrix) : matrix_(std::move(matrix)) {}
  Solver(Solver const &) = delete;
  Solver(Solver &&) noexcept = default;
  Solver &operator=(Solver const &) = delete;
  Solver &operator=(Solver &&) noexcept = default;
  ~Solver() = default;

public:
  void inputGraph(bool isFromFile, const std::string &filename) {
    std::ifstream fin(filename);
    std::istream &input = isFromFile ? fin : std::cin;
    size_t node_from, node_to;
    auto &matrix = *matrix_;
    while (input >> node_from >> node_to) {
      matrix(node_from, node_to) = 1;
    }
  }

  void outputPageRank(bool isToFile, const std::string &filename) {
    ;
    ;
  }

public:
  void calculate(size_t iters) {
    ;
    ;
  }

private:
  std::unique_ptr<Matrix> matrix_;
};
