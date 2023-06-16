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
  WordValidator validator(state);
  validator.InitVocabularies();
}