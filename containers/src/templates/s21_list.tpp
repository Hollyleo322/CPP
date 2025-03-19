#ifndef S21_CONTAINERS_21_LIST_TPP
#define S21_CONTAINERS_21_LIST_TPP
// #include "./s21_list.h"

namespace s21 {

// ******************* Constructor methods ******************

// default constructor, creates empty list 
template <typename T>
list<T>::list() : front_(nullptr), back_(nullptr), size_(0) {}

// parameterized constructor, creates the list of size n
template <typename T>
list<T>::list(size_type n) : front_(nullptr), back_(nullptr), size_(0) {
  for (size_type i = 0; i < n; ++i) {
    push_back(T());
  }
}

// initializer list constructor, creates list initialized using
// std::initializer_list
template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : front_(nullptr), back_(nullptr), size_(0) {
  for (const auto &item : items) {
    push_back(item);
  }
}

// copy constructor
template <typename T>
list<T>::list(const list &l) : front_(nullptr), back_(nullptr), size_(0) {
  for (auto it = l.cbegin(); it != l.cend(); ++it) {
    push_back(*it);
  }
}

// move constructor
template <typename T>
list<T>::list(list &&l) : front_(l.front_), back_(l.back_), size_(l.size_) {
  l.front_ = nullptr;
  l.back_ = nullptr;
  l.size_ = 0;
}

// destructor
template <typename T>
list<T>::~list() {
  while (front_ != nullptr) {
    ListNode *temp = front_;
    front_ = front_->next_;
    delete temp;
  }
  back_ = nullptr;
  size_ = 0;
}

// assignment operator overload for moving object
template <typename T>
typename list<T>::list &list<T>::operator=(list &&l) {
  if (this != &l) {
    clear();
    front_ = l.front_;
    back_ = l.back_;
    size_ = l.size_;
    l.front_ = nullptr;
    l.back_ = nullptr;
    l.size_ = 0;
  }
  return *this;
}

// ***************** ListNode access methods ****************

// Возвращает ссылку на первый элемент списка.
template <typename T>
typename list<T>::const_reference list<T>::front() {
  if (empty()) throw std::out_of_range("List is empty");
  return front_->data_;
}

// Возвращает ссылку на последний элемент списка.
template <typename T>
typename list<T>::const_reference list<T>::back() {
  if (empty()) throw std::out_of_range("List is empty");
  return back_->data_;
}

// Возвращает итератор, указывающий на первый элемент списка.
template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator(front_);
}

// Возвращает константный итератор, указывающий на первый элемент списка.
template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const {
  return const_iterator(front_);
}

// Возвращает итератор, указывающий на элемент, следующий за последним элементом
// списка.
template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator(back_->next_);
}

// Возвращает константный итератор, указывающий на элемент, следующий за
// последним элементом списка.
template <typename T>
typename list<T>::const_iterator list<T>::cend() const {
  return const_iterator(back_->next_);
}

// Проверяет, пуст ли список.
template <typename T>
bool list<T>::empty() {
  return size_ == 0;
}

// Возвращает количество элементов в списке.
template <typename T>
typename list<T>::size_type list<T>::size() {
  return size_;
}

// Возвращает максимальное количество элементов, которое может содержать список.
template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

// *********************** Modifiers ************************

// Удаляет все элементы из списка.
template <typename T>
void list<T>::clear() {
  while (front_ != nullptr) {
    ListNode *temp = front_;
    front_ = front_->next_;
    delete temp;
  }
  back_ = nullptr;
  size_ = 0;
}

// Удаляет элемент из заданной позиции.
template <typename T>
void list<T>::erase(iterator pos) {
  ListNode *node = pos.getNode();
  if (node == nullptr) {
    throw std::out_of_range("Iterator is out of range");
  }
  if (node == front_) {
    front_ = front_->next_;
    if (front_ != nullptr) {
      front_->prev_ = nullptr;
    }
  } else if (node == back_) {
    back_ = back_->prev_;
    back_->next_ = nullptr;
  } else {
    node->prev_->next_ = node->next_;
    node->next_->prev_ = node->prev_;
  }
  delete node;
  --size_;
}

