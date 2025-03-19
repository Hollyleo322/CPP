#include <gtest/gtest.h>

#include <exception>

#include "../templates/s21_containers.h"
class test_vector {
 private:
  int size = 0;

 public:
  test_vector() {}
  test_vector(const test_vector &val) {
    if (val.size != 0) {
      throw std::exception();
    }
  }
  void set_size() { this->size = 100; }
};

TEST(constructor, def) {
  std::vector<int> first;
  s21::vector<int> second;
  ASSERT_EQ(first.size(), second.size());
  ASSERT_EQ(first.capacity(), second.capacity());
  ASSERT_EQ(first.empty(), second.empty());
}
TEST(constructor, size_par) {
  std::vector<int> first(10);
  s21::vector<int> second(10);
  ASSERT_EQ(first.size(), second.size());
  ASSERT_EQ(first.capacity(), second.capacity());
  ASSERT_EQ(first.empty(), second.empty());
}
TEST(constructor, init_list) {
  std::vector<int> first = {123, 150, 175};
  s21::vector<int> second = {123, 150, 175};
  auto it = first.begin();
  auto it2 = second.begin();
  for (; it != first.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
  ASSERT_EQ(first.empty(), second.empty());
}
TEST(constructor, init_list_exc) {
  test_vector b;
  test_vector c;
  s21::vector<test_vector> a = {b, c};
  a[0].set_size();
  s21::vector<test_vector> d;
  ASSERT_ANY_THROW(d = a);
}
TEST(erase, exception) {
  test_vector b;
  test_vector c;
  s21::vector<test_vector> a = {b, c};
  a[1].set_size();
  ASSERT_ANY_THROW(a.erase(a.data()));
}
TEST(constructor, cpy_exc) {
  test_vector b;
  test_vector c;
  s21::vector<test_vector> a = {b, c};
  a[0].set_size();
  ASSERT_ANY_THROW(s21::vector<test_vector> d = a);
}
TEST(shrink_to, exception) {
  test_vector b;
  test_vector c;
  s21::vector<test_vector> a = {b, c};
  a.reserve(100);
  a[0].set_size();
  ASSERT_ANY_THROW(a.shrink_to_fit());
}
TEST(insert, exception) {
  test_vector b;
  test_vector c;
  s21::vector<test_vector> a = {b, c};
  a.reserve(100);
  a[0].set_size();
  ASSERT_ANY_THROW(a.insert(a.begin(), a[0]));
}
TEST(insert, exception3) {
  test_vector b;
  test_vector c;
  s21::vector<test_vector> a = {b, c};
  a.reserve(100);
  a[1].set_size();
  ASSERT_ANY_THROW(a.insert(a.data() + 2, a[1]));
}
TEST(insert, exception4) {
  test_vector b;
  test_vector c;
  s21::vector<test_vector> a = {b, c};
  a.reserve(100);
  a[1].set_size();
  ASSERT_ANY_THROW(a.insert(a.data(), b));
}
TEST(insert, exception2) {
  s21::vector<int> a = {1, 2, 3};
  ASSERT_ANY_THROW(a.insert((a.data() + 5), 56));
}
TEST(erase, exception2) {
  s21::vector<int> a = {1, 2, 3};
  ASSERT_ANY_THROW(a.erase(a.data() + 5));
}
TEST(erase, exception3) {
  test_vector b;
  test_vector c;
  s21::vector<test_vector> a = {b, c, c, b};
  a.reserve(100);
  a[3].set_size();
  ASSERT_ANY_THROW(a.erase(a.data() + 1));
}
TEST(reserve, exception) {
  test_vector b;
  test_vector c;
  s21::vector<test_vector> a = {b, c};
  a[0].set_size();
  ASSERT_ANY_THROW(a.reserve(100));
}
TEST(constructor, cpy) {
  std::vector<int> first = {123, 150, 175};
  s21::vector<int> second = {123, 150, 175};
  std::vector<int> first_cpy(first);
  s21::vector<int> second_cpy(second);
  ASSERT_EQ(first_cpy.size(), second_cpy.size());
  ASSERT_EQ(first_cpy.capacity(), second_cpy.capacity());
  auto it = first_cpy.begin();
  auto it2 = second_cpy.begin();
  for (; it != first_cpy.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(operator_eq, cpy) {
  std::vector<int> first = {123, 150, 175};
  s21::vector<int> second = {123, 150, 175};
  std::vector<int> first_cpy;
  s21::vector<int> second_cpy;
  first_cpy = first;
  second_cpy = second;
  ASSERT_EQ(first_cpy.size(), second_cpy.size());
  ASSERT_EQ(first_cpy.capacity(), second_cpy.capacity());
  auto it = first_cpy.begin();
  auto it2 = second_cpy.begin();
  for (; it != first_cpy.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(operator_eq, cpy2) {
  std::vector<int> first = {123, 150, 175};
  s21::vector<int> second = {123, 150, 175};
  std::vector<int> first_cpy = {1, 2};
  s21::vector<int> second_cpy = {1, 2};
  first_cpy = first;
  second_cpy = second;
  ASSERT_EQ(first_cpy.size(), second_cpy.size());
  ASSERT_EQ(first_cpy.capacity(), second_cpy.capacity());
  auto it = first_cpy.begin();
  auto it2 = second_cpy.begin();
  for (; it != first_cpy.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(constructor, move) {
  std::vector<int> first = {123, 150, 175};
  s21::vector<int> second = {123, 150, 175};
  std::vector<int> first_cpy = std::move(first);
  s21::vector<int> second_cpy = std::move(second);
  ASSERT_EQ(first_cpy.size(), second_cpy.size());
  ASSERT_EQ(first_cpy.capacity(), second_cpy.capacity());
  auto it = first_cpy.begin();
  auto it2 = second_cpy.begin();
  for (; it != first_cpy.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
  ASSERT_EQ(first.size(), second.size());
  ASSERT_EQ(first.capacity(), second.capacity());
}
TEST(constructor, move2) {
  std::vector<int> first = {123, 150, 175};
  s21::vector<int> second = {123, 150, 175};
  std::vector<int> first_cpy = {1, 2, 3};
  s21::vector<int> second_cpy = {1, 2, 3};
  first_cpy = std::move(first);
  second_cpy = std::move(second);
  ASSERT_EQ(first_cpy.size(), second_cpy.size());
  ASSERT_EQ(first_cpy.capacity(), second_cpy.capacity());
  auto it = first_cpy.begin();
  auto it2 = second_cpy.begin();
  for (; it != first_cpy.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
  ASSERT_EQ(first.size(), second.size());
  ASSERT_EQ(first.capacity(), second.capacity());
}
TEST(at, true_test) {
  std::vector<int> first = {123, 150, 175};
  s21::vector<int> second = {123, 150, 175};
  int a = first.at(2);
  int b = second.at(2);
  ASSERT_EQ(a, b);
}
TEST(at, false_test) {
  std::vector<int> first = {123, 150, 175};
  s21::vector<int> second = {123, 150, 175};
  ASSERT_ANY_THROW(first.at(4));
  ASSERT_ANY_THROW(second.at(4));
}
TEST(size, single) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  ASSERT_EQ(first.size(), second.size());
}
TEST(max_size, single) {
  std::vector<int> first;
  std::vector<int> second;
  ASSERT_EQ(first.max_size(), second.max_size());
}
TEST(reserve, single) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  first.reserve(100);
  second.reserve(100);
  ASSERT_EQ(first.size(), second.size());
  ASSERT_EQ(first.capacity(), second.capacity());
}
TEST(shrink_to_fit, single) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  first.reserve(100);
  second.reserve(100);
  first.shrink_to_fit();
  second.shrink_to_fit();
  ASSERT_EQ(first.size(), second.size());
  ASSERT_EQ(first.capacity(), second.capacity());
}
TEST(clear, single) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  first.clear();
  second.clear();
  ASSERT_EQ(first.size(), second.size());
  ASSERT_EQ(first.capacity(), second.capacity());
}
TEST(front, single) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  auto it = first.front();
  auto it2 = second.front();
  ASSERT_EQ(it, it2);
}
TEST(back, single) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  auto it = first.back();
  auto it2 = second.back();
  ASSERT_EQ(it, it2);
}
TEST(data, single) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  auto it = first.data();
  auto it2 = second.data();
  ASSERT_EQ(*it, *it2);
}
TEST(insert, first) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  first.insert(first.begin(), 322);
  second.insert(second.begin(), 322);
  ASSERT_EQ(first.size(), second.size());
  ASSERT_EQ(first.capacity(), second.capacity());
  auto it = first.begin();
  auto it2 = second.begin();
  for (; it != first.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(insert, second) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  auto it = first.end();
  auto it2 = second.end();
  first.insert(it, 322);
  second.insert(it2, 322);
  ASSERT_EQ(first.size(), second.size());
  ASSERT_EQ(first.capacity(), second.capacity());
  it = first.begin();
  it2 = second.begin();
  for (; it != first.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(erase, start) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  first.erase(first.begin());
  second.erase(second.begin());
  ASSERT_EQ(first.size(), second.size());
  ASSERT_EQ(first.capacity(), second.capacity());
  auto it = first.begin();
  auto it2 = second.begin();
  for (; it != first.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(erase, end) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  auto it = first.end();
  auto it2 = second.end();
  it--;
  it2--;
  first.erase(it);
  second.erase(it2);
  ASSERT_EQ(first.size(), second.size());
  ASSERT_EQ(first.capacity(), second.capacity());
  it = first.begin();
  it2 = second.begin();
  for (; it != first.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(push_back, single) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  for (int i = 0; i < 15; i++) {
    first.push_back(i);
    second.push_back(i);
  }
  ASSERT_EQ(first.size(), second.size());
  ASSERT_EQ(first.capacity(), second.capacity());
  auto it = first.begin();
  auto it2 = second.begin();
  for (; it != first.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(pop_back, single) {
  std::vector<int> first;
  s21::vector<int> second;
  for (int i = 0; i < 100; i++) {
    first.push_back(i);
    second.push_back(i);
  }
  for (int i = 0; i < 100; i++) {
    first.pop_back();
    second.pop_back();
    ASSERT_EQ(first.size(), second.size());
    ASSERT_EQ(first.capacity(), second.capacity());
  }
}
TEST(swap, single) {
  std::vector<int> first = {123, 150, 175, 355, 123123, 32131};
  s21::vector<int> second = {123, 150, 175, 355, 123123, 32131};
  std::vector<int> first_swap = {322, 150, 323};
  s21::vector<int> second_swap = {322, 150, 323};
  first.swap(first_swap);
  second.swap(second_swap);
  auto it = first.begin();
  auto it2 = second.begin();
  for (; it != first.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(insert_many, single) {
  s21::vector<int> first = {1, 2, 3};
  s21::vector<int> second = {125, 124, 123, 1, 2, 3};
  auto it = first.begin();
  auto it2 = first.insert_many(it, 123, 124, 125);
  ASSERT_EQ(*it2, *first.begin());
  auto it3 = second.begin();
  for (auto it = first.begin(); it != first.end(); it++, it3++) {
    ASSERT_EQ(*it, *it3);
  }
}
TEST(inser_many_back, single) {
  s21::vector<int> first = {1, 2, 3};
  s21::vector<int> cmp_vector = {1, 2, 3, 322, 322, 322};
  first.insert_many_back(322, 322, 322);
  auto it2 = cmp_vector.begin();
  for (auto it = first.begin(); it != first.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
