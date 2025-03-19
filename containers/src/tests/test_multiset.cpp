#include <gtest/gtest.h>

#include "../templates/s21_containersplus.h"

TEST(constructor, def) {
  std::multiset<int> first_set;
  s21::multiset<int> second_set;
  ASSERT_EQ(first_set.empty(), second_set.empty());
}
TEST(constructor, init_list) {
  std::multiset<int> first_set = {1, 2, 322, 1, 2};
  s21::multiset<int> second_set = {1, 2, 322, 1, 2};
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  ASSERT_EQ(first_set.size(), second_set.size());
  for (; it != first_set.end(); ++it, ++it2) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(constructor, copy) {
  std::multiset<int> first_cpy = {322, 322, 322};
  s21::multiset<int> second_cpy = {322, 322, 322};
  std::multiset<int> first_set(first_cpy);
  s21::multiset<int> second_set(second_cpy);
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  ASSERT_EQ(first_set.size(), second_set.size());
  for (; it != first_set.end(); ++it, ++it2) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(construtctor, move) {
  std::multiset<int> first_cpy = {322, 322, 322};
  s21::multiset<int> second_cpy = {322, 322, 322};
  std::multiset<int> first_set = std::move(first_cpy);
  s21::multiset<int> second_set = std::move(second_cpy);
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  ASSERT_EQ(first_set.size(), second_set.size());
  for (; it != first_set.end(); ++it, ++it2) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(iterator, begin) {
  std::multiset<const char *> first_set = {"322",  "192",   "123",
                                           "1232", "hello", "hello"};
  s21::multiset<const char *> second_set = {"322",  "192",   "123",
                                            "1232", "hello", "hello"};
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  for (; it2 != second_set.end(); ++it, ++it2) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(empty, true_check) {
  std::multiset<char> first_set;
  s21::multiset<char> second_set;
  ASSERT_EQ(first_set.empty(), second_set.empty());
}
TEST(empty, false_check) {
  std::multiset<int> first_set = {2, 3, 5};
  s21::multiset<int> second_set = {3, 322, 322};
  ASSERT_EQ(first_set.empty(), second_set.empty());
}
TEST(size, empty) {
  std::multiset<char> first_set;
  s21::multiset<char> second_set;
  ASSERT_EQ(first_set.size(), second_set.size());
}
TEST(size, not_empty) {
  std::multiset<int> first_set = {32, 124, 3211, 32};
  s21::multiset<int> second_set = {322, 125, 1233, 322};
  ASSERT_EQ(first_set.size(), second_set.size());
}
TEST(clear, clear) {
  std::multiset<int> first_set = {32, 124, 3211};
  s21::multiset<int> second_set = {322, 125, 1233};
  first_set.clear();
  second_set.clear();
  ASSERT_EQ(first_set.size(), second_set.size());
  ASSERT_EQ(first_set.empty(), second_set.empty());
}
TEST(insert, true_test) {
  std::multiset<int> first_set = {32, 124, 3211};
  s21::multiset<int> second_set = {322, 125, 1233};
  auto it = first_set.insert(128);
  auto it2 = second_set.insert(128);
  ASSERT_EQ(first_set.size(), second_set.size());
  ASSERT_EQ(*it, *it2);
}
TEST(erase, single) {
  std::multiset<int> first_set = {32, 124, 3211, 32, 124};
  s21::multiset<int> second_set = {32, 124, 3211, 32, 124};
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  first_set.erase(it);
  second_set.erase(it2);
  it = first_set.begin();
  it2 = second_set.begin();
  ASSERT_EQ(first_set.size(), second_set.size());
  for (; it != first_set.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(swap, single) {
  std::multiset<const char *> first_set = {"hello, school, 21"};
  s21::multiset<const char *> second_set = {"hello, school, 21"};
  std::multiset<const char *> swap_for_first = {"you, are, welcome"};
  s21::multiset<const char *> swap_for_second = {"you, are, welcome"};
  first_set.swap(swap_for_first);
  second_set.swap(swap_for_second);
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  for (; it != first_set.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
  it = swap_for_first.begin();
  it2 = swap_for_second.begin();
  for (; it != swap_for_first.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(merge, single) {
  std::multiset<int> first_set = {1, 50, 322};
  s21::multiset<int> second_set = {1, 50, 322};
  std::multiset<int> first_merge = {32, 124, 3211, 1, 50};
  s21::multiset<int> second_merge = {32, 124, 3211, 1, 50};
  first_set.merge(first_merge);
  second_set.merge(second_merge);
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  for (; it != first_set.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(count, true_test) {
  std::multiset<int> first_set = {32, 124, 3211, 32, 124};
  s21::multiset<int> second_set = {32, 124, 3211, 32, 124};
  ASSERT_EQ(first_set.count(32), second_set.count(32));
}
TEST(count, false_test) {
  std::multiset<int> first_set = {32, 124, 3211, 32, 124};
  s21::multiset<int> second_set = {32, 124, 3211, 32, 124};
  ASSERT_EQ(first_set.count(322), second_set.count(322));
}
TEST(find, single) {
  std::multiset<int> first_set = {32, 124, 3211, 32, 124};
  s21::multiset<int> second_set = {32, 124, 3211, 32, 124};
  auto it = first_set.find(124);
  auto it2 = second_set.find(124);
  ASSERT_EQ(*it, *it2);
}
TEST(contains, true_test) {
  s21::multiset<int> second_set = {1, 50, 322, 215, 32322, 12314};
  ASSERT_EQ(true, second_set.contains(50));
}
TEST(contains, false_test) {
  s21::multiset<int> second_set = {1, 50, 322, 215, 32322, 12314};
  ASSERT_EQ(false, second_set.contains(323));
}
TEST(equal_range, single) {
  std::multiset<int> first_set = {32, 124, 3211, 32, 124, 32, 32};
  s21::multiset<int> second_set = {32, 124, 3211, 32, 124, 32, 32};
  auto it = first_set.equal_range(32);
  auto it2 = second_set.equal_range(32);
  for (; it.first != it.second; it.first++, it2.first++) {
    ASSERT_EQ(*it.first, *it2.first);
  }
}
TEST(lower_bound, single) {
  std::multiset<int> first_set = {32, 124, 3211, 32, 124, 32, 32};
  s21::multiset<int> second_set = {32, 124, 3211, 32, 124, 32, 32};
  auto it = first_set.lower_bound(32);
  auto it2 = second_set.lower_bound(32);
  ASSERT_EQ(*it, *it2);
}
TEST(upper_bound, single) {
  std::multiset<int> first_set = {32, 124, 3211, 32, 124, 32, 32};
  s21::multiset<int> second_set = {32, 124, 3211, 32, 124, 32, 32};
  auto it = first_set.upper_bound(32);
  auto it2 = second_set.upper_bound(32);
  ASSERT_EQ(*it, *it2);
}
TEST(insert_many, single) {
  s21::multiset<int> my_set = {1, 2, 3};
  s21::vector<int> cmp_vector = {4, 7, 8};
  s21::vector<std::pair<s21::multiset<int>::iterator, bool>> res =
      my_set.insert_many(4, 7, 8);
  auto it = res.begin();
  auto it2 = cmp_vector.begin();
  for (; it != res.end(); it++, it2++) {
    ASSERT_EQ(*it->first, *it2);
    ASSERT_EQ(it->second, true);
  }
}
int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
