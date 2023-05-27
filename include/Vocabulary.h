#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <utils/Generator.h>
#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace anezkasearch {

constexpr size_t EN_SIZE = 26;

template <int AlphSize>
class Vocabulary
{
 public:


  class TrieNode {
   public:
    std::array<TrieNode*, AlphSize> children{nullptr};
    bool m_is_end{false};
    char letter{'\0'};
  };


  void Insert(const std::string& key) noexcept {
    TrieNode* current = &root;
    for (size_t i = 0; i < key.size(); i++) {
      if (current->children[key.at(i) - 'a'] == NULL) {
        current->children[key.at(i) - 'a'] = new TrieNode;
        current->children[key.at(i) - 'a']->letter = key.at(i);
      }
      current = current->children[key.at(i) - 'a'];
    }
    current->m_is_end = true;
  }

  void SearchWords(const std::string& prefix,
                               std::vector<std::string>& words) noexcept {
    TrieNode* current = &root;

    for(size_t i = 0; i < prefix.size(); i++){
      if(current->children[prefix[i] - 'a']){
        current = current->children[prefix[i] - 'a'];
      } else {
        return;
      }
    }

    _SearchWords(current, prefix,words);
  }

  bool Contains(const std::string& key) noexcept {
    TrieNode* current = &root;

    for (size_t i = 0; i < key.size(); i++) {
      if (current->children[key[i] - 'a'] != nullptr) {
        current = current->children[key[i] - 'a'];
      } else {
        return false;
      }
    }

    if (current->m_is_end) {
      return true;
    }
    return false;
  }
  

 private:
  TrieNode root;

  void _SearchWords(Vocabulary::TrieNode* current, std::string word,
                                std::vector<std::string>& words) noexcept {
    if(current->m_is_end){
      words.push_back(word);
    }

    for (size_t i = 0; i < AlphSize; i++) {
      if (current->children[i] != nullptr) {
        _SearchWords(current->children[i], word+current->children[i]->letter, words);
      }
    }
  }
};

}  // namespace anezkasearch

#endif
