#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <string>
#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include <utils/Generator.h>

namespace anezkasearch {

class Vocabulary {
 public:

  class TrieNode{
   public:
    std::array<TrieNode*, 26> children{nullptr};
    bool m_is_end{false};
    char letter{'\0'};
  };


  void Insert(const std::string& key) noexcept;

  std::vector<std::string> SearchWords(const std::string& key) noexcept;

  Generator<std::string> SearchWordsSeq(const std::string& key) noexcept;

  bool Contains(const std::string& key) noexcept;

  void PrintLexical (TrieNode * current, std::string prefix, std::string suffix) {
    if (current->m_is_end and suffix.size() != 0) {
      std::cout << prefix+suffix << std::endl;
    }
    for (int i=0; i<26; i++) {
      std::string temp = suffix;
      if (current->children[i]) {
        temp += current->children[i]->letter;
        PrintLexical(current->children[i], prefix, temp);
      }
    }
  }

  void Print(){
    PrintLexical(&root, "", "");
  }
 private:
  TrieNode root;

};

}  // namespace anezkasearch

#endif