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
#include <Vocabulary.h>
#include <WordValidator.h>

namespace anezkasearch {

using Config = YAML::Node;
constexpr auto ConfigFromFile = &YAML::LoadFile;

using OptionsArgs = cxxopts::Options;
using CommandArgs = cxxopts::ParseResult;

// someday more lang will be here
enum class VocabularyLang {EN};

template <typename IndT>
  requires ConcIndType<IndT>
class AppState {
  inline void init() {
    InitLog();
    LOGI << "Initializaion AppState";
    m_index_storage = std::make_shared<IndexStorage<IndT>>();

    size_t min_key_len = 0;
    if(m_config["data"]["min_key_len"].IsDefined()) {
      min_key_len =
          m_config["data"]["min_key_len"].as<uint32_t>();
    }

    if(m_config["data"]["stopwords"].IsDefined()){
      m_word_validator = std::make_shared<WordValidator>(
        m_config["data"]["stopwords"].as<std::string>(), min_key_len); 
    } else {
      LOGW << "stopwords is not defined";
    }

  }

  inline void InitLog() {
    if (!is_log_inited) {
      static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;

      static plog::RollingFileAppender<plog::CsvFormatter> fileAppender(
          m_args["log-output"].as<std::string>().c_str(), 8000,
          3);  // Create the 1st appender.
      plog::init(plog::info, &consoleAppender).addAppender(&fileAppender);

      is_log_inited = true;
    }
  }

 public:
  using index_type = IndT;
  static bool is_log_inited;

  // TODO remove this constructor
  AppState(const CommandArgs& args) : m_args{args} {
    init();
  }

  AppState(const CommandArgs& args, Config& config)
      : m_config{config}, m_args{args} {
    init();
  }

  inline const CommandArgs& GetArgs() {
    return m_args;
  }

  inline Config& GetConfig() {
    return m_config;
  }

  inline std::shared_ptr<IndexStorage<IndT>> GetIndexStorage() {
    return {m_index_storage};
  }

  inline std::weak_ptr<IndexStorage<IndT>> GetWeakIndexStorage() {
    return {m_index_storage};
  }

  inline std::shared_ptr<WordValidator> GetWordValidator() {
    return {m_word_validator};
  }

  inline std::shared_ptr<Vocabulary> GetVocabulary(VocabularyLang lang) {
    if(not m_vocabularies.contains(lang)){
      m_vocabularies.insert({lang, std::make_shared<Vocabulary>()});
    }

    return {m_vocabularies[lang]};
  }


 private:
  IndT type_value{};
  std::shared_ptr<IndexStorage<IndT>> m_index_storage;
  std::shared_ptr<WordValidator> m_word_validator;
  //  std::shared_ptr<Vocabulary> m_vocabulary;
  std::unordered_map<VocabularyLang, std::shared_ptr<Vocabulary>>
      m_vocabularies;

  Config m_config;
  const CommandArgs m_args;
};

template <typename IndT>
  requires ConcIndType<IndT>
bool anezkasearch::AppState<IndT>::is_log_inited = false;
}  // namespace anezkasearch
#endif  // ANEZKASEARCH_STATE_H
