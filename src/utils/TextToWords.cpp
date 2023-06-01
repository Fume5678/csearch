//
// Created by fume on 14.03.23.
//

#include "utils/TextToWords.h"

#include <iostream>

namespace anezkasearch {

TextToWords::TextToWords(std::string_view strv)
    : m_text(strv) {
}

Generator<std::string> TextToWords::GetWordsSeq() {
  std::string word = "";
  bool is_word = false;

  for (size_t i = 0; i < m_text.size()+1; i++) {
    if (i == m_text.size()){
      if(is_word){
        co_yield word;
      }
    }

    if (IsLetter(m_text[i])) {
      is_word = true;
      char c  = std::tolower(m_text[i]);
      word.push_back(c);
    }

    if (!IsLetter(m_text[i]) && is_word) {
      is_word = false;
      co_yield word;
      word = "";
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
