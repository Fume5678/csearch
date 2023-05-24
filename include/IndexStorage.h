//
// Created by fume on 09.03.23.
//

#ifndef ANEZKASEARCH_INDEXSTORAGE_H
#define ANEZKASEARCH_INDEXSTORAGE_H

#include <cstdint>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <Index.h>

namespace anezkasearch {

template <typename IdT>
using IndexVector = std::vector<IdT>;

template <typename IdT>
using IndexMap = std::unordered_map<std::string, IndexVector<IdT> >;

template <typename IdT>
  requires ConcIndType<IdT>
class IndexStorage {
 public:
  IndexStorage() {
  }

  IndexVector<IdT> Get(std::string key) const {
    if (not m_index_storage.contains(key)) {
      return {};
    }

    return m_index_storage.at(key);
  }

  void Insert(std::string key, IdT ind) {
    if (not m_index_storage.contains(key)) {
      m_index_storage.insert({key, {}});
    }

    auto& index_vector = m_index_storage[key];

    if(index_vector.empty() || index_vector.front() > ind){
      index_vector.insert(index_vector.begin(), ind);
      return;
    }

    for(int i = index_vector.size()-1; i >= 0; i-- ){
      if(index_vector[i] == ind){
        return;
      }
      if(index_vector[i] < ind){
        index_vector.insert(index_vector.begin() + i + 1, ind);
        return;
      }
    }
  }

  void Remove(std::string key) {
    if (m_index_storage.contains(key)) {
      m_index_storage.erase(key);
    }
  }

  void RemoveInd(IdT ind) {
    // TODO reverse map, for remembering where index is placed for more fastly
    // ind deleting
    for (auto& [k, v] : m_index_storage) {
      for( typename std::vector<IdT>::iterator iter = v.begin(); iter != v.end(); ++iter )
      {
        if( *iter == ind )
        {
          v.erase( iter );
          break;
        }
      }
    }
  }

  void Size(){
    return m_index_storage.size();
  }

 private:
  IndexMap<IdT> m_index_storage;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_INDEXSTORAGE_H
