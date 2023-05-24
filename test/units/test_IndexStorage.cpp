//
// Created by fume on 08.03.23.
//

#include "testmain.h"

#include <IndexStorage.h>
#include <cstdint>
#include <functional>
#include <ranges>
#include <set>
#include <string>

using namespace std::literals;
using namespace anezkasearch;

TEST_CASE("IndexStorage constructing") {
  IndexStorage<IntInd> index_storage;
}

TEST_CASE("IndexStorage adding text key") {
  IndexStorage<IntInd> index_storage;

  const auto res = index_storage.Get("word");
  REQUIRE(res.empty());

  auto key = "word"s;
  index_storage.Insert("word", 123);
  const auto indexes = index_storage.Get("word");

  std::vector v(indexes.begin(), indexes.end());
  REQUIRE(v.size() == 1);
  REQUIRE(v[0] == 123);
}

TEST_CASE("IndexStorage unique index") {
  IndexStorage<IntInd>  index_storage;

  auto key = "word"s;
  index_storage.Insert("word", 123);
  index_storage.Insert("word", 123);
  const auto indexes = index_storage.Get("word");

  REQUIRE(indexes.size() == 1);
  REQUIRE(indexes[0] == 123);
}

TEST_CASE("IndexStorage int indexes is sorted") {
  IndexStorage<IntInd>  index_storage;

  auto key = "word"s;
  index_storage.Insert("word", 123);
  index_storage.Insert("word", 124);
  index_storage.Insert("word", 255);
  index_storage.Insert("word", 126);
  const auto indexes = index_storage.Get("word");

  REQUIRE(indexes.size() == 4);
  REQUIRE(indexes[0] == 123);
  REQUIRE(indexes[1] == 124);
  REQUIRE(indexes[2] == 126);
  REQUIRE(indexes[3] == 255);
}

TEST_CASE("IndexStorage string indexes is sorted") {
  IndexStorage<StringInd>  index_storage;

  auto key = "word"s;
  index_storage.Insert("word", "123");
  index_storage.Insert("word", "124");
  index_storage.Insert("word", "255");
  index_storage.Insert("word", "126");
  const auto indexes = index_storage.Get("word");

  REQUIRE(indexes.size() == 4);
  REQUIRE(indexes[0] == "123");
  REQUIRE(indexes[1] == "124");
  REQUIRE(indexes[2] == "126");
  REQUIRE(indexes[3] == "255");
}



TEST_CASE("IndexStorage different type of indexes") {
  IndexStorage<StringInd> index_storage_string;
  index_storage_string.Insert("asd", "123");
  REQUIRE((*index_storage_string.Get("asd").begin()) == "123");

  IndexStorage<IntInd> index_storage_int;
  index_storage_int.Insert("asd", 123);
  REQUIRE((*index_storage_int.Get("asd").begin()) == 123);
}

TEST_CASE("IndexStorage different removing keys") {
  IndexStorage<StringInd> index_storage_string;
  index_storage_string.Insert("asd", "123");
  index_storage_string.Remove("asd");
  REQUIRE(index_storage_string.Get("asd").empty());
}

TEST_CASE("IndexStorage different removing index") {
  IndexStorage<StringInd> index_storage_string;
  index_storage_string.Insert("asd", "123");
  index_storage_string.Insert("asd", "234");
  index_storage_string.Insert("qwe", "123");
  index_storage_string.RemoveInd("123");
  REQUIRE(index_storage_string.Get("asd").size() == 1);
  REQUIRE(index_storage_string.Get("qwe").empty());
}

//// Template test
// TEST_CASE("IndexStorage concept constraint wrong indexes") {
//   IndexStorage<int> index_storage("table_1"); // Ok
//   IndexStorage<int*> index_storage_2("table_2"); // must not compile
// }
