//
// Created by fume on 09.03.23.
//

#include "IndexStorage.h"

namespace anezkasearch {

IndexStorage::IndexStorage() {
}

void IndexStorage::Insert(std::string key, std::uint64_t ind) {
  if (not m_index_storage.contains(key)) {
    m_index_storage.insert({key, {}});
  }
  m_index_storage[key].insert(ind);
}

IdSet IndexStorage::Get(
    std::string key) const {

  if(not m_index_storage.contains(key)){
    return {};
  }

  return m_index_storage.at(key);
}

}  // namespace anezkasearch
