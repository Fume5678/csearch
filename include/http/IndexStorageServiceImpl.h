//
// Created by fume on 27.04.23.
//

#ifndef ANEZKASEARCH_INDESTORAGESERVICEIMPL_H
#define ANEZKASEARCH_INDESTORAGESERVICEIMPL_H

#include <AppState.h>
#include <sstream>
#include <string>

#include <AnezkaSearch.grpc.pb.h>

namespace anezkasearch {

template <typename IndT>
class IndexStorageServiceImpl : public IndexStorageService::Service {
 public:
  IndexStorageServiceImpl(std::shared_ptr<AppState<IndT>> state)
      : m_state{state}, m_index_storage{state->GetIndexStorage()} {
  }

  // TODO rename to indexes
  grpc::Status InsertIndex(::grpc::ServerContext* context,
                           const ::anezkasearch::KeyIndexes* request,
                           ::anezkasearch::Empty* response) {
    std::stringstream sstr;
    sstr << "Insert index by key  " << request->key() << ": "
         << " [ ";

    // TODO implement search request handler
    for (const auto& ind : request->indexes()) {
      if constexpr (std::is_same<IndT, IntInd>::value) {
        sstr << std::to_string(ind.i_ind()) << ", ";
        m_index_storage->Insert( request->key(), ind.i_ind());
      }
      else {
        sstr << ind.s_ind() << ", ";
        m_index_storage->Insert( request->key(), ind.s_ind());
      }
    }
    sstr << "]";
    LOGI << sstr.str();

    return grpc::Status::OK;
  }

  grpc::Status GetIndexes(::grpc::ServerContext* context,
                          const ::anezkasearch::KeyIndexes* request,
                          ::anezkasearch::KeyIndexes* response) {
    LOGI << "Get indexes by key " << request->key();
    response->set_key(request->key());
    for (const auto& ind : m_index_storage->Get(request->key())) {
      if constexpr (std::is_same<IndT, IntInd>::value) {
        response->add_indexes()->set_i_ind(ind);
      }
      else {
        LOGI << ind;
        response->add_indexes()->set_s_ind(ind);
      }
    }
    return grpc::Status::OK;
  }

  grpc::Status RemoveIndexes(::grpc::ServerContext* context,
                             const ::anezkasearch::KeyIndexes* request,
                             ::anezkasearch::Empty* response) {
    std::stringstream sstr;
    sstr << "Remove next indexes [ ";
    for (const auto& ind : request->indexes()) {
      if constexpr (std::is_same<IndT, IntInd>::value) {
        sstr << std::to_string(ind.i_ind()) << ", ";
      }
      else {
        sstr << ind.s_ind() << ", ";
      }
    }
    sstr << "]";
    LOGI << sstr.str();
    return Service::RemoveIndex(context, request, response);
  }

 private:
  std::shared_ptr<AppState<IndT>> m_state;
  std::shared_ptr<IndexStorage<IndT>> m_index_storage;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_INDESTORAGESERVICEIMPL_H
