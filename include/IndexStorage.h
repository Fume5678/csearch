//
// Created by fume on 09.03.23.
//

#ifndef ANEZKASEARCH_INDEXSTORAGE_H
#define ANEZKASEARCH_INDEXSTORAGE_H

#include <unordered_map>
#include <string>
#include <set>
#include <cstdint>
#include <ranges>
#include <optional>
#include <vector>

namespace anezkasearch {

using IdSet = std::set<uint64_t>;
using IndexMap = std::unordered_map<std::string, IdSet>;

class IndexStorage {
 public:
  IndexStorage();

  void Insert(std::string key, std::uint64_t ind);

  IdSet Get(std::string key) const;


 private:
  IndexMap m_index_storage;
};

} // namespace anezkasearch

#endif  // ANEZKASEARCH_INDEXSTORAGE_H
