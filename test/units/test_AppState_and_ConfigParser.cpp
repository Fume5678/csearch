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
  YAML::Node config = YAML::LoadFile("./test_config.yaml");

  REQUIRE(config);
  REQUIRE(config["version"].as<std::string>() == "0.1");
  REQUIRE(config["indexer"]["source"].as<std::string>() == "postgres");
  REQUIRE(config["indexer"]["content"]["key_columns"].size() == 2);
  REQUIRE(config["indexer"]["content"]["key_columns"][0].as<std::string>() == "title");
  REQUIRE_FALSE(config["bad_tag"].IsDefined());
}

TEST_CASE("AppState owns command line args"){
  cxxopts::Options options = GetOptions();
  cxxopts::ParseResult res = options.parse(ARGC, ARGV);
  auto file = res["file"].as<std::string>();
  REQUIRE(file == "somefile.yml");

  AppState<IntInd> state(res);
  REQUIRE(state.GetArgs()["log-output"].count() == 1);

  // Id is parsed from config
}

TEST_CASE("AppState owns indexStorage"){
  cxxopts::Options options = GetOptions();
  cxxopts::ParseResult res = options.parse(ARGC, ARGV);
  YAML::Node config = YAML::LoadFile("./test_config.yaml");
  AppState<IntInd> state(res, config);
  CHECK(state.GetConfig()["version"].as<std::string>() == "0.1");
  REQUIRE(state.GetWeakIndexStorage().use_count() == 1);
  REQUIRE(config["version"].as<std::string>() == "0.1");

  std::vector<int> vec;
}

constexpr bool is_int_index_type(auto state){
  return std::same_as<typename decltype(state)::index_type, IntInd>;
}

TEST_CASE("AppState getting index type"){
  cxxopts::Options options = GetOptions();
  cxxopts::ParseResult res = options.parse(ARGC, ARGV);
  YAML::Node config = YAML::LoadFile("./test_config.yaml");
  AppState<IntInd> state(res, config);
  REQUIRE(is_int_index_type(state));

  AppState<StringInd> state2(res, config);
  REQUIRE(!is_int_index_type(state2));
}