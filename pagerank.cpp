#include "logger.hpp"
#include "parse.hpp"
#include "solver.hpp"

int main(int argc, const char **argv) {
  auto &logger = Logger::getInstance();
  logger.logInfo("PageRank", "\n");

  // parse arguments
  Argument arg;
  try {
    ArgumentParser parser = argparse(argc, argv);
    if (parser.is_help()) {
      return 0;
    }
    arg = retrieve(parser);
    log_arg(arg);
  } catch (const std::exception &ex) {
    logger.logError(ex.what());
    return 1;
  }

  // solve PageRank
  Solver solver(arg.nodes);
  solver.inputGraph(arg.isFromFile, arg.inFilename);
  if (arg.iters == 0) {
    solver.calculate_eps();
  } else {
    solver.calculate_iters(arg.iters);
  }
  solver.outputPageRank(arg.isToFile, arg.outFilename);
}