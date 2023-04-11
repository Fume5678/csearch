//
// Created by fume on 10.04.23.
//

#include <yaml-cpp/yaml.h>
#include <fstream>
#include <iostream>
#include <AppState.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Log.h>
#include "tests.h"

using namespace anezkasearch;
using namespace YAML;

TEST_CASE("Parsing config") {
  // TODO change absolute test_config path to relative path
  YAML::Node config = YAML::LoadFile("/home/fume/projects/cpp/anezkasearch/test/test_config.yaml");

  REQUIRE(config);
  REQUIRE(config["version"].as<std::string>() == "0.1");
  REQUIRE(config["indexer"]["source"].as<std::string>() == "postgres");
  REQUIRE(config["indexer"]["content"]["key_columns"].size() == 2);
  REQUIRE_FALSE(config["bad_tag"].IsDefined());
}

TEST_CASE("AppState loading"){
//  plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
//  plog::init(plog::info, &consoleAppender);

  AppState state;
  REQUIRE(state.GetConfig() == std::nullopt);

  REQUIRE_NOTHROW(state.LoadConfig("/home/fume/projects/cpp/anezkasearch/test/test_config.yaml"));
  REQUIRE(state.GetConfig() != std::nullopt);
  REQUIRE(state.GetConfig().value()["version"].as<std::string>() == "0.1");
}