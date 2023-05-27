//
// Created by fumedesk on 27.05.23.
//
#include <Vocabulary.h>

using namespace anezkasearch;

void Vocabulary::Insert(const std::string& key) noexcept {
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

std::vector<std::string> Vocabulary::SearchWords(
    const std::string& key) noexcept {
  return std::vector<std::string>();
}

bool Vocabulary::Contains(const std::string& key) noexcept {
  TrieNode* current = &root;
//
//  if (current->children[key[0]] != nullptr) {
//    current = current->children[key[0]];
//  }
//  else {
//    return false;
//  }

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
