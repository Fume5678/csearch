//
// Created by fume on 27.04.23.
//

#ifndef ANEZKASEARCH_SEARCHREQUESTHANDLER_H
#define ANEZKASEARCH_SEARCHREQUESTHANDLER_H

#include <AppState.h>
#include <memory>

#include <utils/TextToWords.h>

namespace anezkasearch {

template <typename IndT>
class SearchRequestHandler {
 public:
  SearchRequestHandler(std::shared_ptr<AppState<IndT>> state)
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

#endif  // ANEZKASEARCH_SEARCHREQUESTHANDLER_H
