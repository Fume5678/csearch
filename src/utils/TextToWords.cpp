//
// Created by fume on 14.03.23.
//

#include "utils/TextToWords.h"

#include <iostream>

namespace anezkasearch {

TextToWords::TextToWords(std::string_view strv)
    : m_strv(strv), m_word(""), m_current_ind(0) {
}

Generator<std::string> TextToWords::GetWordsSeq() {
  m_word = "";
  bool is_word = false;

  for (; m_current_ind < m_strv.size(); m_current_ind++) {
    if (IsLetter(m_strv[m_current_ind])) {
      is_word = true;
      char c  = std::tolower(m_strv[m_current_ind]);
      m_word.push_back(c);
    }

    if (!IsLetter(m_strv[m_current_ind]) && is_word) {
      is_word = false;
      co_yield m_word;
      m_word = "";
    }
  }
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
