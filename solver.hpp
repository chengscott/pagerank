#pragma once
#include "graph.hpp"
#include <memory>

class Solver {
public:
  static Solver &getInstance() {
    static Solver instance;
    return instance;
  }
  Solver() = default;
  ~Solver() = default;
  Solver(Solver const &) = delete;
  Solver(Solver &&) = delete;
  Solver &operator=(Solver const &) = delete;
  Solver &operator=(Solver &&) = delete;

public:
  void set_graph(std::unique_ptr<Graph> &graph) { graph_ = std::move(graph); }

private:
  std::unique_ptr<Graph> graph_ = nullptr;
};