//
// Created by fumedesk on 27.05.23.
//
#include <Vocabulary.h>

using namespace anezkasearch;

Vocabulary::Vocabulary(VocabularyLang lang) noexcept {
  switch (lang) {
    case VocabularyLang::EN: {
      m_alph_size = 26;
      break;
    }
    case VocabularyLang::RU: {
      m_alph_size = 33;
      break;
    }
  }
  m_root = std::make_shared<TrieNode>();
}

void Vocabulary::Insert(const std::string& key) noexcept {
  std::shared_ptr<TrieNode> current = m_root;
  for (size_t i = 0; i < key.size(); i++) {
    if (not current->children.contains(key.at(i))) {
      current->children.insert({key.at(i), std::make_shared<TrieNode>()});
      current->children[key.at(i)]->letter = key.at(i);
    }
    current = current->children[key.at(i)];
  }
  current->m_is_end = true;
}

void Vocabulary::SearchWords(const std::string& prefix,
                             std::vector<std::string>& words) noexcept {
  std::shared_ptr<TrieNode> current = m_root;

  for (size_t i = 0; i < prefix.size(); i++) {
    if (current->children[prefix[i]]) {
      current = current->children[prefix[i]];
    }
    else {
      return;
    }
  }

  _SearchWords(current, prefix, words);
}

Generator<std::string> Vocabulary::SearchWordsSeq(
    const std::string& prefix) noexcept {
  std::shared_ptr<TrieNode> current = m_root;

  for (size_t i = 0; i < prefix.size(); i++) {
    if (current->children[prefix[i]]) {
      current = current->children[prefix[i]];
    }
    else {
      co_return;
    }
  }

  for (auto w : _SearchWordsSeq(current, prefix)) {
    co_yield w;
  }
}

bool Vocabulary::Contains(const std::string& key) noexcept {
  std::shared_ptr<TrieNode> current = m_root;

  for (size_t i = 0; i < key.size(); i++) {
    if (current->children[key[i]] != nullptr) {
      current = current->children[key[i]];
    }
    else {
      return false;
    }
  }

  if (current->m_is_end) {
    return true;
  }
  return false;
}

void Vocabulary::_SearchWords(  std::shared_ptr<TrieNode> current, std::string word,
                              std::vector<std::string>& words) noexcept {
  if (current->m_is_end) {
    words.push_back(word);
  }

  for (auto [letter, ch] : current->children) {
    if (ch != nullptr) {
      _SearchWords(ch, word + ch->letter, words);
    }
  }
}

Generator<std::string> Vocabulary::_SearchWordsSeq(
    std::shared_ptr<TrieNode> current, std::string word) noexcept {
  if (current->m_is_end) {
    co_yield word;
  }

  for (auto [letter, ch] : current->children) {
    if (ch != nullptr) {
      for (auto w : _SearchWordsSeq(ch,
                                    word + ch->letter)) {
        co_yield w;
      }
    }
  }
}

Vocabulary::~Vocabulary() noexcept {
}
