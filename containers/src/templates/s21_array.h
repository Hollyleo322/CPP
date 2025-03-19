#ifndef S21_CONTAINERSPLUS_S21_ARRAY_H
#define S21_CONTAINERSPLUS_S21_ARRAY_H
#include <initializer_list>
#include <iostream>
#include <string>

namespace s21 {
template <class T, size_t N>
class array {
 public:
  // ***************** Member type definition *****************

  // defines the type of an element (T is template parameter)
  using value_type = T;
  // defines the type of the reference to an element
  using reference = T &;
  // defines the type of the constant reference
  using const_reference = const T &;
  // defines the type for iterating through the container
  using iterator = T *;
  // defines the constant type for iterating through the container
  using const_iterator = const T *;
  // defines the type of the container size (standard type is size_t)
  using size_type = size_t;

  // ************************* Methods ************************

  // ******************* Constructor methods ******************
  // default constructor, creates empty array
  array();
  // initializer list constructor. Uses std::initializer_list
  array(std::initializer_list<value_type> const &items);
  // copy constructor
  array(array &a);
  // move constructor
  array(array &&a);
  // destructor
  ~array();
  // assignment operator overload for moving object
  array<T, N> &operator=(array<T, N> &&a);

  // ****************** Array access methods ******************
  reference at(size_type pos);  // access specified element with bounds checking
  reference operator[](size_type pos);  // access specified element
  const_reference front();              // access the first element
  const_reference back();               // access the last element
  iterator data();                      // direct access to the underlying array
  bool empty();                         // checks whether the container is empty
  size_type size();                     // returns the number of elements
  size_type max_size();  // returns the maximum possible number of elements

  // *********************** Modifiers ************************
  void swap(array<T, N> &other);     // swaps the contents
  void fill(const_reference value);  // assigns the given value value to all
                                     // elements in the container.

  // ************************ Iterator ************************
  iterator begin();  // returns an iterator to the beginning
  iterator end();    // returns an iterator to the end

  // ********************* Private fields *********************
 private:
  size_type cap_;
  iterator arr_ptr_;
  size_type size_;
};
};  // namespace s21

#include "s21_array.tpp"
#endif  // S21_CONTAINERSPLUS_S21_ARRAY_H
