//
// Created by fume on 07.03.23.
//

#ifndef STATE_H
#define STATE_H

#include <fmt/core.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Log.h>
#include <yaml-cpp/yaml.h>
#include <cxxopts/cxxopts.hpp>

#include <memory>
#include <optional>

#include <Index.h>
#include <IndexStorage.h>

namespace anezkasearch {

using Config = YAML::Node;
constexpr auto ConfigFromFile = &YAML::LoadFile;

using OptionsArgs = cxxopts::Options;
using CommandArgs = cxxopts::ParseResult;

template <typename IndT>
  requires ConcIndType<IndT>
class AppState {
  inline void init() {
    InitLog();
    LOGI << "Initializaion AppState";
    m_index_storage = std::make_shared<IndexStorage<IndT>>();
  }

  inline static void InitLog() {
    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::info, &consoleAppender);
  }

 public:

  using value_type = IndT;
//  constexpr operator value_type() const noexcept
//  {	// return stored value
//    return (m_index_storage);
//  }

  // TODO remove this constructor
  AppState(const CommandArgs& args): m_args{args} {
    init();
  }

  AppState(const CommandArgs& args,  Config& config) : m_config{config}, m_args{args}{
    init();
  }

  inline const CommandArgs& GetArgs(){
    return m_args;
  }

  inline Config& GetConfig() {
    return m_config;
  }

  inline std::weak_ptr<IndexStorage<IndT>> GetWeakIndexStorage() {
    return m_index_storage;
  }

 private:
  IndT type_value{};
  std::shared_ptr<IndexStorage<IndT>> m_index_storage;
  Config m_config;
  const CommandArgs m_args;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_STATE_H
