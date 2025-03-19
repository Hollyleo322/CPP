#ifndef S21_CONTAINERS_21_QUEUE_TPP
#define S21_CONTAINERS_21_QUEUE_TPP
// #include "s21_queue.h"

namespace s21 {
// ******************* Constructor methods ******************
// default constructor, creates empty queue
template <typename T>
queue<T>::queue() : front_(nullptr), back_(nullptr), size_(0){};

// initializer list constructor, creates queue initialized using
// std::initializer_list
template <typename T>
queue<T>::queue(std::initializer_list<value_type> const &items)
    : front_(nullptr), back_(nullptr), size_(0) {
  for (const auto &item : items) {
    push(item);
  }
}
// copy constructor
template <typename T>
queue<T>::queue(const queue &q) : front_(nullptr), back_(nullptr), size_(0) {
  QueueNode *current = q.front_;
  while (current != nullptr) {
    push(current->data);
    current = current->next;
  }
}

// move constructor
template <typename T>
queue<T>::queue(queue &&q) : front_(q.front_), back_(q.back_), size_(q.size_) {
  q.front_ = nullptr;
  q.back_ = nullptr;
  q.size_ = 0;
}

// destructor
template <typename T>
queue<T>::~queue() {
  while (!empty()) pop();
}

// assignment operator overload for moving object
template <typename T>
queue<T> &queue<T>::operator=(queue &&q) {
  while (!empty()) pop();

  front_ = q.front_;
  back_ = q.back_;
  size_ = q.size_;

  q.front_ = nullptr;
  q.back_ = nullptr;
  q.size_ = 0;

  return *this;
}

// ****************** Queue access methods ******************

// access the first element
template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  if (empty()) throw std::out_of_range("Queue is empty");
  return front_->data;
}

// access the last element
template <typename T>
typename queue<T>::const_reference queue<T>::back() {
  if (empty()) throw std::out_of_range("Queue is empty");
  return back_->data;
}

// checks whether the container is empty
template <typename T>
bool queue<T>::empty() {
  return (front_ == nullptr && back_ == nullptr && size_ == 0);
}

// returns the number of elements
template <typename T>
typename queue<T>::size_type queue<T>::size() {
  return size_;
}

// *********************** Modifiers ************************
// inserts element at the end
template <typename T>
void queue<T>::push(const_reference value) {
  QueueNode *newQueueNode = new QueueNode(value);
  if (empty()) {
    front_ = newQueueNode;
  } else {
    back_->next = newQueueNode;
  }
  back_ = newQueueNode;
  ++size_;
}

// removes the first element
template <typename T>
void queue<T>::pop() {
  if (empty()) throw std::out_of_range("Queue is empty");
  QueueNode *tmp = front_;
  front_ = front_->next;
  delete tmp;
  --size_;
  if (front_ == nullptr) {
    back_ = nullptr;
  }
}

// swaps the contents
template <typename T>
void queue<T>::swap(queue &other) {
  std::swap(front_, other.front_);
  std::swap(back_, other.back_);
  std::swap(size_, other.size_);
}

// insert_many
template <typename T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  for (const auto &arg : {args...}) {
    push(arg);
  }
}

};  // namespace s21

#endif  // S21_CONTAINERS_21_QUEUE_TPP
