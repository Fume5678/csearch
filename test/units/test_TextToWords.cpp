//
// Created by fume on 14.03.23.
//

#include <array>
#include <iostream>
#include <ranges>
#include <sstream>
#include "testmain.h"
#include "utils/TextToWords.h"

using namespace anezkasearch;

TEST_CASE("TextToWords") {
  const std::string text =
      "Lorem a ipsum or dolor sit amet, consectetur adipiscing elit.\n"
      " Vivamus rhoncus lorem non euismod eleifend. Duis elementum\n";

  const std::array<std::string, 18> arr_words = {
      "lorem", "a",  "ipsum", "or",   "dolor",   "sit",  "amet",  "consectetur",
      "adipiscing", "elit",     "vivamus", "rhoncus",  "lorem", "non",
      "euismod",    "eleifend", "duis",  "elementum"};

  SECTION("Range-based loop") {
    TextToWords text_word(text);
    int count = 0;
    for(const auto& word:  text_word.GetWordsSeq()) {
      CHECK(word == arr_words[count]);
      count++;
    }
  }
}