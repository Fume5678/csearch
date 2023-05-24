//
// Created by fume on 12.03.23.
//
#include "testmain.h"

#include <memory>
#include <optional>
#include <tuple>

#include <AppState.h>
#include <DataRow.h>
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
  MockDbConnection(std::shared_ptr<AppState<IdT>> state) {
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

  std::optional<DataRow<IdT>> Next() {
    next_count++;

    if (current_row >= max_rows) {
      return std::nullopt;
    }

    IntInd id = std::get<0>(data_rows[current_row]);
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
  SECTION("initialization and closing") {
    cxxopts::Options options = GetOptions();
    cxxopts::ParseResult res = options.parse(ARGC, ARGV);
    auto state = std::make_shared<AppState<IntInd>>(res);
    Indexer<MockDbConnection, AppState<IntInd>::index_type> indexer(state);
    CHECK(MockDbConnection<IntInd>::init_count == 1);
    CHECK(MockDbConnection<IntInd>::open_count == 0);
    REQUIRE(MockDbConnection<IntInd>::close_count == 0);
  }

  MockDbConnection<IntInd>::reset_static();
  SECTION("run indexing") {
    cxxopts::Options options = GetOptions();
    cxxopts::ParseResult res = options.parse(ARGC, ARGV);
    auto state = std::make_shared<AppState<IntInd>>(res);
    Indexer<MockDbConnection, AppState<IntInd>::index_type> indexer(state);
    indexer.Run();
    CHECK(MockDbConnection<IntInd>::init_count == 1);
    CHECK(MockDbConnection<IntInd>::open_count == 1);
    CHECK(MockDbConnection<IntInd>::close_count == 1);
    CHECK(MockDbConnection<IntInd>::next_count == 4);

    REQUIRE(state->GetWeakIndexStorage().lock()->Get("pochemu") ==
            std::vector<IntInd>{2});
    REQUIRE(state->GetWeakIndexStorage().lock()->Get("vsegda") ==
            std::vector<IntInd>{1, 3});
  }
}