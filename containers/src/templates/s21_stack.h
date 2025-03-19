#pragma once
#include <utility>
namespace s21 {
template <typename T>
class stack {
 private:
  T *array;
  size_t quantity;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  stack() : array(nullptr), quantity(0) {}
  stack(std::initializer_list<value_type> const &items)
      : array(new value_type[items.size()]{}), quantity(items.size()) {
    try {
      std::uninitialized_copy(items.begin(), items.end(), array);
    } catch (...) {
      throw;
    }
  }
  stack(const stack &s)
      : array(new value_type[s.quantity]{}), quantity(s.quantity) {
    if (this != &s) {
      try {
        std::uninitialized_copy(s.array, s.array + (s.quantity), array);
      } catch (...) {
        delete[] this->array;
        throw;
      }
    }
  }
  stack(stack &&s) {
    if (this != &s) {
      this->array = std::move(s.array);
      this->quantity = s.quantity;
      s.quantity = 0;
      s.array = nullptr;
    }
  }
  reference operator[](size_t val) { return *(this->array + val); }
  stack &operator=(const stack &s) {
    if (this != &s) {
      if (this->quantity) {
        delete[] this->array;
        this->array = nullptr;
      }
      if (!this->array) {
        this->array = new value_type[s.quantity]{};
      }
      try {
        std::uninitialized_copy(s.array, s.array + s.quantity, array);
      } catch (...) {
        throw;
      }
    }
    this->quantity = s.quantity;
    return *this;
  }
  stack &operator=(stack &&s) {
    if (this != &s) {
      this->array = std::move(s.array);
      this->quantity = s.quantity;
      s.quantity = 0;
      s.array = nullptr;
    }
    return *this;
  }
  ~stack() { delete[] array; }
  const_reference top() { return *(this->array + (this->quantity - 1)); }
  bool empty() { return this->quantity == 0; }
  size_type size() { return this->quantity; }
  void push(const_reference value) {
    rewrite_stack();
    try {
      new (this->array + this->quantity - 1) T(value);
    } catch (...) {
      (this->array + this->quantity - 1)->~T();
      throw;
    }
  }
  void rewrite_stack() {
    value_type *tmp = new value_type[this->quantity + 1];
    if (this->quantity) {
      try {
        std::uninitialized_copy(this->array, this->array + this->quantity, tmp);
      } catch (...) {
        delete[] reinterpret_cast<char *>(tmp);
        throw;
      }
    }
    this->quantity += 1;
    delete[] this->array;
    this->array = tmp;
  }
  void pop() {
    (this->array + this->quantity - 1)->~T();
    this->quantity -= 1;
  }
  void swap(stack &other) { std::swap(*this, other); }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    if constexpr ((std::is_same_v<T, Args> && ...)) {
      (this->push(std::forward<Args>(args)), ...);
    }
  }
};
}  // namespace s21
