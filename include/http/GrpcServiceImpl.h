//
// Created by fume on 27.04.23.
//

#ifndef ANEZKASEARCH_GRPCSERVICEIMPL_H
#define ANEZKASEARCH_GRPCSERVICEIMPL_H

#include <AppState.h>
#include <http/SearchRequestHandler.h>

#include <IndexStorage.grpc.pb.h>

namespace anezkasearch {

template <typename IndT>
class GrpcServiceImpl : public IndexStorageService::Service {
 public:
  grpc::Status InsertIndex(::grpc::ServerContext* context,
                           const ::anezkasearch::KeyIndexes* request,
                           ::anezkasearch::KeyIndexes* response) {
    //    if constexpr(std::is_same<IntId, typename
    //    decltype(*m_state)::value_type>::value) {
    //      std::cout << "Insert IntId\n";
    //    }
    //    if constexpr(std::is_same<StringId, typename
    //    decltype(*m_state)::value_type>::value) {
    //      std::cout << "Insert StringId\n";
    //    }

    return Service::InsertIndex(context, request, response);
  }

  grpc::Status GetIndexes(::grpc::ServerContext* context,
                          const ::anezkasearch::KeyIndexes* request,
                          ::anezkasearch::KeyIndexes* response) {
    return Service::GetIndexes(context, request, response);
  }

  grpc::Status RemoveIndex(::grpc::ServerContext* context,
                           const ::anezkasearch::KeyIndexes* request,
                           ::anezkasearch::KeyIndexes* response) {
    return Service::RemoveIndex(context, request, response);
  }

 private:
  SearchRequestHandler m_handler;

  std::shared_ptr<AppState<IndT>>& m_state;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_GRPCSERVICEIMPL_H
