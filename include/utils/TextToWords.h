//
// Created by fume on 14.03.23.
//

#ifndef ANEZKASEARCH_TEXTTOWORDS_H
#define ANEZKASEARCH_TEXTTOWORDS_H

#include <optional>
#include <string>
#include <utils/Generator.h>

namespace anezkasearch {

class TextToWords {
 public:
  TextToWords(std::string_view strv);

  bool IsLetter(char c);

  // Warn: works only with lvalue objects
  Generator<std::string> GetWordsSeq();

 private :
  std::string_view m_text;
};

}  // namespace anezkasearch
#endif  // ANEZKASEARCH_TEXTTOWORDS_H
