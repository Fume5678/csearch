//
// Created by fume on 14.03.23.
//

#include <TextToWords.h>

namespace anezkasearch {

TextToWords::TextToWords(std::string_view strv) : m_strv{strv} {
}

TextToWords::TextToWords(const TextToWords& other) : m_strv{other.m_strv} {
}

TextToWords& TextToWords::operator=(const TextToWords& other) {
  m_strv = other.m_strv;
  return *this;
}

TextToWords::iterator TextToWords::begin() {
  return {0, m_strv};
}

TextToWords::iterator TextToWords::end() {
  return {m_strv.size(), m_strv};
}

bool TextToWords::iterator::operator<(
    const TextToWords::iterator& other) const {
  return m_current_ind < other.m_current_ind;
}

bool TextToWords::iterator::operator<=(
    const TextToWords::iterator& other) const {
  return m_current_ind <= other.m_current_ind;
}

bool TextToWords::iterator::operator==(
    const TextToWords::iterator& other) const {
  return m_current_ind == other.m_current_ind;
}

bool TextToWords::iterator::operator!=(
    const TextToWords::iterator& other) const {
  return m_current_ind != other.m_current_ind;
}

std::optional<std::string> TextToWords::iterator::operator*() const {
  return Get();
}

std::optional<std::string> TextToWords::iterator::Get() const {
  if (m_current_ind >= m_strv.size()) {
    return std::nullopt;
  }
  if (m_word.size() < TextToWords::MIN_WORD_LEN) {
    return std::nullopt;
  }
  return {m_word};
}

int TextToWords::iterator::CurrentIndex() {
  return m_current_ind;
}

std::ostream& operator<<(std::ostream& os, const TextToWords::iterator& it) {
  os << it.m_word;
  return os;
}
void TextToWords::iterator::Next() {
  m_word = "";
  if (m_current_ind >= m_strv.size()) {
    return;
  }

  bool is_word = false;
  for (; m_current_ind < m_strv.size(); m_current_ind++) {
    if (std::isalpha(m_strv[m_current_ind])) {
      is_word = true;
      char c = std::tolower(m_strv[m_current_ind]);
      m_word.push_back(c);
    }

    if (!std::isalpha(m_strv[m_current_ind]) && is_word) {
      is_word = false;
      if (m_word.size() >= MIN_WORD_LEN) {
        return;
      }
      m_word = "";
    }
  }
}

TextToWords::iterator& TextToWords::iterator::operator++() {
  Next();
  return *this;
}
TextToWords::iterator::iterator(size_t ind, std::string_view strv)
    : m_current_ind{ind}, m_strv(strv) {
  Next();
}

}  // namespace anezkasearch
