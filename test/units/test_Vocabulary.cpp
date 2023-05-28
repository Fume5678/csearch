#include <Vocabulary.h>
#include <ranges>
#include "testmain.h"

using namespace anezkasearch;

TEST_CASE("Vocabulary adding keys and contains method") {
  Vocabulary vocabulary{EN_SIZE};

  vocabulary.Insert("walk");
  vocabulary.Insert("wait");
  vocabulary.Insert("wonder");
  vocabulary.Insert("igor");

  REQUIRE(vocabulary.Contains("walk"));
  REQUIRE(vocabulary.Contains("wait"));
  REQUIRE(vocabulary.Contains("wonder"));
  REQUIRE(!vocabulary.Contains("walter"));
  REQUIRE(!vocabulary.Contains("some"));
}

TEST_CASE("Vocabulary getting keys by key") {
  Vocabulary vocabulary{EN_SIZE};
  vocabulary.Insert("walk");
  vocabulary.Insert("wait");
  vocabulary.Insert("waitanger");
  vocabulary.Insert("wonder");
  vocabulary.Insert("igor");

  std::vector<std::string> words;
  vocabulary.SearchWords("wa", words);

  REQUIRE(std::ranges::find(words, "walk") != words.end());
  REQUIRE(std::ranges::find(words, "wait") != words.end());
  REQUIRE(std::ranges::find(words, "waitanger") != words.end());
  REQUIRE(std::ranges::find(words, "wonder") == words.end());
}

TEST_CASE("Vocabulary getting keys in generator by key ") {
  Vocabulary vocabulary{EN_SIZE};
  vocabulary.Insert("walk");
  vocabulary.Insert("wait");
  vocabulary.Insert("waitanger");
  vocabulary.Insert("wonder");
  vocabulary.Insert("igor");

  std::vector<std::string> words;

  for(auto word : vocabulary.SearchWordsSeq("wa")){
    words.push_back(word);
  }

  REQUIRE(std::ranges::find(words, "walk") != words.end());
  REQUIRE(std::ranges::find(words, "wait") != words.end());
  REQUIRE(std::ranges::find(words, "waitanger") != words.end());
  REQUIRE(std::ranges::find(words, "wonder") == words.end());
}