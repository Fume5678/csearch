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

#include <DataIds.h>
#include <IndexStorage.h>

namespace anezkasearch {

using Config = YAML::Node;
constexpr auto ConfigFromFile = &YAML::LoadFile;

using CommArgs = cxxopts::ParseResult;

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
  AppState(CommArgs options): m_args{options} {
    init();
  }

  AppState(CommArgs options, Config& config) : m_config{config}, m_args{options}{
    init();
  }

  inline CommArgs GetArgs(){
    return m_args;
  }

  inline std::optional<Config> GetConfig() const {
    return m_config;
  }

  inline std::weak_ptr<IndexStorage<IndT>> GetWeakIndexStorage() {
    return m_index_storage;
  }

 private:
  std::shared_ptr<IndexStorage<IndT>> m_index_storage;
  std::optional<Config> m_config;
  CommArgs m_args;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_STATE_H
