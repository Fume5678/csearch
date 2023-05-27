#include "testmain.h"

#include <Vocabulary.h>

using namespace anezkasearch;

TEST_CASE("Vocabulary adding keys and contains method") {
  Vocabulary vocabulary;

  vocabulary.Insert("walk");
  vocabulary.Insert("wait");
  vocabulary.Insert("wonder");
  vocabulary.Insert("igor");


  vocabulary.Print();

  REQUIRE(vocabulary.Contains("walk"));
  REQUIRE(vocabulary.Contains("wait"));
  REQUIRE(vocabulary.Contains("wonder"));
  REQUIRE(!vocabulary.Contains("walter"));
  REQUIRE(!vocabulary.Contains("some"));

}

TEST_CASE("Vocabulary getting keys by key") {

}