#ifndef S21_CONTAINERS_S21_LIST_H_
#define S21_CONTAINERS_S21_LIST_H_
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 public:
  // ***************** Member type definition *****************
  class ListIterator;  // Итератор для класса list. Класс позволяет обходить
                       // двусвязный список,
  class ListConstIterator;  // Константный итератор для класса list.
                            // Ограничивает доступ к элементам списка только для
                            // чтения
  using value_type =
      T;  // T defines the type of an element (T is template parameter)
  using reference = T &;  // T & defines the type of the reference to an element
  using const_reference =
      const T &;  // const T & defines the type of the constant reference
  using iterator = ListIterator;  //  internal class ListIterator<T> defines the
                                  //  type for iterating through the container
  using const_iterator =
      ListConstIterator;  // internal class ListConstIterator<T> defines the
                          // constant type for iterating through the container
  using size_type = size_t;  // size_t defines the type of the container size
                             // (standard type is size_t)

  // ************************* Methods ************************

  // ******************* Constructor methods ******************
  list();             // default constructor, creates empty list 
  list(size_type n);  // parameterized constructor, creates the list of size n
  list(std::initializer_list<value_type> const
           &items);  // initializer list constructor, creates list initialized
                     // using std::initializer_list
  list(const list &l);        // copy constructor
  list(list &&l);             // move constructor
  ~list();                    // destructor
  list &operator=(list &&l);  // assignment operator overload for moving object

  // ***************** ListNode access methods ****************
  const_reference front();  // Возвращает ссылку на первый элемент списка.
  const_reference back();  // Возвращает ссылку на последний элемент списка.
  size_type size();  // Возвращает количество элементов в списке.
  size_type max_size();  // Возвращает максимальное количество элементов,
                         // которое может содержать список.
  iterator
  begin();  // Возвращает итератор, указывающий на первый элемент списка.
  const_iterator cbegin() const;  // Возвращает константный итератор,
                                  // указывающий на первый элемент списка.
  iterator end();  // Возвращает итератор, указывающий на элемент, следующий за
                   // последним элементом списка.
  const_iterator cend()
      const;  // Возвращает константный итератор, указывающий на элемент,
              // следующий за последним элементом списка.
  bool empty();  // Проверяет, пуст ли список.

  // *********************** Modifiers ************************
  void clear();  // Удаляет все элементы из списка.
  void erase(iterator pos);  // Удаляет элемент из заданной позиции.
  void push_back(const_reference value);  // Добавляет элемент в конец списка.
  void pop_back();  // Удаляет последний элемент списка.
  void push_front(const_reference value);  // Добавляет элемент в начало списка.
  void pop_front();  // Удаляет первый элемент списка.
  void swap(
      list &other);  // Обменивает содержимое текущего списка с другим списком.
  void merge(list &other);  // Объединяет с другим списком.
  void splice(iterator pos,
              list &other);  // Перемещает элементы из одного списка в другой.
  void reverse();  // Обращает порядок элементов в списке.
  void unique();  // Удаляет дубликаты из списка.
  void sort();    // Сортирует элементы списка.
  iterator insert(
      iterator pos,
      const_reference value);  // Вставляет значение в заданную позицию.

  // Методы для вставки множества элементов
  // Метод вставки множества значений в список,
  // начиная с заданной позиции (pos). Значения передаются как параметры.
  // возвращает итератор на первый вставленный элемент.
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  // Метод добавляет множество значений в конец списка.
  template <typename... Args>
  void insert_many_back(Args &&...args);

  // Метод добавляет множество значений в начало списка.
  template <typename... Args>
  void insert_many_front(Args &&...args);

  // ************************* Fields *************************
 private:
  // ***************** List node declaration ******************
  struct ListNode {
    value_type data_;
    ListNode *prev_;
    ListNode *next_;
    ListNode(const_reference value)
        : data_(value), prev_(nullptr), next_(nullptr) {}
  };
  ListNode *front_;
  ListNode *back_;
  size_type size_;
};
// ********************* List Iterator **********************

template <typename T>
class list<T>::ListIterator {
 public:
  // member type
  using value_type = T;  // Определяет тип значения, хранимого в контейнере
  using reference = T &;  // Определяет тип ссылки на элемент
  using pointer = T *;  // Определяет тип указателя на элемент
  using difference_type =
      std::ptrdiff_t;  // Определяет тип, который используется для расстояния
                       // между итераторами,
  using iterator_category =
      std::forward_iterator_tag;  // используется для однократного прохода по
                                  // контейнеру

  ListIterator(typename list<T>::ListNode *node)
      : node_(node) {
  }  // Конструктор принимает указатель на узел списка и инициализирует его

  reference operator*() const {
    return node_->data_;
  }  //  Оператор разыменования *. Возвращает ссылку на данные в узле, на
     //  который указывает итератор

  // Префиксный оператор ++, который перемещает итератор на следующий узел и
  // возвращает его
  ListIterator &operator++() {
    node_ = node_->next_;
    return *this;
  }

  // Постфиксный оператор ++. Сохраняет текущее состояние итератора, затем
  // увеличивает его на 1 и возвращает копию предыдущего состояния
  ListIterator operator++(int) {
    ListIterator temp = *this;
    ++(*this);
    return temp;
  }

  // возвращает true, если итераторы равны (т.е. указывают на один и тот же
  // узел),
  bool operator==(const ListIterator &other) const {
    return node_ == other.node_;
  }

  // возвращает true, если они не равны.
  bool operator!=(const ListIterator &other) const { return !(*this == other); }

  // метод возвращает указатель на узел, на который указывает итератор
  typename list<T>::ListNode *getNode() { return node_; }

 private:
  typename list<T>::ListNode *node_;
};

// ***************** Constant List Iterator *****************

template <typename T>
class list<T>::ListConstIterator {
 public:
  using value_type =
      T;  // Определяет тип значения, который хранится в контейнере
  using reference =
      const T &;  // Определяет тип ссылки на данные — в этом случае это
                  // константная ссылка, что позволяет только читать данные
  using pointer = const T
      *;  // Указатель на данные, при этом указатель также является константным
  using difference_type =
      std::ptrdiff_t;  // Тип, представляющий разность между итераторами
  using iterator_category =
      std::forward_iterator_tag;  // Определяет категорию итератора. Это
                                  // итератор прямого доступа

  // Конструктор принимает указатель на узел и инициализирует его без
  // возможности менять данные через этот итератор
  ListConstIterator(const typename list<T>::ListNode *node) : node_(node) {}

  reference operator*() const {
    return node_->data_;
  }  // Оператор разыменования *, который возвращает константную ссылку на
     // данные в узле

  // Префиксный оператор ++, который перемещает итератор на следующий узел и
  // возвращает ссылку на текущий итератор
  ListConstIterator &operator++() {
    node_ = node_->next_;
    return *this;
  }
  // Постфиксный оператор ++. Аналогичен реализации из ListIterator
  ListConstIterator operator++(int) {
    ListConstIterator temp = *this;
    ++(*this);
    return temp;
  }

  // Операторы сравниения итераторов

  bool operator==(const ListConstIterator &other) const {
    return node_ == other.node_;
  }

  bool operator!=(const ListConstIterator &other) const {
    return !(*this == other);
  }

  // Метод возвращает указатель на константный узел.
  const typename list<T>::ListNode *cgetNode() { return node_; }

 private:
  const typename list<T>::ListNode *node_;
};

};  // namespace s21
#include "s21_list.tpp"
#endif  // S21_CONTAINERS_S21_LIST_H_
