//
// Created by fume on 13.03.23.
//

#ifndef ANEZKASEARCH_DATAIDS_H
#define ANEZKASEARCH_DATAIDS_H

#include <cstdint>
#include <string>
#include <set>

namespace anezkasearch {

using IntId = uint64_t;
using StringId = std::string;

template <typename T>
concept ConcIndType =
    !std::is_reference_v<T> &&
    !std::is_pointer_v<T> &&
    requires {
      typename std::set<T>;
    };

} // namespace anezkasearch

#endif  //  ANEZKASEARCH_DATAIDS_H
