#pragma once
#include "graph.hpp"
#include <memory>

class Solver {
public:
  Solver(std::unique_ptr<Graph> graph = nullptr) : graph_{std::move(graph)} {};
  ~Solver() = default;
  Solver(Solver const &) = delete;
  Solver(Solver &&) noexcept = default;
  Solver &operator=(Solver const &) = delete;
  Solver &operator=(Solver &&) noexcept = default;

private:
  std::unique_ptr<Graph> graph_;
};