//
// Created by fumedesk on 11.06.23.
//

#include <WordValidator.h>

#include "testmain.h"

using namespace anezkasearch;

TEST_CASE("WorldValidator inition"){
  cxxopts::Options options = GetOptions();
  cxxopts::ParseResult res = options.parse(ARGC, ARGV);
  YAML::Node config = YAML::LoadFile("./test_config.yaml");
  auto state = std::make_shared<AppState<IntInd>>(res, config);

  auto min_key_len =
    state->GetConfig()["data"]["min_key_len"].as<uint32_t>();

  WordValidator validator(state->GetConfig()["data"]["stopwords"].as<std::string>(), min_key_len);
  validator.InitVocabularies();

  REQUIRE_FALSE(validator.CheckWord("or"));
  REQUIRE_FALSE(validator.CheckWord("все"));
  REQUIRE(validator.CheckWord("слово"));
  REQUIRE_FALSE(validator.CheckWord("сл"));
}