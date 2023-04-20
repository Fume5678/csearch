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

#include "testmain.h"

#include <IndexStorage.h>

using namespace anezkasearch;
using namespace YAML;

TEST_CASE("Parsing config") {
  // TODO change absolute test_config path to relative path
  YAML::Node config = YAML::LoadFile("/home/fume/projects/cpp/anezkasearch/test/units/test_config.yaml");

  REQUIRE(config);
  REQUIRE(config["version"].as<std::string>() == "0.1");
  REQUIRE(config["indexer"]["source"].as<std::string>() == "postgres");
  REQUIRE(config["indexer"]["content"]["key_columns"].size() == 2);
  REQUIRE(config["indexer"]["content"]["key_columns"][0].as<std::string>() == "title");
  REQUIRE_FALSE(config["bad_tag"].IsDefined());
}

TEST_CASE("AppState loading"){
  YAML::Node config = YAML::LoadFile("/home/fume/projects/cpp/anezkasearch/test/units/test_config.yaml");

  // Id is parsed from config
  AppState<IntId> state(config);
  REQUIRE(state.GetConfig() != std::nullopt);
  REQUIRE(state.GetConfig() != std::nullopt);
  REQUIRE(state.GetConfig().value()["version"].as<std::string>() == "0.1");

  AppState<IntId> state2;
  REQUIRE(state2.GetConfig() == std::nullopt);
}

TEST_CASE("AppState owns indexStorage"){
  YAML::Node config = YAML::LoadFile("/home/fume/projects/cpp/anezkasearch/test/units/test_config.yaml");

  AppState<IntId> state(config);
  CHECK(state.GetConfig().value()["version"].as<std::string>() == "0.1");
  REQUIRE(state.GetWeakIndexStorage().use_count() == 1);
  REQUIRE(config["version"].as<std::string>() == "0.1");

  std::vector<int> vec;
  
}