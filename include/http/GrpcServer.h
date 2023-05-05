//
// Created by fume on 27.04.23.
//

#ifndef ANEZKASEARCH_GRPCSERVER_H
#define ANEZKASEARCH_GRPCSERVER_H

#include <AppState.h>

namespace anezkasearch {

template<typename IndT>
class GrpcServer {
 public:
  GrpcServer(std::shared_ptr<AppState<IndT>> state) : m_state{state}{
  }

  void Run();

  void HandleConnection();

 private:
  std::shared_ptr<AppState<IndT>> m_state;
  std::string m_addr;

};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_GRPCSERVER_H
