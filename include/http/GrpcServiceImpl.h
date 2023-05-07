//
// Created by fume on 27.04.23.
//

#ifndef ANEZKASEARCH_GRPCSERVICEIMPL_H
#define ANEZKASEARCH_GRPCSERVICEIMPL_H

#include <AppState.h>
#include <http/SearchRequestHandler.h>

#include <IndexStorage.grpc.pb.h>
#include <sstream>
#include <string>

namespace anezkasearch {

template <typename IndT>
class GrpcServiceImpl : public IndexStorageService::Service {
 public:
  GrpcServiceImpl(std::shared_ptr<AppState<IndT>> state)
      : m_state{state}, m_index_storage{state->GetIndexStorage()} {
  }

  grpc::Status InsertIndex(::grpc::ServerContext* context,
                           const ::anezkasearch::KeyIndexes* request,
                           ::anezkasearch::KeyIndexes* response) {
    std::stringstream sstr;
    sstr << "Insert index by key  " << request->key() << ": "
         << " [ ";

    // TODO implement search request handler
    response->set_key(request->key());
    for (const auto& ind : request->indexes()) {
      if constexpr (std::is_same<IndT, IntInd>::value) {
        sstr << std::to_string(ind.i_ind()) << ", ";
        m_index_storage->Insert(request->key(), ind.i_ind());
      }
      else {
        sstr << ind.s_ind() << ", ";
        m_index_storage->Insert(request->key(), ind.s_ind());
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
        response->add_indexes()->set_s_ind(ind);
      }
    }
    return grpc::Status::OK;
  }

  grpc::Status RemoveIndexes(::grpc::ServerContext* context,
                             const ::anezkasearch::KeyIndexes* request,
                             ::anezkasearch::KeyIndexes* response) {
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
  SearchRequestHandler m_handler;
  std::shared_ptr<AppState<IndT>> m_state;
  std::shared_ptr<IndexStorage<IndT>> m_index_storage;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_GRPCSERVICEIMPL_H
