#pragma once
#include <cstring>
#include <limits>
#include <memory>
#include <utility>
namespace s21 {
template <typename T>
class vector {
 private:
  T *array;
  size_t quantity;
  size_t vector_size;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  vector() : array(nullptr), quantity(0), vector_size(0) {}
  vector(size_type n) : array(nullptr), quantity(n), vector_size(n) {
    array = new value_type[vector_size + 1]{};
  }
  vector(std::initializer_list<value_type> const &items)
      : array(nullptr), quantity(items.size()), vector_size(items.size()) {
    array = new value_type[vector_size + 1];
    try {
      std::uninitialized_copy(items.begin(), items.end(), array);
    } catch (...) {
      throw;
    }
  }
  vector(const vector &v) : vector(v.vector_size) {
    this->quantity = v.quantity;
    try {
      std::uninitialized_copy(v.array, v.array + v.quantity, this->array);
    } catch (...) {
      throw;
    }
  }
  vector(vector &&v) {
    this->quantity = v.quantity;
    this->vector_size = v.vector_size;
    this->array = std::move(v.array);
    v.array = nullptr;
    v.vector_size = 0;
    v.quantity = 0;
  }
  bool operator!=(vector &other) { return this != &other; }
  ~vector() {
    call_destructor();
    delete[] reinterpret_cast<char *>(this->array);
  }
  vector &operator=(const vector &v) {
    if (this != &v) {
      if (this->array) {
        call_destructor();
        delete[] this->array;
      }
      this->quantity = v.quantity;
      this->vector_size = v.vector_size;
      this->array = new value_type[this->vector_size];
      try {
        std::uninitialized_copy(v.array, v.array + v.vector_size, this->array);
      } catch (...) {
        throw;
      }
    }
    return *this;
  }
  const vector &operator=(vector &&v) {
    if (this != &v) {
      if (this->array) {
        call_destructor();
        delete[] this->array;
      }
      this->quantity = v.quantity;
      this->vector_size = v.vector_size;
      this->array = std::move(v.array);
      v.array = nullptr;
      v.vector_size = 0;
      v.quantity = 0;
    }
    return *this;
  }
  reference at(size_type pos) {
    if (pos > this->quantity) {
      throw std::out_of_range("out of range");
    }
    return *(this->array + pos);
  }
  reference operator[](size_type pos) { return *(this->array + pos); }
  const_reference front() { return *this->array; }
  const_reference back() { return *(this->array + quantity - 1); }
  T *data() { return this->array; }
  iterator begin() { return this->array; }
  iterator end() { return this->array + quantity; }
  bool empty() { return this->quantity == 0; }
  size_type size() { return this->quantity; }
  size_type max_size() {
    return std::numeric_limits<size_t>::max() / 2 / sizeof(vector);
  }
  void reserve(size_type size) {
    if (size < this->quantity) {
      return;
    } else {
      T *tmp_array = reinterpret_cast<T *>(new char[size * sizeof(T)]);
      try {
        std::uninitialized_copy(this->array, this->array + this->quantity,
                                tmp_array);
      } catch (...) {
        delete[] reinterpret_cast<char *>(tmp_array);
        throw;
      }
      this->call_destructor();
      delete[] reinterpret_cast<char *>(this->array);
      this->array = tmp_array;
      this->vector_size = size;
      tmp_array = nullptr;
    }
  }
  size_type capacity() { return this->vector_size; }
  void shrink_to_fit() {
    T *tmp_array = new value_type[this->quantity + 1];
    try {
      std::uninitialized_copy(this->array, this->end(), tmp_array);
    } catch (...) {
      delete[] reinterpret_cast<char *>(tmp_array);
      throw;
    }
    this->call_destructor();
    delete[] reinterpret_cast<char *>(this->array);
    this->array = tmp_array;
    this->vector_size = this->quantity;
  }
  void clear() {
    this->call_destructor();
    this->quantity = 0;
  }
  iterator insert(iterator pos, const_reference value) {
    size_t moves = pos - this->array;
    if ((size_t)(pos - this->array) > this->vector_size + 1) {
      throw std::out_of_range("out of range");
    } else {
      if (this->quantity == this->vector_size) {
        if (this->vector_size == 0 || this->vector_size == 1) {
          this->vector_size += 1;
        } else {
          this->vector_size *= 2;
        }
      }
      T *tmp_array = new value_type[this->vector_size + 1];
      try {
        std::uninitialized_copy(this->array, pos, tmp_array);
      } catch (...) {
        delete[] reinterpret_cast<char *>(tmp_array);
        throw;
      }
      try {
        new (tmp_array + moves) T(value);
      } catch (...) {
        (tmp_array + moves)->~T();
        for (size_t i = 0; i <= moves; i++) {
          (tmp_array + i)->~T();
        }
        delete[] reinterpret_cast<char *>(tmp_array);
        throw;
      }
      try {
        std::uninitialized_copy(pos, this->end(), tmp_array + moves + 1);
      } catch (...) {
        for (size_t i = 0; i <= moves; i++) {
          (tmp_array + i)->~T();
        }
        delete[] reinterpret_cast<char *>(tmp_array);
        throw;
      }
      this->call_destructor();
      delete[] reinterpret_cast<char *>(this->array);
      this->array = tmp_array;
      this->quantity += 1;
    }
    return this->array + moves;
  }
  void erase(iterator pos) {
    if ((size_t)(pos - this->array) > this->quantity + 1) {
      throw std::out_of_range("out of range");
    }
    if (pos == this->array) {
      try {
        std::uninitialized_copy(pos + 1, this->end(), this->array);
      } catch (...) {
        throw;
      }
    } else {
      T *tmp_array = new value_type[this->vector_size + 1];
      try {
        std::uninitialized_copy(this->array, pos, tmp_array);
      } catch (...) {
        delete[] reinterpret_cast<char *>(tmp_array);
        throw;
      }
      try {
        std::uninitialized_copy(pos + 1, this->end(),
                                tmp_array + (pos - tmp_array));
      } catch (...) {
        for (long int i = 0; i < (pos - tmp_array); i++) {
          (tmp_array + i)->~T();
        }
        delete[] reinterpret_cast<char *>(tmp_array);
        throw;
      }
      call_destructor();
      delete[] reinterpret_cast<char *>(this->array);
      this->array = tmp_array;
    }
    this->quantity -= 1;
  }
  void call_destructor() {
    for (size_t i = 0; i < this->quantity; i++) {
      (this->array + i)->~T();
    }
  }
  void push_back(const_reference value) { this->insert(this->end(), value); }
  void pop_back() {
    (this->array + this->quantity - 1)->~T();
    this->quantity -= 1;
  }
  void swap(vector &other) { std::swap(*this, other); }
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    size_t moves = const_cast<iterator>(pos) - this->array;
    this->reserve(this->vector_size + 1 + sizeof...(args));
    iterator res = nullptr;
    if constexpr ((std::is_same_v<T, Args> && ...)) {
      res = (this->insert(this->array + moves, std::forward<Args>(args)), ...);
    }
    return res;
  }
  template <typename... Args>
  void insert_many_back(Args &&...args) {
    if constexpr ((std::is_same_v<T, Args> && ...)) {
      (this->push_back(std::forward<Args>(args)), ...);
    }
  }
};
}  // namespace s21