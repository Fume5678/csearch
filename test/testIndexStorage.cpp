//
// Created by fume on 08.03.23.
//

#include <catch2/catch_test_macros.hpp>

#include <search/IndexStorage.h>
#include <cstdint>
#include <ranges>
#include <set>
#include <functional>
#include <string>

using namespace std::literals;
using namespace anezkasearch;

TEST_CASE("IndexStorage adding text key") {
  IndexStorage<std::hash<std::string>, std::uint64_t> index_storage;

  std::set<std::uint64_t> res = index_storage.Get();

  auto key = "word"s;
  index_storage.Insert(std::hash<std::string>{}(key), 123);

//  std::set<std::uint64_t> indexs = index_storage.Get(std::hash("word"));
//
//  std::vector v(indexs.begin(), indexs.end());
//  REQUIRE(v.size() == 1);
//  REQUIRE(v[0] == 123);
}
