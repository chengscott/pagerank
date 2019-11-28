CXX ?= g++
CXXFLAGS += -std=c++17 -O3 -Wall
BIN = pagerank
SRCS = pagerank.cpp
DEPS = graph.hpp matrix.hpp solver.hpp graph_builder.hpp
OBJS = $(SRCS:.cpp=)
OBJS += $(DEPS:.hpp=)
CHECKS = -checks=bugprone-*,clang-analyzer-*,modernize-*,performance-*,readability-*

.PHONY: $(BIN) format check clean
all: $(BIN)

$(BIN): $(SRCS) $(DEPS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

format:
	clang-format -i $(SRCS) $(DEPS)

check:
	clang-tidy $(SRCS) $(DEPS) $(CHECKS) -- $(CXXFLAGS)

clean:
	rm -f $(OBJS)