//
// Created by fume on 09.03.23.
//

#include "IndexStorage.h"

#include <algorithm>
#include <ranges>
#include <functional>

namespace anezkasearch {

template <typename IndT>
IndexStorage<IndT>::IndexStorage(std::string m_table_name)
    : m_table_name(m_table_name) {
}

template <typename IndT>
std::set<IndT> IndexStorage<IndT>::Get(std::string key) const {
  if (not m_index_storage.contains(key)) {
    return {};
  }

  return m_index_storage.at(key);
}

template <typename IndT>
void IndexStorage<IndT>::Insert(std::string key, IndT ind) {
  if (not m_index_storage.contains(key)) {
    m_index_storage.insert({key, {}});
  }
  m_index_storage[key].insert(ind);
}

template <typename IndT>
void IndexStorage<IndT>::Remove(std::string key) {
  if (m_index_storage.contains(key)) {
    m_index_storage.erase(key);
  }
}

template <typename IndT>
void IndexStorage<IndT>::RemoveInd(IndT ind) {
  // TODO reverse map, for remembering where index is placed
  for (auto& [k, s] : m_index_storage){
    s.erase(ind);
  }
}

template <typename IndT>
std::string IndexStorage<IndT>::TableName() const {
  return m_table_name;
}

template class anezkasearch::IndexStorage<anezkasearch::IntId>;
template class anezkasearch::IndexStorage<anezkasearch::StringId>;
}  // namespace anezkasearch
