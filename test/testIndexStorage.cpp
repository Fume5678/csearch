//
// Created by fume on 08.03.23.
//

#include "tests.h"

#include <IndexStorage.h>
#include <cstdint>
#include <ranges>
#include <set>
#include <functional>
#include <string>

using namespace std::literals;
using namespace anezkasearch;

TEST_CASE("IndexStorage constructing") {

  IndexStorage<IntId> index_storage("table_name");

  REQUIRE(index_storage.TableName() == "table_name");
}

TEST_CASE("IndexStorage adding text key") {

  IndexStorage<IntId> index_storage("table_name");

  std::set<IntId> res = index_storage.Get("word");
  REQUIRE(res.empty());

  auto key = "word"s;
  index_storage.Insert("word", 123);
  const auto indexes = index_storage.Get("word");

  std::vector v(indexes.begin(), indexes.end());
  REQUIRE(v.size() == 1);
  REQUIRE(v[0] == 123);
}

TEST_CASE("IndexStorage unique index") {

  IndexStorage<IntId> index_storage("table_name");

  auto key = "word"s;
  index_storage.Insert("word", 123);
  index_storage.Insert("word", 123);
  const auto indexes = index_storage.Get("word");

  std::vector v_2(indexes.begin(), indexes.end());
  REQUIRE(v_2.size() == 1);
  REQUIRE(v_2[0] == 123);
}

TEST_CASE("IndexStorage different type of indexes") {
  IndexStorage<StringId> index_storage_string("table_name");
  index_storage_string.Insert("asd", "123");
  REQUIRE((*index_storage_string.Get("asd").begin()) == "123");

  IndexStorage<IntId> index_storage_int("table_name");
  index_storage_int.Insert("asd", 123);
  REQUIRE((*index_storage_int.Get("asd").begin()) == 123);
}

TEST_CASE("IndexStorage different removing keys") {
  IndexStorage<StringId> index_storage_string("table_name");
  index_storage_string.Insert("asd", "123");
  index_storage_string.Remove("asd");
  REQUIRE(index_storage_string.Get("asd").empty());
}

TEST_CASE("IndexStorage different removing index") {
  IndexStorage<StringId> index_storage_string("table_name");
  index_storage_string.Insert("asd", "123");
  index_storage_string.Insert("asd", "234");
  index_storage_string.Insert("qwe", "123");
  index_storage_string.RemoveInd("123");
  REQUIRE(index_storage_string.Get("asd").size() == 1);
  REQUIRE(index_storage_string.Get("qwe").empty());
}

//// Template test
//TEST_CASE("IndexStorage concept constraint wrong indexes") {
//  IndexStorage<int> index_storage("table_1"); // Ok
//  IndexStorage<int*> index_storage_2("table_2"); // must not compile
//}
