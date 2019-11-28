#pragma once
#include "graph.hpp"

template <size_t currentSet> class GraphBuilderEngine {
private:
  template <size_t> friend class GraphBuilderEngine;
  enum Component : size_t { InputFormat = 1U << 0, Provider = 1U << 1 };

public:
  GraphBuilderEngine() = delete;
  GraphBuilderEngine(GraphType gt) : graph_type_{gt} {}
  GraphBuilderEngine(const GraphBuilderEngine &) = default;
  GraphBuilderEngine(GraphBuilderEngine &&) noexcept = default;
  GraphBuilderEngine &operator=(const GraphBuilderEngine &) = default;
  GraphBuilderEngine &operator=(GraphBuilderEngine &&) noexcept = default;
  ~GraphBuilderEngine() = default;

public:
  constexpr GraphBuilderEngine<currentSet | Component::InputFormat>
  withInputFormat(GraphType gt) {
    auto &&nextBuilder = *this;
    nextBuilder.input_format_ = gt;
    return nextBuilder;
  }

  constexpr GraphBuilderEngine<currentSet | Component::Provider>
  withProvider(MatrixProvider mp) {
    auto &&nextBuilder = *this;
    nextBuilder.matrix_provider_ = mp;
    return nextBuilder;
  }

  std::unique_ptr<Graph> build() const {
    constexpr const auto allSet = Component::InputFormat | Component::Provider;
    static_assert((currentSet ^ allSet) == 0, "Build is not completed.");
    // RAII: create and own the graph
    std::unique_ptr<Graph> graph;
    switch (graph_type_) {
    // case GraphType::Sparse:
    // graph = std::make_unique<SparseGraph>();
    case GraphType::Dense:
      graph = std::make_unique<DenseGraph>();
      break;
    default:
      throw "Not Implemented.";
    }
    // RAII: create and own the matrix
    switch (matrix_provider_) {
    case MatrixProvider::Naive:
      /* code */
      break;
    default:
      throw "Not Implemented.";
    }
    graph->input_format_ = input_format_;
    return graph;
  }

private:
  template <size_t otherSet>
  GraphBuilderEngine(GraphBuilderEngine<otherSet> rhs) {
    // copy and swap idiom; enabled by copy elision
    std::swap(graph_type_, rhs.graph_type_);
    std::swap(input_format_, rhs.input_format_);
    std::swap(matrix_provider_, rhs.matrix_provider_);
  }
  template <size_t otherSet>
  GraphBuilderEngine(GraphBuilderEngine<otherSet> &&rhs) noexcept {
    std::swap(graph_type_, rhs.graph_type_);
    std::swap(input_format_, rhs.input_format_);
    std::swap(matrix_provider_, rhs.matrix_provider_);
  }

private:
  GraphType graph_type_, input_format_;
  MatrixProvider matrix_provider_;
};

using GraphBuilder = GraphBuilderEngine<0>;
