//
// Created by fume on 12.03.23.
//

#ifndef ANEZKASEARCH_INDEXER_H
#define ANEZKASEARCH_INDEXER_H

#include <AppState.h>
#include <DbConnection.h>
#include <IndexStorage.h>
#include <functional>
#include <memory>

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

  }

 private:
  std::unique_ptr<Connection, decltype(ConnectionDeleter)> m_connection;
  std::shared_ptr<AppState> m_app_state;
  std::shared_ptr<IndexStorage<IdT>> m_index_storage;
};

}  // namespace anezkasearch
#endif  // ANEZKASEARCH_INDEXER_H
