//
// Created by fume on 13.03.23.
//

#ifndef ANEZKASEARCH_TESTMAIN_H
#define ANEZKASEARCH_TESTMAIN_H

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include <AppState.h>

inline cxxopts::Options GetOptions (){
  cxxopts::Options options("AnezkaSearch", "One line description of MyProgram");
  options.add_options()
      ("f,file", "Path to config file", cxxopts::value<std::string>())
#ifdef linux
          ("log-output", "Path to config file", cxxopts::value<std::string>()->default_value("/var/log/anezka.log"));
#elif _WIN32
          ("log-output", "Path to config file", cxxopts::value<std::string>()->default_value("./log/anezka.log"));
#endif

  return options;
};

inline const int ARGC = 5;
inline const char* ARGV[] = {"anezkasearch", "--file", "somefile.yml", "--log-output", "anezkasearch_test.log"};


#endif  // ANEZKASEARCH_TESTMAIN_H
