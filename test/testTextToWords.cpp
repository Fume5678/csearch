//
// Created by fume on 14.03.23.
//

#include <TextToWords.h>
#include <array>
#include <iostream>
#include <ranges>
#include <sstream>
#include "tests.h"

using namespace anezkasearch;

TEST_CASE("TextToWords") {
  const std::string text =
      "Lorem a ipsum or dolor sit amet, consectetur adipiscing elit.\n"
      " Vivamus rhoncus lorem non euismod eleifend. Duis elementum\n";

  const std::array<std::string, 16> arr_words = {
      "lorem",      "ipsum",    "dolor",   "sit",      "amet",  "consectetur",
      "adipiscing", "elit",     "vivamus", "rhoncus",  "lorem", "non",
      "euismod",    "eleifend", "duis",    "elementum"};

  SECTION("Initialize") {
    TextToWords text_to_word(text);
    TextToWords::iterator it = text_to_word.begin();
    REQUIRE(it.CurrentIndex() == 5);
    REQUIRE(it.Get() == "lorem");
    REQUIRE(*it == "lorem");
    REQUIRE(text_to_word.end().Get() == std::nullopt);
  }

  SECTION("Foreach") {
    TextToWords text_word(text);
    int count = 0;
    for (auto word : text_word) {
      CHECK(*word == arr_words[count]);
      count++;
    }
  }

  SECTION("Output to stream") {
    std::stringstream sstr;
    TextToWords text_word(text);

    for (auto word : text_word) {
      sstr << *word;
    }

    std::stringstream sstr2;
    for (char const c : arr_words | std::views::join) sstr2 << c;

    REQUIRE_THAT(sstr.str(), Catch::Matchers::Equals(sstr.str()));
  }
}