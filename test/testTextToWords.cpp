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
    TextToWords it = text_to_word;
    REQUIRE(it.CurrentIndex() == 5);
    REQUIRE(it.Get() == "lorem");
    REQUIRE(*it == "lorem");
  }

  SECTION("Foreach") {
    TextToWords text_word(text);
    int count = 0;
    while (text_word) {
      CHECK(*text_word == arr_words[count]);
      ++text_word;
      count++;
    }
  }

  SECTION("Output to stream") {
    std::stringstream sstr;
    TextToWords text_word(text);

    while (text_word) {
      sstr << *text_word;
      text_word.Next();
    }

    std::stringstream sstr2;
    for (char const c : arr_words | std::views::join) sstr2 << c;

    REQUIRE_THAT(sstr.str(), Catch::Matchers::Equals(sstr.str()));
  }

  SECTION("Test 1") {
    std::string str = "some description vsegda";
    TextToWords text_to_words(str);
    std::vector<std::string> arr;

    while(text_to_words){
        arr.push_back(*text_to_words);
        text_to_words.Next();
    }

    REQUIRE(arr == std::vector<std::string>{"some", "description", "vsegda"});

  }
}