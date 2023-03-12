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

namespace anezkasearch {


using IntId = uint64_t;
using StringId = std::string;

template <typename T>
using IndexMap = std::unordered_map<
    std::string,
    std::set<T>
    >;

template <typename IndT>
class IndexStorage {
 public:
  IndexStorage(std::string m_table_name);

  void Insert(std::string key, IndT ind);
  void Remove(std::string key);
  void RemoveInd(IndT ind);

  std::set<IndT> Get(std::string key) const;

  std::string TableName() const;

 private:
  IndexMap<IndT> m_index_storage;
  std::string m_table_name;
};

} // namespace anezkasearch


#endif  // ANEZKASEARCH_INDEXSTORAGE_H
