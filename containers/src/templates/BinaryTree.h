#pragma once
#include "s21_vector.h"
template <typename key, typename value>
class BinaryTree {
 protected:
  typedef struct node {
    key key_node;
    value value_node;
    node *leftptr;
    node *rightptr;
    node *parent;
    char color;
    node(key a, value b, node *c, char col)
        : key_node(a),
          value_node(b),
          leftptr(nullptr),
          rightptr(nullptr),
          parent(c),
          color(col) {}
  } node;
  node *root;

 public:
  class iterator {
   private:
    using iterator_type = node *;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = iterator_type;
    using reference = iterator_type &;
    using pointer = iterator_type *;

   protected:
    node *it;

   public:
    iterator() : it(nullptr) {}
    iterator(iterator_type ptr) : it(ptr) {}
    iterator(const iterator &val) : it(val.it) {}
    iterator(iterator &&val) {
      this->it = val.it;
      val.it = nullptr;
    }
    const iterator &operator=(const iterator &val) {
      this->it = val.it;
      return *this;
    }
    key operator*() { return it->key_node; }
    const iterator &operator++() {
      if (!this->it->leftptr && !this->it->rightptr &&
          (this->it->parent->key_node < this->it->key_node) &&
          (!this->it->parent->parent ||
           this->it->parent->parent->key_node < this->it->key_node)) {
        key max = this->it->key_node;
        this->it = this->it->parent;
        while (this->it->parent) {
          if (this->it->key_node > max) {
            break;
          }
          this->it = this->it->parent;
        }
      } else if (this->it->rightptr) {
        this->it = this->it->rightptr;
        while (this->it->leftptr) {
          this->it = this->it->leftptr;
        }
      } else if (!this->it->rightptr &&
                 this->it->parent->key_node > this->it->key_node) {
        this->it = this->it->parent;
      } else if (!this->it->leftptr && !this->it->rightptr &&
                 this->it->parent->key_node < this->it->key_node &&
                 this->it->parent->parent) {
        this->it = this->it->parent->parent;
      }
      return *this;
    }
    iterator operator++(int) {
      iterator tmp = *this;
      if (!this->it->leftptr && !this->it->rightptr &&
          (this->it->parent->key_node < this->it->key_node) &&
          (!this->it->parent->parent ||
           this->it->parent->parent->key_node < this->it->key_node)) {
        key max = this->it->key_node;
        this->it = this->it->parent;
        while (this->it->parent) {
          if (this->it->key_node > max) {
            break;
          }
          this->it = this->it->parent;
        }
      } else if (this->it->rightptr) {
        this->it = this->it->rightptr;
        while (this->it->leftptr) {
          this->it = this->it->leftptr;
        }
      } else if (!this->it->rightptr &&
                 this->it->parent->key_node > this->it->key_node) {
        this->it = this->it->parent;
      } else if (!this->it->leftptr && !this->it->rightptr &&
                 this->it->parent->key_node < this->it->key_node &&
                 this->it->parent->parent) {
        this->it = this->it->parent->parent;
      }
      return tmp;
    }
    const iterator &operator--() {
      if (!this->it->leftptr && !this->it->rightptr &&
          this->it->parent->key_node > this->it->key_node &&
          (!this->it->parent->parent ||
           this->it->parent->parent->key_node > this->it->key_node)) {
        key min = this->it->key_node;
        this->it = this->it->parent;
        while (this->it->parent) {
          if (this->it->key_node < min) {
            break;
          }
          this->it = this->it->parent;
        }
      } else if (this->it->leftptr) {
        this->it = this->it->leftptr;
        while (this->it->rightptr) {
          this->it = this->it->rightptr;
        }
      } else if (!this->it->leftptr &&
                 this->it->parent->key_node < this->it->key_node) {
        this->it = this->it->parent;
      } else if (!this->it->leftptr && !this->it->rightptr &&
                 this->it->parent->key_node > this->it->key_node &&
                 this->it->parent->parent) {
        this->it = this->it->parent->parent;
      }
      return *this;
    }
    iterator operator--(int) {
      iterator tmp = *this;
      if (!this->it->leftptr && !this->it->rightptr &&
          this->it->parent->key_node > this->it->key_node &&
          (!this->it->parent->parent ||
           this->it->parent->parent->key_node > this->it->key_node)) {
        key min = this->it->key_node;
        this->it = this->it->parent;
        while (this->it->parent) {
          if (this->it->key_node < min) {
            break;
          }
          this->it = this->it->parent;
        }
      } else if (this->it->leftptr) {
        this->it = this->it->leftptr;
        while (this->it->rightptr) {
          this->it = this->it->rightptr;
        }
      } else if (!this->it->leftptr &&
                 this->it->parent->key_node < this->it->key_node) {
        this->it = this->it->parent;
      } else if (!this->it->leftptr && !this->it->rightptr &&
                 this->it->parent->key_node > this->it->key_node &&
                 this->it->parent->parent) {
        this->it = this->it->parent->parent;
      }
      return tmp;
    }
    bool operator!=(iterator other) { return this->it != other.it; }
    bool operator==(iterator other) { return this->it == other.it; }
    void set_iterator(node *ptr) { this->it = ptr; }
    iterator_type get_it() { return this->it; }
    char get_color() { return it->color; }
    void set_value(const value &var) { this->it->value_node = var; }
    const key &get_key() { return it->key_node; }
    value &get_value() { return it->value_node; }
    void move_iterator() { it++; }
  };
  class const_iterator : public iterator {
   private:
    const node *it;
    const key *first;
    const value *second;

   public:
    using iterator_type = const node *;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = iterator_type;
    using reference = iterator_type &;
    using pointer = iterator_type *;
    const_iterator() : iterator() {}
    const_iterator(node *val) : iterator(val) {}
  };

 public:
  BinaryTree() : root(nullptr) {}
  BinaryTree(const BinaryTree &other) { this->root = copy_binary_tree(other); }
  BinaryTree(const BinaryTree &&other) {
    if (this != &other) {
      this->root = other.root;
      other.root = nullptr;
    }
  }
  ~BinaryTree() { clear_tree(this->root); }
  node *get_root() { return this->root; }
  BinaryTree &operator=(const BinaryTree &other) {
    if (this != &other) {
      clear_tree(this->root);
      this->root = copy_binary_tree(other);
    }
  }
  BinaryTree &operator=(BinaryTree &&other) {
    if (this != &other) {
      this->root = std::move(other.root);
      other.root = nullptr;
    }
  }
  node *bratuha(node *current);
  node *start_of_tree(node *root) const;
  void insert(key key_par, value val_par, node *var, char col);
  void right_rotate(node *root);
  void left_rotate(node *root);
  void swap_color(node *root);
  void delete_node(node *root, key var);
  node *find_node(key var, node *root);
  void delete_node_with_one_child(node *root);
  node *get_max(node *root) const;
  void delete_node_with_black_one(node *root);
  void ptr_to_null(node *current_node);
  void delete_one_case_first(node *root);
  void clear_tree(node *root);
  void clear_obj();
  iterator end() const;
  iterator begin() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
  node *copy_binary_tree(const BinaryTree &other);
};

#include "BinaryTree.tpp"