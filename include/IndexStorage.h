//
// Created by fume on 09.03.23.
//

#ifndef ANEZKASEARCH_INDEXSTORAGE_H
#define ANEZKASEARCH_INDEXSTORAGE_H

#include <unordered_map>
#include <string>
#include <set>
#include <cstdint>
#include <optional>
#include <vector>
#include <memory>

#include <DataIDs.h>

namespace anezkasearch {

template <typename T>
using IndexMap = std::unordered_map<
    std::string,
    std::set<T>
    >;

template <typename IndT>
  requires ConcIndType<IndT>
class IndexStorage {
 public:
  IndexStorage(std::string m_table_name)
      : m_table_name(m_table_name) {
  }
  
  std::set<IndT> Get(std::string key) const {
    if (not m_index_storage.contains(key)) {
      return {};
    }

    return m_index_storage.at(key);
  }

  
  void Insert(std::string key, IndT ind) {
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

  
  void RemoveInd(IndT ind) {
    // TODO reverse map, for remembering where index is placed
    for (auto& [k, s] : m_index_storage){
      s.erase(ind);
    }
  }

  
  std::string TableName() const {
    return m_table_name;
  }


 private:
  IndexMap<IndT> m_index_storage;
  std::string m_table_name;
};

} // namespace anezkasearch


#endif  // ANEZKASEARCH_INDEXSTORAGE_H
