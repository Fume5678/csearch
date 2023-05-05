//
// Created by fume on 13.03.23.
//

#ifndef ANEZKASEARCH_DATAROW_H
#define ANEZKASEARCH_DATAROW_H

#include <Index.h>
#include <optional>

namespace anezkasearch {

template <typename IdT>
  requires ConcIndType<IdT>
class DataRow {
 public:
  IdT id;
  std::string text_data;
};

} // namespace anezkasearch
#endif  // ANEZKASEARCH_DATAROW_H
