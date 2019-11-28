#include "graph.hpp"
#include "graph_builder.hpp"
#include "solver.hpp"

int main(int argc, char **argv) {
  auto &&graph = GraphBuilder(GraphType::Dense)
                     .withInputFormat(GraphType::Sparse)
                     .withProvider(MatrixProvider::Naive)
                     .build();
  Solver solver(std::move(graph));
}