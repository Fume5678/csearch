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
                             val.IterateRows()
                           } -> std::same_as<Generator<std::optional<DataRow<IdT>>>>;
                         };

template <template <class> class ConnectionT, typename IdT>
  requires ConcConnection<ConnectionT, IdT>
class Indexer {
 public:
  using Connection = ConnectionT<IdT>;

  std::function<void(Connection*)> ConnectionDeleter = [](Connection* conn) {
    conn->Close();
  };

  Indexer(std::shared_ptr<AppState<IdT>> app_state)
      : m_connection(new Connection(app_state), ConnectionDeleter),
        m_app_state(app_state),
        m_index_storage(app_state->GetIndexStorage()) {
  }

  void Run() {
    m_connection->Open();

//    std::optional<DataRow<IdT>> data_row;

    PLOG_INFO << "Indexer start iterate row!";
    for(const auto& data_row : m_connection->IterateRows() ) {
      if(data_row == std::nullopt){
        LOGI << "nullopt returned";
        continue;
      }
      LOGI << fmt::format("Data row: id {} text [\"{}\"]", data_row->id,
                               data_row->text_data);

      TextToWords text_to_words(data_row->text_data);

      std::string log_msg = "";
      // Reqrite to generator
      while (text_to_words) {
        if (text_to_words.Get().length() > text_to_words.MIN_WORD_LEN) {
          log_msg += text_to_words.Get() + ", ";
          m_index_storage->Insert(text_to_words.Get(), data_row->id);
        }
        text_to_words.Next();
      }

      LOGI << fmt::format("To words: [{}]", log_msg);
    };

    PLOG_INFO << "Indexer end iterate row!";
    m_connection->Close();
  }

 private:
  std::unique_ptr<Connection, decltype(ConnectionDeleter)> m_connection;
  std::shared_ptr<AppState<IdT>> m_app_state = nullptr;
  std::shared_ptr<IndexStorage<IdT>> m_index_storage = nullptr;
};

}  // namespace anezkasearch
#endif  // ANEZKASEARCH_INDEXER_H
