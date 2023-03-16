//
// Created by fume on 13.03.23.
//

#ifndef ANEZKASEARCH_DBCONNECTION_H
#define ANEZKASEARCH_DBCONNECTION_H

#include <optional>
#include <DataIDs.h>

namespace anezkasearch {

template <typename IdT>
  requires ConcIndType<IdT>
class DataRow {
 public:
  IdT id;
  std::string text_data;
};

} // namespace anezkasearch
#endif  // ANEZKASEARCH_DBCONNECTION_H
