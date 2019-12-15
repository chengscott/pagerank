#pragma once
#include "argparse.hpp"
#include "matrix_mkl.hpp"
#include "matrix_naive.hpp"
#include "solver.hpp"
#include <variant>

static ArgumentParser parse(int argc, const char **argv) {
  ArgumentParser parser("PageRank");
  // algorithm arguments
  parser.add_argument("-i", "--input", "Input filename", false);
  parser.add_argument("-o", "--output", "Output filename", false);
  parser.add_argument("-it", "--iteration", "Update iterations", false);
  parser.add_argument("-n", "--nodes", "Number of nodes", true);
  // implementation arguments
  parser.add_argument("-m", "--matrix_impl", "Matrix implementation", false);
  parser.parse(argc, argv);
  return parser;
}

static size_t parse_iters(ArgumentParser &parser) {
  constexpr const size_t iters_default = 1000;
  return parser.exists("iteration") ? iters_default
                                    : parser.get<size_t>("iteration");
}

static std::unique_ptr<Matrix> parse_matrix(ArgumentParser &parser) {
  const auto &nodes = parser.get<size_t>("nodes");
  if (parser.exists("matrix_impl")) {
    const auto &matrix_impl = parser.get<std::string>("matrix_impl");
    if (matrix_impl == "naive") {
      return std::make_unique<MatrixNaive>(nodes, nodes);
    } else if (matrix_impl == "mkl") {
      return std::make_unique<MatrixMKL>(nodes, nodes);
    } else {
      parser.print_help();
      throw std::logic_error("");
    }
  } else {
    return std::make_unique<MatrixNaive>(nodes, nodes);
  }
}