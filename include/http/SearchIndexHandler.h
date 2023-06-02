//
// Created by fume on 27.04.23.
//

#ifndef ANEZKASEARCH_SEARCHINDEXHANDLER_H
#define ANEZKASEARCH_SEARCHINDEXHANDLER_H

#include <AppState.h>
#include <memory>

#include <utils/TextToWords.h>

namespace anezkasearch {

template <typename IndT>
class SearchIndexHandler {
 public:
  SearchIndexHandler(std::shared_ptr<AppState<IndT>> state)
      : m_state{state},
        m_index_storage{state->GetIndexStorage()},
        m_min_key_len{3} {
    if (m_state->GetConfig()["data"]["min_key_len"].IsDefined()) {
      m_min_key_len =
          m_state->GetConfig()["data"]["min_key_len"].template as<uint32_t>();
    }
  }

  std::vector<IndT> GetIndexes(std::string text) {
    std::vector<std::vector<std::string>> words_table;
    TextToWords text_to_words(text);

    // ERROR
    for (const auto& word : text_to_words.GetWordsSeq()) {
      std::vector<std::string> words_row;
      if (word.length() >= m_min_key_len) {
        words_row.push_back(word);

        // TODO checking for uniques indexes
        m_state->GetVocabulary(VocabularyLang::EN)
            ->SearchWords(word, words_row);
      }
      if (!words_row.empty()) {
        words_table.push_back(std::move(words_row));
      }
    }

    if (words_table.empty()) {
      return {};
    }

    // The words by prefix are summing indexes. And different words
    // are multiplies between them
    std::vector<IndT> res;
    for (const auto& word : words_table[0]) {
      auto found_indexes = m_index_storage->Get(word);
      res.insert(res.cend(), found_indexes.begin(), found_indexes.end());
    }

    for (size_t i = 1; i < words_table.size(); i++) {
      std::vector<IndT> row_indexes;
      for (const auto& word : words_table[i]) {
        auto found_indexes = m_index_storage->Get(word);
        row_indexes.insert(row_indexes.cend(), found_indexes.begin(),
                           found_indexes.end());
      }

      std::vector<IndT> new_res{};
      std::ranges::set_intersection(res, row_indexes,
                                    std::back_inserter(new_res));
      res = std::move(new_res);
    }

    return res;
  }

 private:
  std::shared_ptr<AppState<IndT>> m_state;
  std::shared_ptr<IndexStorage<IndT>> m_index_storage;
  size_t m_min_key_len;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_SEARCHINDEXHANDLER_H
