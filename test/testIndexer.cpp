//
// Created by fume on 12.03.23.
//
#include "tests.h"

#include <memory>
#include <optional>
#include <tuple>

#include <AppState.h>
#include <DbConnection.h>
#include <IndexStorage.h>
#include <Indexer.h>

using namespace anezkasearch;

// Db immitation
static std::vector data_rows = {
    std::tuple(1, "title 1", "some description"),
    std::tuple(2, "name 2", "a pochemu i da"),
    std::tuple(3, "test 3", "on vsegda hotel pivka"),
};

// Mock Connection
class MockDbConnection {
 public:
  MockDbConnection(std::shared_ptr<AppState> state) {
  }

  void Open() {
    open_count++;

    current_row = 0;
    max_rows = data_rows.size();
  }

  void Close() {
    close_count++;
  }

  std::optional<DataRow<IntId>> Next() {
    next_count++;

    if (current_row >= next_count) {
      return std::nullopt;
    }

    IntId id = std::get<0>(data_rows[current_row]);
    std::string text = std::get<1>(data_rows[current_row]);
    text += std::get<2>(data_rows[current_row]);
    current_row++;

    return {{id, text}};
  }

  static inline int open_count = 0;
  static inline int close_count = 0;
  static inline int next_count = 0;

  static void reset_static() {
    open_count = 0;
    close_count = 0;
    next_count = 0;
  }

 private:
  int current_row;
  int max_rows;
};

TEST_CASE("Indexer tests") {
  auto state = std::make_shared<AppState>();
  auto storage = std::make_shared<IndexStorage<IntId>>();

  SECTION("initialization and closing") {
    Indexer<MockDbConnection, IntId> indexer(state, storage);
    CHECK(MockDbConnection::open_count == 0);
    REQUIRE(MockDbConnection::close_count == 0);
  }

  SECTION("run indexing") {
  }

  SECTION("") {
  }
}