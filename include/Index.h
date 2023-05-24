//
// Created by fume on 13.03.23.
//

#ifndef ANEZKASEARCH_INDEX_H
#define ANEZKASEARCH_INDEX_H

#include <cstdint>
#include <string>
#include <vector>

namespace anezkasearch {

using IntInd = uint64_t;
using StringInd = std::string;

template <typename T>
concept ConcIndType =
    !std::is_reference_v<T> &&
    !std::is_pointer_v<T> &&
    requires {
      typename std::vector<T>;
    } &&
    requires (T a, T b){
      {a < b} -> std::same_as<bool>;
      {a == b} -> std::same_as<bool>;
      {a > b} -> std::same_as<bool>;
    };

} // namespace anezkasearch

#endif  //  ANEZKASEARCH_INDEX_H
