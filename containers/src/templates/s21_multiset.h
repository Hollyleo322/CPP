#pragma once
#include "BinaryTree.h"
#include "s21_map.h"
namespace s21 {
template <typename Key>
class multiset : public BinaryTree<Key, size_t> {
 private:
  s21::map<Key, size_t> multi;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using const_iterator = typename BinaryTree<Key, size_t>::const_iterator;
  class MultisetIterator : public BinaryTree<Key, size_t>::iterator {
   private:
    multiset<Key> *ptr;

   public:
    MultisetIterator() : BinaryTree<Key, size_t>::iterator(), ptr(nullptr) {}
    MultisetIterator(typename BinaryTree<Key, size_t>::iterator val,
                     multiset<Key> *map)
        : BinaryTree<Key, size_t>::iterator(val), ptr(map) {}
    MultisetIterator operator++() {
      if (this->get_value() != 1) {
        size_t val = this->get_value();
        val -= 1;
        this->set_value(val);
      } else {
        ptr->return_quantity(this->get_key());
        BinaryTree<Key, size_t>::iterator::operator++();
      }
      return *this;
    }
    MultisetIterator operator++(int) {
      MultisetIterator res = *this;
      if (this->get_value() != 1) {
        size_t val = this->get_value();
        val -= 1;
        this->set_value(val);
      } else {
        ptr->return_quantity(this->get_key());
        BinaryTree<Key, size_t>::iterator::operator++();
      }
      return res;
    }
    MultisetIterator operator--() {
      if (this->get_value() != 1) {
        size_t val = this->get_value();
        val -= 1;
        this->set_value(val);
      } else {
        ptr->return_quantity(this->get_key());
        BinaryTree<Key, size_t>::iterator::operator--();
      }
    }
    MultisetIterator operator--(int) {
      MultisetIterator res = *this;
      if (this->get_value() != 1) {
        size_t val = this->get_value();
        val -= 1;
        this->set_value(val);
      } else {
        ptr->return_quantity(this->get_key());
        BinaryTree<Key, size_t>::iterator::operator--();
      }
      return res;
    }
  };
  using iterator = MultisetIterator;
  multiset() : BinaryTree<Key, size_t>() {}
  multiset(std::initializer_list<value_type> const &items) {
    for (auto it = items.begin(); it != items.end(); it++) {
      if (!this->root || this->find(*it).get_color() == 'w') {
        BinaryTree<Key, size_t>::insert(*it, 1, this->root, 'r');
      } else {
        if (multi.find(*it) == nullptr || multi.find(*it).get_color() == 'w') {
          this->find(*it).set_value(2);
          multi.insert_or_assign(*it, 2);
        } else {
          size_t sum = this->find(*it).get_value();
          multi.insert_or_assign(*it, multi.find(*it).get_value() + 1);
          this->find(*it).set_value(sum + 1);
        }
      }
    }
  }
  multiset(const multiset &ms) : BinaryTree<Key, size_t>(ms) {
    if (this->root) {
      BinaryTree<Key, size_t>::clear_tree(this->root);
    }
    this->root = BinaryTree<Key, size_t>::copy_binary_tree(ms);
    this->multi = ms.multi;
  }
  multiset(multiset &&ms) {
    if (this->root) {
      BinaryTree<Key, size_t>::clear_tree(this->root);
    }
    this->root = std::move(ms.root);
    this->multi = std::move(ms.multi);
    ms.root = nullptr;
  }
  ~multiset() {
    BinaryTree<Key, size_t>::clear_obj();
    multi.clear_obj();
  }
  multiset &operator=(multiset &&ms) {
    if (this != &ms) {
      if (this->root) {
        BinaryTree<Key, size_t>::clear_tree(this->root);
      }
      this->root = std::move(ms.root);
      this->multi = std::move(ms.multi);
      ms.root = nullptr;
    }
    return *this;
  }
  multiset &operator=(const multiset &ms) {
    if (this != &ms) {
      if (this->root) {
        BinaryTree<Key, size_t>::clear_tree(this->root);
      }
      this->root = BinaryTree<Key, size_t>::copy_binary_tree(ms);
      this->multi = ms.multi;
    }
    return *this;
  }
  iterator find(const Key &key) {
    auto res = BinaryTree<Key, size_t>::find_node(key, this->root);
    if (res == nullptr) {
      res = BinaryTree<Key, size_t>::get_max(this->root);
    }
    return MultisetIterator(res, this);
  }
  iterator begin() {
    return MultisetIterator(BinaryTree<Key, size_t>::begin(), this);
  }
  iterator end() {
    return MultisetIterator(BinaryTree<Key, size_t>::end(), this);
  }
  bool empty() { return this->root == nullptr; }
  size_type size() {
    size_type res = 0;
    for (auto it = this->begin(); it != this->end(); ++it) {
      res++;
    }
    return res;
  }
  size_type max_size() {
    return std::numeric_limits<size_t>::max() / 2 /
           (sizeof(typename BinaryTree<Key, size_t>::node) +
            sizeof(s21::map<Key, size_t>));
  }
  void clear() {
    BinaryTree<Key, size_t>::clear_obj();
    multi.clear();
  }
  iterator insert(const value_type &value) {
    if (!this->root || this->find(value) == nullptr ||
        this->find(value).get_color() == 'w') {
      BinaryTree<Key, size_t>::insert(value, 1, this->root, 'r');
    } else {
      if (multi.find(value) == nullptr ||
          multi.find(value).get_color() == 'w') {
        this->find(value).set_value(2);
        multi.insert_or_assign(value, 2);
      } else {
        size_t sum = this->find(value).get_value();
        multi.insert_or_assign(value, multi.find(value).get_value() + 1);
        this->find(value).set_value(sum + 1);
      }
    }
    return this->find(value);
  }
  void erase(iterator pos) {
    if (multi.contains(pos.get_key())) {
      multi[pos.get_key()] -= 1;
      pos.set_value(multi[pos.get_key()]);
      if (multi[pos.get_key()] == 0) {
        multi.erase(multi.find(pos.get_key()));
        BinaryTree<Key, size_t>::delete_node(this->root,
                                             pos.get_it()->key_node);
      }
    } else {
      BinaryTree<Key, size_t>::delete_node(this->root, pos.get_it()->key_node);
    }
  }
  void swap(multiset &other) { std::swap(this->root, other.root); }
  void merge(multiset &other) {
    for (auto it = other.begin(); it != other.end(); it++) {
      this->insert(*it);
    }
    other.clear();
  }
  size_type count(const Key &key) {
    size_type cnt = 0;
    if (this->find(key) != nullptr && this->find(key).get_color() != 'w') {
      auto it = multi.find(key);
      if (it != nullptr) {
        cnt = it.get_value();
      } else {
        cnt = 1;
      }
    }
    return cnt;
  }
  bool contains(const Key &key) {
    bool res = true;
    auto it = BinaryTree<Key, size_t>::find_node(key, this->root);
    if (it == nullptr || it->color == 'w') {
      res = false;
    }
    return res;
  }
  std::pair<iterator, iterator> equal_range(const Key &key) {
    std::pair<iterator, iterator> res;
    typename BinaryTree<Key, size_t>::iterator it =
        BinaryTree<Key, size_t>::find_node(key, this->root);
    if (it == nullptr || it.get_color() == 'w') {
      res.first = MultisetIterator(BinaryTree<Key, size_t>::end(), this);
      res.second = res.first;
    } else {
      res.first = MultisetIterator(it, this);
      it++;
      res.second = MultisetIterator(it, this);
    }
    return res;
  }
  void return_quantity(const Key &key) {
    auto it = this->find(key);
    size_t quant = 1;
    auto check = multi.find(key);
    if (check != nullptr && check.get_color() != 'w') {
      quant = multi.at(key);
    }
    it.set_value(quant);
  }
  iterator lower_bound(const Key &key) {
    auto it = this->begin();
    while (key > *it && it != this->end()) {
      it++;
    }
    return it;
  }
  iterator upper_bound(const Key &key) {
    auto it = this->begin();
    while (key >= *it && it != this->end()) {
      it++;
    }
    return it;
  }
  std::pair<iterator, bool> insert_for_many(const value_type &value) {
    std::pair<iterator, bool> res;
    res.first = MultisetIterator(
        BinaryTree<Key, size_t>::find_node(value, this->root), this);
    if (res.first != nullptr && res.first.get_color() != 'w') {
      res.second = false;
    } else {
      BinaryTree<Key, size_t>::insert(value, 1, this->root, 'r');
      res.first = MultisetIterator(
          BinaryTree<Key, size_t>::find_node(value, this->root), this);
      if (res.first != nullptr) {
        res.second = true;
      } else {
        res.second = false;
      }
    }
    return res;
  }
  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    vector<std::pair<iterator, bool>> res;
    if constexpr ((std::is_same_v<Key, Args> && ...)) {
      (res.push_back(this->insert_for_many(std::forward<Args>(args))), ...);
    }
    return res;
  }
};
}  // namespace s21