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

#include <DataIds.h>

namespace anezkasearch {

template <typename IdT>
using IndexMap = std::unordered_map<std::string, std::set<IdT> >;


template <typename IdT>
  requires ConcIndType<IdT>
class IndexStorage {
 public:
  IndexStorage() {
  }

  std::set<IdT> Get(std::string key) const {
    if (not m_index_storage.contains(key)) {
      return {};
    }

    return m_index_storage.at(key);
  }

  void Insert(std::string key, IdT ind) {
    if (not m_index_storage.contains(key)) {
      m_index_storage.insert({key, {}});
    }
    m_index_storage[key].insert(ind);
  }

  void Remove(std::string key) {
    if (m_index_storage.contains(key)) {
      m_index_storage.erase(key);
    }
  }

  void RemoveInd(IdT ind) {
    // TODO reverse map, for remembering where index is placed for more fastly
    // ind deleting
    for (auto& [k, s] : m_index_storage) {
      s.erase(ind);
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
