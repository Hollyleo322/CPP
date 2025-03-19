#pragma once
#include <initializer_list>
#include <limits>

#include "BinaryTree.h"
#include "s21_vector.h"
namespace s21 {
template <typename Key>
class set : public BinaryTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using iterator = typename BinaryTree<Key, Key>::iterator;
  using const_iterator = typename BinaryTree<Key, Key>::const_iterator;
  set() : BinaryTree<Key, Key>() {}
  set(std::initializer_list<value_type> const &items) {
    for (auto it = items.begin(); it != items.end(); it++) {
      BinaryTree<Key, Key>::insert(*it, *it, this->root, 'r');
    }
  }
  set(const set &s) : BinaryTree<Key, Key>(s) {
    if (this->root) {
      BinaryTree<Key, Key>::clear_tree(this->root);
    }
    this->root = BinaryTree<Key, Key>::copy_binary_tree(s);
  }
  set(set &&s) {
    this->root = std::move(s.root);
    s.root = nullptr;
  }
  ~set() { BinaryTree<Key, Key>::clear_obj(); }
  set &operator=(const set &s) {
    if (this != &s) {
      if (this->root) {
        BinaryTree<Key, Key>::clear_tree(this->root);
      }
      this->root = BinaryTree<Key, Key>::copy_binary_tree(s);
    }
    return *this;
  }
  set &operator=(set &&s) {
    if (this != &s) {
      if (this->root == s.root) {
        return s;
      }
      BinaryTree<Key, Key>::clear_tree(this->root);
      this->root = std::move(s.root);
      s.root = nullptr;
    }
    return *this;
  }
  iterator begin() { return BinaryTree<Key, Key>::begin(); }
  iterator end() { return BinaryTree<Key, Key>::end(); }
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
           sizeof(typename BinaryTree<Key, Key>::node);
  }
  void clear() { BinaryTree<Key, Key>::clear_obj(); }
  std::pair<iterator, bool> insert(const value_type &value) {
    std::pair<typename BinaryTree<Key, Key>::iterator, bool> res;
    res.first = BinaryTree<Key, Key>::find_node(value, this->root);
    if (res.first != nullptr && res.first.get_color() != 'w') {
      res.second = false;
    } else {
      BinaryTree<Key, Key>::insert(value, value, this->root, 'r');
      res.first = BinaryTree<Key, Key>::find_node(value, this->root);
      if (res.first != nullptr) {
        res.second = true;
      } else {
        res.second = false;
      }
    }
    return res;
  }
  void erase(iterator pos) {
    BinaryTree<Key, Key>::delete_node(this->root, pos.get_it()->key_node);
  }
  void swap(set &other) { std::swap(this->root, other.root); }
  void merge(set &other) {
    for (auto it = other.begin(); it != other.end(); it++) {
      BinaryTree<Key, Key>::insert(*it, *it, this->root, 'r');
    }
    other.clear();
  }
  iterator find(const Key &key) {
    iterator res = BinaryTree<Key, Key>::find_node(key, this->root);
    if (res == nullptr) {
      res = BinaryTree<Key, Key>::get_max(this->root);
    }
    return res;
  }
  bool contains(const Key &key) {
    bool res = true;
    auto it = BinaryTree<Key, Key>::find_node(key, this->root);
    if (it == nullptr || it->color == 'w') {
      res = false;
    }
    return res;
  }
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    vector<std::pair<iterator, bool>> res;
    if constexpr ((std::is_same_v<Key, Args> && ...)) {
      (res.push_back(this->insert(std::forward<Args>(args))), ...);
    }
    return res;
  }
};
}  // namespace s21