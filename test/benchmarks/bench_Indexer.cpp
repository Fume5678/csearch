//
// Created by fume on 15.03.23.
//

#include "../units/testmain.h"

#ifdef ENABLED_BENCHMARK
#include <catch2/benchmark/catch_benchmark.hpp>
#include <chrono>
#include <fstream>
#include <iostream>

#include <Indexer.h>
#include <sources/PostgresSource.h>

using namespace anezkasearch;
using namespace std::chrono_literals;

TEST_CASE("Indexer benchmarks") {
  cxxopts::Options options = GetOptions();
  cxxopts::ParseResult res = options.parse(ARGC, ARGV);
  YAML::Node config = YAML::LoadFile("./test_config.yaml");
  auto state = std::make_shared<AppState<IntInd>>(res, config);

  BENCHMARK("Postgres reading") {
    Indexer<PostgresSource, IntInd> indexer(state);
    indexer.Run();
  };
}

#endif