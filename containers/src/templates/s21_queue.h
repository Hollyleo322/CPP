#ifndef S21_CONTAINERS_S21_QUEUE_H
#define S21_CONTAINERS_S21_QUEUE_H

#include <iostream>

namespace s21 {
template <typename T>
class queue {
 public:
  // ***************** Member type definition *****************

  using value_type = T;   // the template parameter T;
  using reference = T &;  // T & defines the type of the reference to an element
  using const_reference =
      const T &;  // const T & defines the type of the constant reference
  using size_type = size_t;  // size_t defines the type of the container size
                             // (standard type is size_t)

  // ************************* Methods ************************

  // ******************* Constructor methods ******************
  queue();  // default constructor, creates empty queue
  queue(std::initializer_list<value_type> const
            &items);  // initializer list constructor, creates queue initialized
                      // using std::initializer_list
  queue(const queue &q);  // copy constructor
  queue(queue &&q);       // move constructor
  ~queue();               // destructor
  queue &operator=(
      queue &&q);  // assignment operator overload for moving object

  // ****************** Queue access methods ******************

  const_reference front();  // access the first element
  const_reference back();   // access the last element
  bool empty();             // checks whether the container is empty
  size_type size();         // returns the number of elements

  // *********************** Modifiers ************************
  void push(const_reference value);  // inserts element at the end
  void pop();                        // removes the first element
  void swap(queue &other);           // swaps the contents
  template <typename... Args>        // insert_many
  void insert_many_back(Args &&...args);

  // ************************* Fields *************************
 private:
  // ***************** Queue node declaration *****************
  struct QueueNode {
    value_type data;
    QueueNode *next;
    QueueNode(const_reference value) : data(value), next(nullptr) {}
  };

  QueueNode *front_;
  QueueNode *back_;
  size_type size_;
};
};  // namespace s21

#include "s21_queue.tpp"

#endif  // S21_CONTAINERS_S21_QUEUE_H
