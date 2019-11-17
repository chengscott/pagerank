#include "graph.hpp"
#include "solver.hpp"

int main(int argc, char **argv) {
  // TODO: parse argc, argv
  auto &solver = Solver::getInstance();
  std::unique_ptr<Graph> graph(new DenseGraph);
  graph->set_input_format(Graph::GraphType::Sparse);
  solver.set_graph(graph);
}