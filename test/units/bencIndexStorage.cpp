//
// Created by fume on 15.03.23.
//

#include "testmain.h"

#ifdef ENABLED_BENCHMARK
#include <IndexStorage.h>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <chrono>
#include <iostream>
#include <random>
#include <syncstream>
#include <thread>
#include <fstream>

using namespace std::chrono_literals;

auto ReadWords(){
  std::ifstream ifs("/home/fume/projects/cpp/anezkasearch/test/words.txt");

  if(not ifs.is_open()){
    throw std::runtime_error("words.txt file not found");
  }
  std::vector<std::string> words;

  std::string word;
  while(not ifs.eof()){
    std::getline(ifs, word);
    words.push_back(word);
  }

  ifs.close();
  return words;
}


TEST_CASE("IndexStorage benchmark") {
  // не ну а че
  const std::vector<std::string> words = ReadWords();

  std::random_device rd;
  std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()

  // For random keys
  std::uniform_int_distribution<> distrib_keys(0, 1000);

  // For random indexes
  std::uniform_int_distribution<> distrib_indexes(1, 10000);
  SECTION("One insert") {
    anezkasearch::IndexStorage<anezkasearch::IntId> index_storage;

    BENCHMARK("Sync insert") {
      index_storage.Insert(words[distrib_keys(gen)], distrib_indexes(gen));
    };

    BENCHMARK("Sync get") {
      index_storage.Get(words[distrib_keys(gen)]);
    };
  }

}

#endif