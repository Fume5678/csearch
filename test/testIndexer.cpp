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
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Log.h>

using namespace anezkasearch;

// Db immitation
static std::vector data_rows = {
    std::tuple(1, "title 1", "some description vsegda"),
    std::tuple(2, "name 2", "a pochemu i da"),
    std::tuple(3, "test 3", "on vsegda hotel pivka"),
};

// Mock Connection
template <typename IdT>
class MockDbConnection {
 public:
  MockDbConnection(std::shared_ptr<AppState> state) {
    init_count++;
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

    if (current_row >= max_rows) {
      return std::nullopt;
    }

    IntId id = std::get<0>(data_rows[current_row]);
    std::string text = std::get<1>(data_rows[current_row]);
    text += std::get<2>(data_rows[current_row]);
    current_row++;

    return {{id, text}};
  }

  static inline int init_count = 0;
  static inline int open_count = 0;
  static inline int close_count = 0;
  static inline int next_count = 0;

  static void reset_static() {
    init_count = 0;
    open_count = 0;
    close_count = 0;
    next_count = 0;
  }

 private:
  int current_row{};
  int max_rows{};
};

TEST_CASE("Indexer tests") {
  auto storage = std::make_shared<IndexStorage<IntId>>();

  SECTION("initialization and closing") {
    auto state = std::make_shared<AppState>();
    Indexer<IntId, MockDbConnection> indexer(state, storage);
    CHECK(MockDbConnection<IntId>::init_count == 1);
    CHECK(MockDbConnection<IntId>::open_count == 0);
    REQUIRE(MockDbConnection<IntId>::close_count == 0);
  }

  MockDbConnection<IntId>::reset_static();
  SECTION("run indexing") {
    plog::RollingFileAppender<plog::CsvFormatter> fileAppender("log.csv", 8000, 1);
    plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::info, &fileAppender).addAppender(&consoleAppender);

    auto state = std::make_shared<AppState>();
    Indexer<IntId, MockDbConnection> indexer(state, storage);
    indexer.Run();
    CHECK(MockDbConnection<IntId>::init_count == 1);
    CHECK(MockDbConnection<IntId>::open_count == 1);
    CHECK(MockDbConnection<IntId>::close_count == 1);
    CHECK(MockDbConnection<IntId>::next_count == 4);

    REQUIRE(storage->Get("pochemu") == std::set<IntId>{2});
    REQUIRE(storage->Get("vsegda") == std::set<IntId>{1, 3});

  }

}