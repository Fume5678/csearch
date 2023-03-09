//
// Created by fume on 08.03.23.
//

#include <catch2/catch_test_macros.hpp>

#include <IndexStorage.h>
#include <cstdint>
#include <ranges>
#include <set>
#include <functional>
#include <string>

using namespace std::literals;
using namespace anezkasearch;

TEST_CASE("IndexStorage adding text key") {

  IndexStorage index_storage;

  std::set<std::uint64_t> res = index_storage.Get("word");
  REQUIRE(res.empty());

  auto key = "word"s;
  index_storage.Insert("word", 123);
  const auto indexs = index_storage.Get("word");

  std::vector v(indexs.begin(), indexs.end());
  REQUIRE(v.size() == 1);
  REQUIRE(v[0] == 123);
}
