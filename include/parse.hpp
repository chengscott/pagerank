#pragma once
#include "argparse.hpp"
#include "logger.hpp"

static ArgumentParser argparse(int argc, const char **argv) {
  ArgumentParser parser("PageRank");
  // algorithm arguments
  parser.add_argument("-n", "--nodes", "Number of nodes", true);
  parser.add_argument("-t", "--iteration", "Update iterations", false);
  parser.add_argument("-i", "--input", "Input filename", false);
  parser.add_argument("-o", "--output", "Output filename", false);
  parser.parse(argc, argv);
  return parser;
}

struct Argument {
  size_t iters, nodes;
  bool isFromFile, isToFile;
  std::string inFilename, outFilename;
};

static Argument retrieve(ArgumentParser &parser) {
  Argument arg;
  arg.iters = parser.exists("iteration") ? parser.get<size_t>("iteration") : 0;
  arg.nodes = parser.get<size_t>("nodes");
  arg.isFromFile = parser.exists("input");
  arg.isToFile = parser.exists("output");
  arg.inFilename = parser.get<std::string>("input");
  arg.outFilename = parser.get<std::string>("output");
  return arg;
}

static void log_arg(const Argument &arg) {
  auto &logger = Logger::getInstance();
  logger.logInfo("Number of nodes: ", arg.nodes);
  logger.logInfo("Number of iterations: ", arg.iters);
  if (arg.isFromFile) {
    logger.logInfo("Input from file: ", arg.inFilename);
  } else {
    logger.logInfo("Input from stdin");
  }
  if (arg.isToFile) {
    logger.logInfo("Output to file: ", arg.outFilename);
  } else {
    logger.logInfo("Output to stdout");
  }
  logger.logInfo("\n");
}