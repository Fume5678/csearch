//
// Created by fume on 14.03.23.
//

#include "utils/TextToWords.h"

#include <iostream>

namespace anezkasearch {

TextToWords::TextToWords(std::string_view strv)
    : m_strv(strv), m_word(""), m_current_ind(0) {
  Next();
}

TextToWords::operator bool() {
  return m_word.length() >= MIN_WORD_LEN;
}

std::string TextToWords::Get() const {
  return m_word;
}


void TextToWords::Next() {
  m_word = "";
  if (m_current_ind >= m_strv.size()) {
    return;
  }

  bool is_word = false;
  for (; m_current_ind < m_strv.size(); m_current_ind++) {
    if (IsLetter(m_strv[m_current_ind])) {
      is_word = true;
      char c  = std::tolower(m_strv[m_current_ind]);
      m_word.push_back(c);
    }

    if (!IsLetter(m_strv[m_current_ind]) && is_word) {
      is_word = false;
      if (m_word.size() >= MIN_WORD_LEN) {
        return;
      }
      m_word = "";
    }
  }
}
std::ostream& operator<<(std::ostream& os, const TextToWords& text_to_word) {
  os << text_to_word.m_word;
  return os;
}

size_t TextToWords::CurrentIndex() const {
  return m_current_ind;
}
std::string TextToWords::operator*() const {
  return Get();
}

TextToWords& TextToWords::operator++() {
  Next();
  return *this;
}

bool TextToWords::IsLetter(char c) {
  if(std::isspace(c)){
    return false;
  }
  if(std::isblank(c)){
    return false;
  }
  if(std::ispunct(c) && c != '-'){
    return false;
  }

  return true;
}

}  // namespace anezkasearch
