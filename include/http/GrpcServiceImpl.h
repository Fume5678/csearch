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
  GrpcServiceImpl(std::shared_ptr<AppState<IndT>> state) : m_state{state}{}

  grpc::Status InsertIndex(::grpc::ServerContext* context,
                           const ::anezkasearch::KeyIndexes* request,
                           ::anezkasearch::KeyIndexes* response) {
    std::stringstream sstr;
    sstr << "Insert index by key  " <<  request->key() << ": " << " [ " ;
    for(const auto& ind : request->indexes()){
      if constexpr (std::is_same<IndT, IntInd>::value){
        sstr << std::to_string(ind.i_ind()) << ", ";
      } else {
        sstr <<ind.s_ind() << ", ";
      }
    }
    sstr << "]" ;
    LOGI << sstr.str();

    return grpc::Status::OK;
  }

  grpc::Status GetIndexes(::grpc::ServerContext* context,
                          const ::anezkasearch::KeyIndexes* request,
                          ::anezkasearch::KeyIndexes* response) {
    LOGI << "Get indexes by key " << request->key();
    return Service::GetIndexes(context, request, response);
  }

  grpc::Status RemoveIndexes(::grpc::ServerContext* context,
                           const ::anezkasearch::KeyIndexes* request,
                           ::anezkasearch::KeyIndexes* response) {
    std::stringstream sstr;
    sstr << "Remove next indexes [ " ;
    for(const auto& ind : request->indexes()){
      if constexpr (std::is_same<IndT, IntInd>::value){
        sstr << std::to_string(ind.i_ind()) << ", ";
      } else {
        sstr <<ind.s_ind() << ", ";
      }
    }
    sstr << "]" ;
    LOGI << sstr.str();
    return Service::RemoveIndex(context, request, response);
  }

 private:
  SearchRequestHandler m_handler;

  std::shared_ptr<AppState<IndT>>& m_state;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_GRPCSERVICEIMPL_H
