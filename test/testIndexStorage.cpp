//
// Created by fume on 08.03.23.
//

#include <catch2/catch_test_macros.hpp>

#include <search/IndexStorage.h>
#include <cstdint>
#include <ranges>
#include <set>

TEST_CASE("IndexStorage adding") {
  IndexStorage<std::hash, std::uint64_t> index_storage;

  index_storage.Get()

  index_storage.Insert(std::hash("word"), 123);

  std::set<std::uint64_t> indexs = index_storage.Get(std::hash("word"));

  std::vector v(indexs.begin(), indexs.end());
  REQUIRE(v.size() == 1);
  REQUIRE(v[0] == 123);

}
