#pragma once
#include "gtest/gtest.h"

#include "logger.hpp"

namespace {

TEST(LoggerMessage, LogInfoOne) {
  testing::internal::CaptureStdout();
  testing::internal::CaptureStderr();

  auto &logger = Logger::getInstance();
  logger.logInfo("test");

  auto log_stdout = testing::internal::GetCapturedStdout();
  auto log_stderr = testing::internal::GetCapturedStderr();

  EXPECT_EQ(log_stdout, std::string("test\n"));
  EXPECT_EQ(log_stderr, std::string(""));
}

TEST(LoggerMessage, LogInfoMultiple) {
  testing::internal::CaptureStdout();
  testing::internal::CaptureStderr();

  auto &logger = Logger::getInstance();
  logger.logInfo(std::string("test"), 1, '2', "3", "45");

  auto log_stdout = testing::internal::GetCapturedStdout();
  auto log_stderr = testing::internal::GetCapturedStderr();

  EXPECT_EQ(log_stdout, std::string("test12345\n"));
  EXPECT_EQ(log_stderr, std::string(""));
}

TEST(LoggerMessage, LogError) {
  testing::internal::CaptureStdout();
  testing::internal::CaptureStderr();

  auto &logger = Logger::getInstance();
  logger.logError(std::string("test"), 1, '2', "3", "45");

  auto log_stdout = testing::internal::GetCapturedStdout();
  auto log_stderr = testing::internal::GetCapturedStderr();

  EXPECT_EQ(log_stdout, std::string(""));
  EXPECT_EQ(log_stderr, std::string("test12345\n"));
}

} // namespace