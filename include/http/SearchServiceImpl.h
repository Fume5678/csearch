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
    : m_state{state}, m_handler{state}{
  }

  grpc::Status SearchIndex(::grpc::ServerContext* context,
                           const ::anezkasearch::SearchRequest* request,
                           ::anezkasearch::SearchResponse* response) override {
    LOGI << "Search request: " << request->text();

    for(const auto& ind : m_handler.GetIndexes(request->text())){
      if constexpr (std::is_same<IndT, IntInd>::value) {
        response->add_indexes()->set_i_ind(ind);
      }
      else {
        response->add_indexes()->set_s_ind(ind);
      }
    }

    return grpc::Status::OK;
  }

 private:
  std::shared_ptr<AppState<IndT>> m_state;
  SearchRequestHandler<IndT> m_handler;

};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_SEARCHSERVICEIMPL_H
