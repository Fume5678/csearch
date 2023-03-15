//
// Created by fume on 14.03.23.
//

#ifndef ANEZKASEARCH_TEXTTOWORDS_H
#define ANEZKASEARCH_TEXTTOWORDS_H

#include <string>
#include <optional>

namespace anezkasearch {


class TextToWords {
 public:
  static inline size_t MIN_WORD_LEN = 3;

  class iterator {
   public:
    iterator(size_t ind, std::string_view strv);
    bool operator<(const iterator& other) const;
    bool operator<=(const iterator& other) const;
    bool operator==(const iterator& other) const;
    bool operator!=(const iterator& other) const;

    std::optional<std::string> operator*() const;
    std::optional<std::string> Get() const;

    int CurrentIndex();

    iterator& operator++();
    void Next();

    friend std::ostream& operator<<(std::ostream& os, const TextToWords::iterator& it);
   private:
    std::string m_word;
    size_t m_current_ind;
    std::string_view m_strv;
  };

  TextToWords(std::string_view strv);
  TextToWords(const TextToWords& other);
  TextToWords& operator=(const TextToWords& other);

  iterator begin();
  iterator end();

 private:
  std::string_view m_strv;

};

} // namespace anezkasearch
#endif  // ANEZKASEARCH_TEXTTOWORDS_H
