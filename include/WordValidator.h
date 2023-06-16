//
// Created by fumedesk on 11.06.23.
//

#ifndef ANEZKASEARCH_WORDCHECK_H
#define ANEZKASEARCH_WORDCHECK_H

#include <array>
#include <string>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <fmt/ranges.h>

#include <AppState.h>
#include <Vocabulary.h>

namespace anezkasearch {


template <typename IndT>
class WordValidator {
 public:
  WordValidator(std::shared_ptr<AppState<IndT>> state):m_state{state}{

  }

  void InitVocabularies() {
    using namespace nlohmann;

    if(!m_state->GetConfig()["data"]["stopwords"].template IsDefined()){
      LOGW << "stopwords is not defined";
      return;
    }

    try {
      std::string path_to_sw = m_state->GetConfig()["data"]["stopwords"].template as<std::string>();

      LOGI << "Stopwords reads from " << path_to_sw << std::endl;

      std::ifstream f(path_to_sw);
      f.exceptions(std::ios::badbit | std::ios::failbit);

      json stopword_js = json::parse(f);

      for(const auto& el: stopword_js.items()){
        auto key = el.key();
        if(!m_vocabularies.contains(key)){
          m_vocabularies.insert({key, std::make_unique<Vocabulary>()});
        }
        for(const auto& word : el.value()){
          m_vocabularies[key].get()->Insert(word);
        }
      }

      f.close();
    } catch (const std::ios_base::failure& fail){
      LOGE << "Fail to read stopwords file: " << fail.what() << std::endl;
    }

    LOGI << "End read stopwords " << std::endl;
  }

  bool CheckWord(std::string word) const;


 private:
  std::shared_ptr<AppState<IndT>> m_state;
  const  std::array<std::string, 2> stop_words_langs = {"en", "ru"};
  std::unordered_map<std::string, std::unique_ptr<Vocabulary>> m_vocabularies;
};

} // namespace anezkasearch

#endif  // ANEZKASEARCH_WORDCHECK_H
