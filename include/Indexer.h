//
// Created by fume on 12.03.23.
//

#ifndef ANEZKASEARCH_INDEXER_H
#define ANEZKASEARCH_INDEXER_H

#include <AppState.h>
#include <DbConnection.h>
#include <IndexStorage.h>
#include <fmt/format.h>
#include <plog/Log.h>
#include <functional>
#include <memory>
#include "TextToWords.h"

namespace anezkasearch {

template <typename IdT, template <typename> class T>
concept ConcConnection = requires(T<IdT> val, std::shared_ptr<AppState> state) {
                           val.Open();
                           val.Close();
                           {
                             val.Next()
                           } -> std::same_as<std::optional<DataRow<IdT>>>;
                         };

template <typename IdT, template <class> class ConnectionT>
  requires ConcConnection<IdT, ConnectionT>
class Indexer {
 public:
  using Connection = ConnectionT<IdT>;

  std::function<void(Connection*)> ConnectionDeleter = [](Connection* conn) {
    conn->Close();
  };

  Indexer(std::shared_ptr<AppState> app_state,
          std::shared_ptr<IndexStorage<IdT>> index_storage)
      : m_connection(new Connection(app_state), ConnectionDeleter),
        m_app_state(app_state),
        m_index_storage(index_storage) {
  }

  void Run() {
    m_connection->Open();

    std::optional<DataRow<IdT>> data_row;

    PLOG_INFO << "Indexer start iterate row!";
    while (data_row = m_connection->Next(), data_row != std::nullopt) {
      PLOG_INFO << fmt::format("Data row: id {} text [\"{}\"]", data_row->id,
                               data_row->text_data);

      TextToWords text_to_words(data_row->text_data);

      std::string log_msg = "";
      while (text_to_words) {
        log_msg += text_to_words.Get() + ", ";
        m_index_storage->Insert(text_to_words.Get(), data_row->id);
        text_to_words.Next();
      }

      LOGI << fmt::format("To words: [{}]", log_msg);
    };

    PLOG_INFO << "Indexer end iterate row!";
    m_connection->Close();
  }

 private:
  std::unique_ptr<Connection, decltype(ConnectionDeleter)> m_connection;
  std::shared_ptr<AppState> m_app_state = nullptr;
  std::shared_ptr<IndexStorage<IdT>> m_index_storage = nullptr;
};

}  // namespace anezkasearch
#endif  // ANEZKASEARCH_INDEXER_H
