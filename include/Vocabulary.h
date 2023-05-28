#ifndef ANEZKASEARCH_VOCABULARY_H
#define ANEZKASEARCH_VOCABULARY_H

#include <utils/Generator.h>
#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace anezkasearch {

constexpr size_t EN_SIZE = 26;

class Vocabulary {
 public:
  class TrieNode {
   public:
    TrieNode(size_t alphs_size) : children{alphs_size} {
      std::ranges::fill(children, nullptr);
    }

    std::vector<TrieNode*> children;
    bool m_is_end{false};
    char letter{'\0'};
  };

  explicit Vocabulary(size_t alph_size) noexcept;

  void Insert(const std::string& key) noexcept;

  void SearchWords(const std::string& prefix,
                   std::vector<std::string>& words) noexcept;
  Generator<std::string> SearchWordsSeq(const std::string& prefix) noexcept;

  bool Contains(const std::string& key) noexcept;

 private:
  TrieNode m_root;
  size_t m_alph_size;

  void _SearchWords(Vocabulary::TrieNode* current, std::string word,
                    std::vector<std::string>& words) noexcept;

  Generator<std::string> _SearchWordsSeq(Vocabulary::TrieNode* current,
                                         std::string word) noexcept;
};

}  // namespace anezkasearch

#endif
