#ifndef ANEZKASEARCH_STREAMSUGGESTHANDLER_H
#define ANEZKASEARCH_STREAMSUGGESTHANDLER_H

#include <AppState.h>
#include <Vocabulary.h>
#include <memory>

namespace anezkasearch {
template <int AlphSize>
class StreamSuggestHandler {
 public:
  template <typename IndT>
  StreamSuggestHandler(std::shared_ptr<AppState<IndT>> state)
      : m_vocabulary{state->GetVocabulary()} {
  }

  std::vector<std::string> GetSuggests(const std::string& prefix) {
    std::vector<std::string> res;
    m_vocabulary->SearchWords(prefix, res);
    return res;
  }

 private:
  std::shared_ptr<Vocabulary<AlphSize>> m_vocabulary;
};
};  // namespace anezkasearch

#endif