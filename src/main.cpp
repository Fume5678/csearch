//
// Created by fume on 06.03.23.
//
#include <vector>
#include <ranges>
#include <fmt/core.h>
#include <cppcoro/generator.hpp>
#include <AppState.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Log.h>

int main() {
  plog::RollingFileAppender<plog::CsvFormatter> fileAppender("log.csv", 8000, 1);
  plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::info, &fileAppender).addAppender(&consoleAppender);

  anezkasearch::AppState state;

  LOGI << "Hello, world!";

  return 0;
}