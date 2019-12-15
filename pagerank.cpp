#include "parse.hpp"

int main(int argc, const char **argv) {
  // parse arguments
  ArgumentParser parser = parse(argc, argv);
  size_t iters = parse_iters(parser);
  auto matrix = parse_matrix(parser);

  // solve PageRank
  Solver solver(std::move(matrix));
  solver.inputGraph(parser.exists("input"), parser.get<std::string>("input"));
  solver.calculate(iters);
  solver.outputPageRank(parser.exists("output"),
                        parser.get<std::string>("output"));
}