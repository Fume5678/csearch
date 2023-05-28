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
      : m_state{state}, m_index_storage{state->GetIndexStorage()} {
  }

  std::vector<IndT> GetIndexes(std::string text) {
    std::vector<IndT> indexes;
    return indexes;
  }

 private:
  std::shared_ptr<AppState<IndT>> m_state;
  std::shared_ptr<IndexStorage<IndT>> m_index_storage;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_SEARCHINDEXHANDLER_H
