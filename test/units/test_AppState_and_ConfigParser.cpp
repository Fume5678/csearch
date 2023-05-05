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
  AppState<IntInd> state(cxxopts::ParseResult(), config);
  REQUIRE(state.GetConfig() != std::nullopt);
  REQUIRE(state.GetConfig() != std::nullopt);
  REQUIRE(state.GetConfig().value()["version"].as<std::string>() == "0.1");

  AppState<IntInd> state2({cxxopts::ParseResult()});
  REQUIRE(state2.GetConfig() == std::nullopt);
}

TEST_CASE("AppState owns command line args"){
  cxxopts::Options options("AnezkaSearch", "One line description of MyProgram");
  options.add_options()
      ("f,file", "Path to config file", cxxopts::value<std::string>())
#ifdef linux
      ("log-output", "Path to config file", cxxopts::value<std::string>()->default_value("/var/log/anezka.log"));
#elif _WIN32
      ("log-output", "Path to config file", cxxopts::value<std::string>()->default_value("./log/anezka.log"));
#endif

  int argc = 3;
  const char* argv[] = {"anezkasearch", "--file", "somefile.yml"};

  cxxopts::ParseResult res = options.parse(argc, argv);
  auto file = res["file"].as<std::string>();
  REQUIRE(file == "somefile.yml");

  AppState<IntInd> state(res);
  REQUIRE(state.GetArgs()["log-output"].count() == 0);

  // Id is parsed from config
}

TEST_CASE("AppState owns indexStorage"){
  YAML::Node config = YAML::LoadFile("/home/fume/projects/cpp/anezkasearch/test/units/test_config.yaml");

  AppState<IntInd> state(cxxopts::ParseResult(), config);
  CHECK(state.GetConfig().value()["version"].as<std::string>() == "0.1");
  REQUIRE(state.GetWeakIndexStorage().use_count() == 1);
  REQUIRE(config["version"].as<std::string>() == "0.1");

  std::vector<int> vec;
}