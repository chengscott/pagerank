# PageRank

[![Build Status](https://travis-ci.org/chengscott/pagerank.svg?branch=master)](https://travis-ci.org/chengscott/pagerank)

## Introduction

This project aims to provide an implementation of PageRank algorithm in partial fulfillment of the requirement of NSD (Numerical Software Design) course.

PageRank was an algorithm used by Google to rank the importance of resulting web pages from their search engine. PageRank simulates Web surfers, starting at a random page and randomly browsing around, would tend to converge and aggregated, and this process is allowed to iterate many times.

The algorithm accepts a directed graph as the input, where vertices and edges represents web pages and links between, respectively; It outputs PageRank scores for each vertices, which represents the likelihood of a page being visited by random web surfing.

## Build

```shell
mkdir build
cd build
cmake ..
make
```

## Run

`pagerank --help` to show all arguements.

### Run Example

```shell
./pagerank -n 3 -i examples/small.txt -o result.txt
```

Hint: use `-t 100` to specify `100` iterations; otherwise iterates until convergence.

### Run Tests (For Developer)

```shell
tests/test_runner
```

## Specs

- Input from either stdin or file
- Operations perform via dense graph operations.
- Output to either stdout or file
- Node numbers increment from zero.

## Reference

- [NSD course](https://github.com/yungyuc/nsd)
- [PageRank Algorithm](https://en.wikipedia.org/wiki/PageRank)