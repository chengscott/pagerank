#pragma once
#include "matrix.hpp"
#include <iostream>

class Graph {
public:
  Graph() = default;
  Graph(const Graph &) = default;
  Graph(Graph &&) noexcept = default;
  Graph &operator=(const Graph &) = default;
  Graph &operator=(Graph &&) noexcept = default;
  virtual ~Graph() = default;

public:
  enum class GraphType { None, Sparse, Dense };

  void set_input_format(const GraphType &gt) { input_format_ = gt; }

  friend std::istream &operator>>(std::istream &in, Graph &g) {
    return g.input(in);
  }

  friend std::ostream &operator<<(std::ostream &out, const Graph &g) {
    return g.output(out);
  }

protected:
  virtual std::istream &input(std::istream &in) = 0;
  virtual std::ostream &output(std::ostream &out) const = 0;

private:
  GraphType input_format_ = GraphType::None;
};

class DenseGraph : public Graph {
public:
protected:
  std::istream &input(std::istream &in) override { return in; }
  std::ostream &output(std::ostream &out) const override { return out; }

private:
  Matrix graph_;
};