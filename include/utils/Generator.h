//
// Created by fumedesk on 24.05.23.
//

#ifndef ANEZKASEARCH_GENERATOR_H
#define ANEZKASEARCH_GENERATOR_H

#include <coroutine>
#include <optional>

namespace anezkasearch {

template <typename T>
class Generator {
 public:
  struct PromiseType;

  using promise_type = PromiseType;

  struct PromiseType {
    auto get_return_object() noexcept {
      return Generator{Generator::Handle::from_promise(*this)};
    }

    std::suspend_never initial_suspend() noexcept {
      return {};
    }

    std::suspend_always final_suspend() noexcept {
      return {};
    }

    std::suspend_always yield_value(T val) {
      value = val;
      return {};
    }

    void return_void() {
    }
    void unhandled_exception(){};

    T value;
  };

  using Handle = std::coroutine_handle<PromiseType>;

  Generator(Handle handle) : m_coro{handle} {
  }

  ~Generator() noexcept {
    m_coro.destroy();
  }

  class GenIterator {
   public:
    bool operator!=(GenIterator second) const {
      return m_self != second.m_self;
    }

    GenIterator& operator++() {
      if (!m_self->m_coro.done()){
        m_self->m_coro.resume();
      }
      if (m_self->m_coro.done()) {
        m_self = nullptr;
      }
      return *this;
    }

    T operator*() {
      /* достаем значение напрямую из promise */
      return m_self->m_coro.promise().value;
    }

    // TODO implement manually terminating

   private:
    GenIterator(Generator* self) : m_self{self} {
    }
    Generator* m_self;
    friend class Generator;
  };

  /* первое значение корутины уже вычитано благодаря
   * inital_suspend, возвращающим suspend_never
   */
  GenIterator begin() {
    return GenIterator{m_coro.done() ? nullptr : this};
  }
  GenIterator end() {
    return GenIterator{nullptr};
  }

 private:
  Handle m_coro;
};

}  // namespace anezkasearch

#endif  // ANEZKASEARCH_GENERATOR_H
