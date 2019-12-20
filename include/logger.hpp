#pragma once
#include <iostream>

class Logger {
public:
  static Logger &getInstance() {
    static Logger instance;
    return instance;
  }
  Logger() = default;
  ~Logger() = default;
  Logger(Logger const &) = delete;
  Logger(Logger &&) = delete;
  Logger &operator=(Logger const &) = delete;
  Logger &operator=(Logger &&) = delete;

public:
  template <typename... Args> void logInfo(Args &&... args) {
    (std::cout << ... << std::forward<Args>(args)) << std::endl;
  }

  template <typename... Args> void logError(Args &&... args) {
    (std::cerr << ... << std::forward<Args>(args)) << std::endl;
  }
};