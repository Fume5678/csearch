//
// Created by fume on 27.04.23.
//

#ifndef ANEZKASEARCH_GRPCSERVER_H
#define ANEZKASEARCH_GRPCSERVER_H

#include <AppState.h>
#include <grpcpp/server_builder.h>
#include <http/IndexStorageServiceImpl.h>
#include <http/SearchServiceImpl.h>
#include "AnezkaSearch.grpc.pb.h"

namespace anezkasearch {

template <typename IndT>
class GrpcServer {
 public:
  GrpcServer(std::shared_ptr<AppState<IndT>> state) : m_state{state} {
  }

  void Run() {
    std::string addr = m_state->GetConfig()["app"]["host"].template as<std::string>();
    IndexStorageServiceImpl index_storage_service(m_state);
    SearchServiceImpl search_service(m_state);
    grpc::ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&index_storage_service);
    builder.RegisterService(&search_service);
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    LOGI << "Server listening on " << addr;
    server->Wait();
  }

 private:
  std::shared_ptr<AppState<IndT>> m_state;
  std::string m_addr;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_GRPCSERVER_H
