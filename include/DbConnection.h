//
// Created by fume on 13.03.23.
//

#ifndef ANEZKASEARCH_DBCONNECTION_H
#define ANEZKASEARCH_DBCONNECTION_H

#include <optional>
#include <DataIDs.h>

namespace anezkasearch {

template <typename IndT>
  requires ConcIndType<IndT>
class DataRow {
 public:
  IndT id;
  std::string text_data;
};

template <typename IndT>
class DBConnection {
 public:
  virtual void Open() = 0;
  virtual void Close() = 0;
  virtual std::optional<DataRow<IndT>> Next() = 0;
};

} // namespace anezkasearch
#endif  // ANEZKASEARCH_DBCONNECTION_H
