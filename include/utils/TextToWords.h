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

  // TODO move to AppState
  operator bool();

  std::string operator*() const;
  std::string Get() const;

  size_t CurrentIndex() const;

  void Next();
  TextToWords& operator++();

  bool IsLetter(char c);

  friend std::ostream& operator<<(std::ostream& os,
                                  const TextToWords& text_to_word);

  Generator<std::string> GetWordsSeq();

 private : std::string_view m_strv;
  std::string m_word;
  size_t m_current_ind;
};

}  // namespace anezkasearch
#endif  // ANEZKASEARCH_TEXTTOWORDS_H
