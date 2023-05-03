//
// Created by fume on 27.04.23.
//

#ifndef ANEZKASEARCH_GRPCSERVICEIMPL_H
#define ANEZKASEARCH_GRPCSERVICEIMPL_H

#include <http/SearchRequestHandler.h>

#include <IndexStorage.grpc.pb.h>

namespace anezkasearch {

class GrpcServiceImpl : public IndexStorageService::Service {
 public:
  grpc::Status InsertIndex(::grpc::ServerContext* context,
                           const ::anezkasearch::KeyIndexes* request,
                           ::anezkasearch::KeyIndexes* response) override;

  grpc::Status GetIndexes(::grpc::ServerContext* context,
                          const ::anezkasearch::KeyIndexes* request,
                          ::anezkasearch::KeyIndexes* response) override;

  grpc::Status RemoveIndex(::grpc::ServerContext* context,
                           const ::anezkasearch::KeyIndexes* request,
                           ::anezkasearch::KeyIndexes* response) override;

 private:
  SearchRequestHandler m_handler;

};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_GRPCSERVICEIMPL_H
