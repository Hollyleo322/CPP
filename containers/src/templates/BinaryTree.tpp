#pragma once
template <typename key, typename value>
typename BinaryTree<key, value>::node *BinaryTree<key, value>::bratuha(
    BinaryTree<key, value>::node *other) {
  node *res;
  if (other->parent->leftptr == other) {
    res = other->parent->rightptr;
  } else {
    res = other->parent->leftptr;
  }
  return res;
}
template <typename key, typename value>
typename BinaryTree<key, value>::node *BinaryTree<key, value>::start_of_tree(
    BinaryTree<key, value>::node *other) const {
  if (!this->root) {
    return nullptr;
  } else {
    while (other->leftptr) {
      other = other->leftptr;
    }
  }
  return other;
}
template <typename key, typename value>
void BinaryTree<key, value>::insert(key key_par, value val_par, node *var,
                                    char col) {
  if (!this->root) {
    this->root = new node(key_par, val_par, nullptr, col);
    this->root->color = 'b';
    this->root->rightptr = new node(key_par + 1, val_par, this->root, 'w');
  } else {
    if (this->get_max(this->root)->color == 'w') {
      node *tmp = this->get_max(this->root);
      tmp->parent->rightptr = nullptr;
      delete tmp;
    }
    if (var->key_node > key_par) {
      if (var->leftptr) {
        insert(key_par, val_par, var->leftptr, col);
      } else {
        var->leftptr = new node(key_par, val_par, var, col);
      }
    }
    if (var->key_node < key_par) {
      if (var->rightptr) {
        insert(key_par, val_par, var->rightptr, col);
      } else {
        var->rightptr = new node(key_par, val_par, var, col);
      }
    }
    if (var->leftptr && var->leftptr->leftptr && var->leftptr->color == 'r' &&
        var->leftptr->leftptr->color == 'r') {
      right_rotate(var);
    } else if (var->rightptr && (!var->leftptr || var->leftptr->color == 'b') &&
               var->rightptr->color == 'r') {
      left_rotate(var);
    } else if (var->leftptr && var->rightptr && var->leftptr->color == 'r' &&
               var->rightptr->color == 'r') {
      swap_color(var);
    }
  }
  if (this->root->color == 'r') {
    this->root->color = 'b';
  }
  if (this->get_max(this->root)->color != 'w') {
    insert(this->get_max(this->root)->key_node + 1, val_par, this->root, 'w');
  }
}
template <typename key, typename value>
void BinaryTree<key, value>::right_rotate(node *root) {
  node *new_root = root->leftptr;
  char tmp = new_root->color;
  if (root->color == 'r') {
    new_root->color = 'r';
  } else {
    new_root->color = 'b';
  }
  root->leftptr = new_root->rightptr;
  if (root->leftptr) {
    root->leftptr->parent = root;
  }
  new_root->rightptr = root;
  if (!root->parent) {
    new_root->parent = nullptr;
  } else {
    new_root->parent = root->parent;
    if (root->parent) {
      if (root->parent->leftptr == root) {
        root->parent->leftptr = new_root;
      } else {
        root->parent->rightptr = new_root;
      }
    }
  }
  if (tmp == 'r') {
    root->color = 'r';
  } else {
    root->color = 'b';
  }
  root->parent = new_root;
  if (new_root->leftptr && new_root->rightptr &&
      new_root->leftptr->color == 'r' && new_root->rightptr->color == 'r') {
    swap_color(new_root);
  }
  if (root == this->root) {
    this->root = new_root;
    if (this->root->color == 'r') {
      this->root->color = 'b';
    }
  }
}
template <typename key, typename value>
void BinaryTree<key, value>::left_rotate(node *root) {
  node *new_root = root->rightptr;
  if (root->color == 'r') {
    new_root->color = 'r';
  } else {
    new_root->color = 'b';
  }
  root->rightptr = new_root->leftptr;
  if (root->rightptr) {
    root->rightptr->parent = root;
  }
  root->color = 'r';
  new_root->leftptr = root;
  if (!root->parent) {
    new_root->parent = nullptr;
  } else {
    new_root->parent = root->parent;
    if (root->parent) {
      if (root->parent->leftptr == root) {
        root->parent->leftptr = new_root;
      } else {
        root->parent->rightptr = new_root;
      }
    }
  }
  root->parent = new_root;
  if (new_root->leftptr && new_root->rightptr &&
      new_root->leftptr->color == 'r' && new_root->rightptr->color == 'r') {
    swap_color(new_root);
  }
  if (root == this->root) {
    this->root = new_root;
    if (this->root->color == 'r') {
      this->root->color = 'b';
    }
  }
}
template <typename key, typename value>
void BinaryTree<key, value>::swap_color(node *root) {
  if (root) {
    if (root->leftptr) {
      root->leftptr->color == 'r' ? root->leftptr->color = 'b'
                                  : root->leftptr->color = 'r';
    }
    if (root->rightptr) {
      root->rightptr->color == 'r' ? root->rightptr->color = 'b'
                                   : root->rightptr->color = 'r';
    }
    root->color == 'r' ? root->color = 'b' : root->color = 'r';
  }
}
template <typename key, typename value>
void BinaryTree<key, value>::delete_node(node *root, key var) {
  key white = 0;
  value white_val = 0;
  if (this->get_max(this->root)->color == 'w') {
    white = this->get_max(this->root)->key_node;
    white_val = this->get_max(this->root)->value_node;
    node *tmp = this->get_max(this->root);
    tmp->parent->rightptr = nullptr;
    delete tmp;
  }
  node *current_node = find_node(var, root);
  if (current_node->leftptr && current_node->rightptr) {
    node *max = get_max(current_node->leftptr);
    current_node->key_node = max->key_node;
    current_node->value_node = max->value_node;
    current_node = max;
  }
  if (!current_node->leftptr && !current_node->rightptr) {
    if (current_node->color == 'r') {
      ptr_to_null(current_node);
      delete current_node;
    } else {
      delete_node_with_black_one(current_node);
      ptr_to_null(current_node);
      if (current_node == this->root) {
        this->root = nullptr;
      }
      delete current_node;
    }
  } else if ((current_node->leftptr && !current_node->rightptr) ||
             (!current_node->leftptr && current_node->rightptr)) {
    delete_node_with_one_child(current_node);
    if (current_node->leftptr) {
      delete current_node->leftptr;
      current_node->leftptr = nullptr;
    } else {
      node *tmp = nullptr;
      if (current_node->rightptr->rightptr) {
        tmp = current_node->rightptr->rightptr;
      }
      delete current_node->rightptr;
      if (tmp) {
        current_node->rightptr = tmp;
      } else {
        current_node->rightptr = nullptr;
      }
    }
  }
  if (this->root && this->get_max(this->root)->color != 'w') {
    insert(white, white_val, this->root, 'w');
  }
}
template <typename key, typename value>
void BinaryTree<key, value>::ptr_to_null(node *current_node) {
  if (current_node->parent) {
    if (current_node->parent->leftptr == current_node) {
      current_node->parent->leftptr = nullptr;
    } else {
      current_node->parent->rightptr = nullptr;
    }
  }
}
template <typename key, typename value>
void BinaryTree<key, value>::delete_node_with_black_one(node *root) {
  if (root != this->root) {
    delete_one_case_first(root);
  }
}
template <typename key, typename value>
void BinaryTree<key, value>::delete_one_case_first(node *root) {
  node *brat = bratuha(root);
  if (root->parent->color == 'r' && (!brat || brat->color == 'b') &&
      ((!brat->leftptr && !brat->rightptr) ||
       (brat->leftptr && brat->rightptr && brat->leftptr->color == 'b' &&
        brat->rightptr->color == 'b'))) {
    root->parent->color = 'b';
    brat->color = 'r';
  } else if (root->parent->color == 'b' && (!brat || brat->color == 'b') &&
             ((!brat->leftptr && !brat->rightptr) ||
              (brat->leftptr && brat->rightptr && brat->leftptr->color == 'b' &&
               brat->rightptr->color == 'b'))) {
    brat->color = 'r';
    delete_node_with_black_one(root->parent);
  } else if (root->parent->color == 'b' && brat->color == 'r') {
    if (root->parent->leftptr == root) {
      left_rotate(root->parent);
      delete_node_with_black_one(root);
    } else {
      right_rotate(root->parent);
      delete_node_with_black_one(root);
    }
  } else if (brat) {
    node *near;
    node *far;
    if (root->parent->leftptr == root) {
      near = brat->leftptr;
      far = brat->rightptr;
    } else {
      near = brat->rightptr;
      far = brat->leftptr;
    }
    if ((near && near->color == 'r') && (!far || far->color == 'b') &&
        root->parent->leftptr == root) {
      right_rotate(brat);
      delete_node_with_black_one(root);
    } else if ((near && near->color == 'r') && (!far || far->color == 'b') &&
               root->parent->rightptr == root) {
      left_rotate(brat);
      delete_node_with_black_one(root);
    } else if ((!near || near->color == 'b') && (far && far->color == 'r') &&
               root->parent->leftptr == root) {
      char tmp = root->parent->rightptr->color;
      char tmp2 = root->parent->color;
      left_rotate(root->parent);
      root->parent->color = tmp;
      root->parent->parent->color = tmp2;
    } else if ((!near || near->color == 'b') && (far && far->color == 'r') &&
               root->parent->rightptr == root) {
      char tmp = root->parent->leftptr->color;
      char tmp2 = root->parent->color;
      right_rotate(root->parent);
      root->parent->color = tmp;
      root->parent->parent->color = tmp2;
    }
  }
}
template <typename key, typename value>
typename BinaryTree<key, value>::node *BinaryTree<key, value>::get_max(
    node *root) const {
  node *res;
  if (!root->rightptr) {
    res = root;
  } else {
    res = get_max(root->rightptr);
  }
  return res;
}
template <typename key, typename value>
void BinaryTree<key, value>::delete_node_with_one_child(node *root) {
  node *tmp;
  if (root->leftptr) {
    tmp = root->leftptr;
  } else {
    tmp = root->rightptr;
  }
  root->key_node = tmp->key_node;
  root->value_node = tmp->value_node;
}
template <typename key, typename value>
typename BinaryTree<key, value>::node *BinaryTree<key, value>::find_node(
    key var, node *root) {
  node *res;
  if (root == nullptr) {
    return nullptr;
  }
  if (var < root->key_node) {
    res = find_node(var, root->leftptr);
  }
  if (var > root->key_node) {
    res = find_node(var, root->rightptr);
  }
  if (var == root->key_node) {
    res = root;
  }
  return res;
}
template <typename key, typename value>
void BinaryTree<key, value>::clear_tree(node *root) {
  if (!root) {
    return;
  }
  clear_tree(root->leftptr);
  clear_tree(root->rightptr);
  delete root;
}
template <typename key, typename value>
typename BinaryTree<key, value>::iterator BinaryTree<key, value>::end() const {
  if (!this->root) {
    return nullptr;
  }
  return this->get_max(this->root);
}
template <typename key, typename value>
typename BinaryTree<key, value>::iterator BinaryTree<key, value>::begin()
    const {
  return this->start_of_tree(this->root);
}
template <typename key, typename value>
typename BinaryTree<key, value>::const_iterator BinaryTree<key, value>::cbegin()
    const {
  const_iterator res;
  res.set_iterator(this->start_of_tree(this->root));
  return res;
}
template <typename key, typename value>
typename BinaryTree<key, value>::const_iterator BinaryTree<key, value>::cend()
    const {
  if (!this->root) {
    return nullptr;
  }
  return const_iterator(this->get_max(this->root));
}
template <typename key, typename value>
typename BinaryTree<key, value>::node *BinaryTree<key, value>::copy_binary_tree(
    const BinaryTree &other) {
  this->root = nullptr;
  for (auto it = other.begin(); it != other.end(); it++) {
    this->insert(it.get_it()->key_node, it.get_it()->value_node, this->root,
                 'r');
  }
  return this->root;
}
template <typename key, typename value>
void BinaryTree<key, value>::clear_obj() {
  clear_tree(this->root);
  this->root = nullptr;
}
