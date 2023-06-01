//
// Created by fume on 12.03.23.
//

#ifndef ANEZKASEARCH_INDEXER_H
#define ANEZKASEARCH_INDEXER_H

#include <AppState.h>
#include <DataRow.h>
#include <IndexStorage.h>
#include <fmt/format.h>
#include <plog/Log.h>
#include <functional>
#include <memory>
#include "utils/TextToWords.h"
#include "utils/Generator.h"

namespace anezkasearch {

template <template <typename> class T, typename IdT>
concept ConcConnection = requires(T<IdT> val, std::shared_ptr<AppState<IdT>> state) {
                           val.Open();
                           val.Close();
                           {
                             val.IterateRowsSeq()
                           } -> std::same_as<Generator<std::optional<DataRow<IdT>>>>;
                         };

template <template <class> class ConnectionT, typename IdT>
  requires ConcConnection<ConnectionT, IdT>
class Indexer {
 public:
  using Connection = ConnectionT<IdT>;

  Indexer(std::shared_ptr<AppState<IdT>> app_state)
      : m_connection(std::make_unique<Connection>(app_state)),
        m_state(app_state),
        m_index_storage(app_state->GetIndexStorage()),
        m_min_key_len{3} {
    if(m_state->GetConfig()["data"]["min_key_len"].IsDefined()) {
      m_min_key_len =
          m_state->GetConfig()["data"]["min_key_len"].template as<uint32_t>();
    } else {
      LOGI << "min key size by default: 3";
    }
  }

  void Run() {
    m_connection->Open();

    PLOG_INFO << "Indexer start iterate row!";
    for(const auto& data_row : m_connection->IterateRowsSeq() ) {
      if(data_row == std::nullopt){
        LOGI << "nullopt returned";
        continue;
      }
      LOGI << fmt::format("Data row: id {} text [\"{}\"]", data_row->id,
                               data_row->text_data);

      TextToWords text_to_words(data_row->text_data);
      std::string log_msg = "";
      // Reqrite to generator
      for(const auto& word : text_to_words.GetWordsSeq()){
        if (word.length() >= m_min_key_len) {
          log_msg += word + ", ";
          m_index_storage->Insert(word, data_row->id);
          m_state->GetVocabulary(VocabularyLang::EN)->Insert(word);
        }
      }
      LOGI << fmt::format("To words: [{}]", log_msg);
    };

    PLOG_INFO << "Indexer end iterate row!";
    m_connection->Close();
  }

 private:
  std::unique_ptr<Connection> m_connection;
  std::shared_ptr<AppState<IdT>> m_state = nullptr;
  std::shared_ptr<IndexStorage<IdT>> m_index_storage = nullptr;
  size_t m_min_key_len;
};

}  // namespace anezkasearch
#endif  // ANEZKASEARCH_INDEXER_H
