#pragma once
#include "BinaryTree.h"
namespace s21 {
template <typename Key, typename T>
class map : public BinaryTree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using const_iterator = typename BinaryTree<Key, T>::const_iterator;
  class MapIterator : public BinaryTree<Key, T>::iterator {
   public:
    MapIterator() : BinaryTree<Key, T>::iterator() {}
    MapIterator(typename BinaryTree<Key, T>::iterator val)
        : BinaryTree<Key, T>::iterator(val) {}
    value_type operator*() {
      std::pair<Key, T> res;
      res.first = this->get_key();
      res.second = this->get_value();
      return res;
    }
  };
  using iterator = MapIterator;
  map() : BinaryTree<Key, T>() {}
  map(std::initializer_list<value_type> const &items) {
    for (auto it = items.begin(); it != items.end(); it++) {
      BinaryTree<Key, T>::insert(it->first, it->second, this->root, 'r');
    }
  }
  map(const map &m) : BinaryTree<Key, T>(m) {
    if (this->root) {
      BinaryTree<Key, T>::clear_tree(this->root);
    }
    this->root = BinaryTree<Key, T>::copy_binary_tree(m);
  }
  map(map &&m) {
    this->root = std::move(m.root);
    m.root = nullptr;
  }
  ~map() { BinaryTree<Key, T>::clear_obj(); }
  map &operator=(const map &m) {
    if (this != &m) {
      if (this->root) {
        BinaryTree<Key, T>::clear_tree(this->root);
      }
      this->root = BinaryTree<Key, T>::copy_binary_tree(m);
    }
    return *this;
  }
  map &operator=(map &&m) {
    if (this != &m) {
      this->root = std::move(m.root);
      m.root = nullptr;
    }
    return *this;
  }
  iterator begin() { return iterator(BinaryTree<Key, T>::begin()); }
  iterator end() { return iterator(BinaryTree<Key, T>::end()); }
  bool empty() { return this->root == nullptr; }
  size_type size() {
    size_type res = 0;
    for (auto it = this->begin(); it != this->end(); it++) {
      ++res;
    }
    return res;
  }
  size_type max_size() {
    return std::numeric_limits<size_t>::max() / 2 /
           sizeof(typename BinaryTree<Key, T>::node);
  }
  void clear() { BinaryTree<Key, T>::clear_obj(); }
  std::pair<iterator, bool> insert(const value_type &value) {
    std::pair<iterator, bool> res = insert(value.first, value.second);
    return res;
  }
  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    std::pair<typename BinaryTree<Key, T>::iterator, bool> res;
    res.first = BinaryTree<Key, T>::find_node(key, this->root);
    if (res.first != nullptr && res.first.get_color() != 'w') {
      res.first = BinaryTree<Key, T>::begin();
      res.second = false;
    } else {
      BinaryTree<Key, T>::insert(key, obj, this->root, 'r');
      res.first = BinaryTree<Key, T>::find_node(key, this->root);
      if (res.first != nullptr) {
        res.second = true;
      } else {
        res.first = BinaryTree<Key, T>::begin();
        res.second = false;
      }
    }
    return res;
  }
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    std::pair<typename BinaryTree<Key, T>::iterator, bool> res;
    res.first = BinaryTree<Key, T>::find_node(key, this->root);
    if (res.first != nullptr && res.first.get_color() != 'w') {
      res.first.set_value(obj);
      res.second = true;
    } else {
      BinaryTree<Key, T>::insert(key, obj, this->root, 'r');
      res.first = BinaryTree<Key, T>::find_node(key, this->root);
      if (res.first != nullptr) {
        res.second = true;
      } else {
        res.second = false;
      }
    }
    return res;
  }
  void erase(iterator pos) {
    BinaryTree<Key, T>::delete_node(this->root, pos.get_it()->key_node);
  }
  void swap(map &other) { std::swap(this->root, other.root); }
  void merge(map &other) {
    for (auto it = other.begin(); it != other.end(); it++) {
      BinaryTree<Key, T>::insert((*it).first, (*it).second, this->root, 'r');
    }
    other.clear();
  }
  bool contains(const Key &key) {
    bool res = true;
    auto it = BinaryTree<Key, T>::find_node(key, this->root);
    if (it == nullptr || it->color == 'w') {
      res = false;
    }
    return res;
  }
  T &at(const Key &key) {
    typename BinaryTree<Key, T>::iterator it =
        BinaryTree<Key, T>::find_node(key, this->root);
    if (it == nullptr || (it != nullptr && it.get_color() == 'w')) {
      throw std::out_of_range("out of range");
    }
    return it.get_value();
  }
  typename BinaryTree<Key, T>::iterator find(const Key &key) {
    auto res = BinaryTree<Key, T>::find_node(key, this->root);
    return res;
  }
  T &operator[](const Key &key) {
    typename BinaryTree<Key, T>::iterator it =
        BinaryTree<Key, T>::find_node(key, this->root);
    if (it == nullptr || (it != nullptr && it.get_color() == 'w')) {
      T value(0);
      BinaryTree<Key, T>::insert(key, value, this->get_root(), 'r');
      it = BinaryTree<Key, T>::find_node(key, this->root);
    }
    return it.get_value();
  }
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    vector<std::pair<iterator, bool>> res;
    if constexpr ((std::is_same_v<value_type, Args> && ...)) {
      (res.push_back(this->insert(std::forward<Args>(args))), ...);
    }
    return res;
  }
};
}  // namespace s21