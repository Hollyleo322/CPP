#ifndef S21_CONTAINERSPLUS_S21_ARRAY_TPP
#define S21_CONTAINERSPLUS_S21_ARRAY_TPP

namespace s21 {

// ******************* Constructor methods ******************

// default constructor, creates empty array
template <class T, size_t N>
s21::array<T, N>::array() {
  size_ = N;
  arr_ptr_ = new T[N + 1];
  cap_ = N;
}

// initializer list constructor. Uses std::initializer_list
template <class T, size_t N>
s21::array<T, N>::array(std::initializer_list<T> const& items) {
  arr_ptr_ = nullptr;

  if (items.size() > N) {
    throw std::out_of_range("Invalid number of elements");
  } else {
    cap_ = N;
    size_ = items.size();
    iterator new_arr = new T[N + 1];

    int count = 0;
    for (auto it = items.begin(); it != items.end(); ++it) {
      new_arr[count] = *it;
      ++count;
    }
    arr_ptr_ = new_arr;
  }
}

// copy constructor
template <class T, size_t N>
s21::array<T, N>::array(s21::array<T, N>& copied_array) {
  cap_ = copied_array.cap_;
  size_ = copied_array.size_;

  T* new_arr = new T[cap_ + 1];
  arr_ptr_ = new_arr;

  T* it = begin();
  for (T* iter = copied_array.begin(); iter != copied_array.end(); ++iter) {
    *it = *iter;
    it++;
  }
}

// move constructor
template <class T, size_t N>
s21::array<T, N>::array(s21::array<T, N>&& mooved_array) {
  cap_ = 0;
  arr_ptr_ = nullptr;
  size_ = 0;
  swap(mooved_array);
}

// destructor
template <class T, size_t N>
s21::array<T, N>::~array() {
  if (arr_ptr_ != nullptr) {
    delete[] arr_ptr_;
  }
  size_ = 0;
  cap_ = 0;
  arr_ptr_ = nullptr;
}

// assignment operator overload for moving object
template <class T, size_t N>
s21::array<T, N>& s21::array<T, N>::operator=(array<T, N>&& mooved_array) {
  swap(mooved_array);
  mooved_array.~array();
  return *this;
}

// assignment operator overload for moving object
template <class T, size_t N>
T& s21::array<T, N>::operator[](size_t pos) {
  if (pos < cap_) {
    return *(data() + pos);
  } else
    throw std::out_of_range("Wrong index");
}

// ***************** ListNode access methods ****************
template <class T, size_t N>
T& s21::array<T, N>::at(size_t pos) {
  if (pos < cap_) {
    return *(data() + pos);
  } else
    throw std::out_of_range("Wrong index");
}

template <class T, size_t N>
void s21::array<T, N>::swap(array<T, N>& mooved_array) {
  std::swap(arr_ptr_, mooved_array.arr_ptr_);
  std::swap(cap_, mooved_array.cap_);
  std::swap(size_, mooved_array.size_);
}

template <class T, size_t N>
void s21::array<T, N>::fill(const T& value) {
  for (T* it = begin(); it != end(); ++it) {
    *it = value;
  }
}

template <class T, size_t N>
const T& s21::array<T, N>::front() {
  return *arr_ptr_;
}

template <class T, size_t N>
const T& s21::array<T, N>::back() {
  return *(end() - 1);
}

template <class T, size_t N>
T* s21::array<T, N>::data() {
  return this->arr_ptr_;
}

template <class T, size_t N>
T* s21::array<T, N>::begin() {
  return this->arr_ptr_;
}

template <class T, size_t N>
T* s21::array<T, N>::end() {
  return this->arr_ptr_ + this->size_;
}

template <class T, size_t N>
bool s21::array<T, N>::empty() {
  return !(this->size_ > 0);
}

template <class T, size_t N>
size_t s21::array<T, N>::size() {
  return this->size_;
}

template <class T, size_t N>
size_t s21::array<T, N>::max_size() {
  return this->cap_;
}

};  // namespace s21

#endif  // S21_CONTAINERSPLUS_S21_ARRAY_H