// Добавляет элемент в конец списка
template <typename T>
void list<T>::push_back(const_reference value) {
  ListNode *node = new ListNode(value);
  if (empty()) {
    front_ = node;
    back_ = node;
  } else {
    node->prev_ = back_;
    back_->next_ = node;
    back_ = node;
  }
  ++size_;
}

// Удаляет последний элемент списка.
template <typename T>
void list<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  if (front_ == back_) {
    clear();
  } else {
    ListNode *temp = back_;
    back_ = back_->prev_;
    back_->next_ = nullptr;
    delete temp;
    --size_;
  }
}

// Добавляет элемент в начало списка.
template <typename T>
void list<T>::push_front(const_reference value) {
  ListNode *node = new ListNode(value);
  if (empty()) {
    front_ = node;
    back_ = node;
  } else {
    node->next_ = front_;
    front_->prev_ = node;
    front_ = node;
  }
  ++size_;
}

// Удаляет первый элемент списка.
template <typename T>
void list<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }
  if (front_ == back_) {
    clear();
  } else {
    erase(begin());
  }
}

// Обменивает содержимое текущего списка с другим списком.
template <typename T>
void list<T>::swap(list &other) {
  std::swap(front_, other.front_);
  std::swap(back_, other.back_);
  std::swap(size_, other.size_);
}

// Объединяет с другим списком.
template <typename T>
void list<T>::merge(list &other) {
  if (this != &other) {
    sort();
    other.sort();
    auto it = begin();
    auto otherIt = other.begin();
    while (otherIt != other.end()) {
      if (it == end() || *otherIt < *it) {
        insert(it, *otherIt);
        ++otherIt;
      } else {
        ++it;
      }
    }
    other.clear();
  }
}

// Перемещает элементы из одного списка в другой.
template <typename T>
void list<T>::splice(iterator pos, list &other) {
  if (this != &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      insert(pos, *it);
    }
    other.clear();
  }
}

// Обращает порядок элементов в списке.
template <typename T>
void list<T>::reverse() {
  if (size_ > 1) {
    ListNode *left = front_;
    ListNode *right = back_;
    while (left != right && left->prev_ != right) {
      std::swap(left->data_, right->data_);
      left = left->next_;
      right = right->prev_;
    }
  }
}

// Удаляет дубликаты из списка.
template <typename T>
void list<T>::unique() {
  if (size_ > 1) {
    ListNode *current = front_->next_;
    ListNode *prev = front_;
    while (current != nullptr) {
      if (current->data_ == prev->data_) {
        ListNode *nextNode = current->next_;
        erase(current);
        current = nextNode;
      } else {
        prev = current;
        current = current->next_;
      }
    }
  }
}

// Сортирует элементы списка.
template <typename T>
void list<T>::sort() {
  if (size_ > 1) {
    bool swapped;
    ListNode *current;
    ListNode *lastSorted = nullptr;
    do {
      swapped = false;
      current = front_;
      while (current->next_ != lastSorted) {
        if (current->data_ > current->next_->data_) {
          std::swap(current->data_, current->next_->data_);
          swapped = true;
        }
        current = current->next_;
      }
      lastSorted = current;
    } while (swapped);
  }
}

// Вставляет значение в заданную позицию.
template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  ListNode *node = new ListNode(value);
  if (pos == begin()) {
    node->next_ = front_;
    if (front_ != nullptr) {
      front_->prev_ = node;
    }
    front_ = node;
    if (back_ == nullptr) {
      back_ = node;
    }
  } else if (pos == end()) {
    back_->next_ = node;
    node->prev_ = back_;
    back_ = node;
  } else {
    ListNode *current = pos.getNode();
    node->next_ = current;
    node->prev_ = current->prev_;
    current->prev_->next_ = node;
    current->prev_ = node;
  }
  ++size_;
  return iterator(node);
}

// Метод вставки множества значений в список.
template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args &&...args) {
  iterator it(const_cast<ListNode *>(pos.cgetNode()));
  for (const auto &arg : {args...}) {
    insert(it, arg);
  }
  return it;
}

// Метод добавляет множество значений в конец списка.
template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args &&...args) {
  insert_many(cend(), args...);
}

// Метод добавляет множество значений в начало списка.
template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args &&...args) {
  insert_many(cbegin(), args...);
}

};  // namespace s21

#endif
// S21_CONTAINERS_LIST_TPP
