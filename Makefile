CXX ?= g++
CXXFLAGS += -std=c++17 -O3 -march=native #-flto
CXXFLAGS += -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wpedantic
CXXFLAGS += -Wunused -Wsign-conversion -Wdouble-promotion
CXXFLAGS += -Iinclude
BIN = pagerank
SRCS = pagerank.cpp
DEPS = $(shell find include -name *.hpp)
OBJS = $(SRCS:.cpp=) $(DEPS:.hpp=)
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