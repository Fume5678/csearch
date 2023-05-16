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

  std::set<IndT> GetIndexes(std::string text){
    TextToWords to_words(text);

    std::set<IndT> indexes = m_index_storage->Get(*to_words);
    ++to_words;
    while(to_words){
      auto row = m_index_storage->Get(*to_words);

      // TODO optimization
      std::set<IndT> merge_set;
      for(const auto& it : indexes){
        if(row.find(it) != row.end()){
          merge_set.insert(it);
        }
      }
      indexes = merge_set;
      ++to_words;
    }

    return indexes;
  }


      private:
  std::shared_ptr<AppState<IndT>> m_state;
  std::shared_ptr<IndexStorage<IndT>> m_index_storage;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_SEARCHREQUESTHANDLER_H
