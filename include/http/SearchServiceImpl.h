//
// Created by fumedesk on 10.05.23.
//

#ifndef ANEZKASEARCH_SEARCHSERVICEIMPL_H
#define ANEZKASEARCH_SEARCHSERVICEIMPL_H

#include <AppState.h>
#include <http/SearchRequestHandler.h>
#include <string>

#include <AnezkaSearch.grpc.pb.h>

namespace anezkasearch {

template <typename IndT>
class SearchServiceImpl : public SearchService::Service {
 public:
  SearchServiceImpl(std::shared_ptr<AppState<IndT>> state)
  : m_state{state}{
  }

  grpc::Status SearchIndex(::grpc::ServerContext* context,
                           const ::anezkasearch::SearchRequest* request,
                           ::anezkasearch::SearchResponse* response) override {

    LOGI << "Search request: " << request->text();

    // TODO search index

    return Service::SearchIndex(context, request, response);
  }

 private:
  SearchRequestHandler handler;
  std::shared_ptr<AppState<IndT>> m_state;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_SEARCHSERVICEIMPL_H
