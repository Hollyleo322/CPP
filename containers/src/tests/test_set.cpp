#include <gtest/gtest.h>

#include "../templates/s21_containers.h"

TEST(constructor, def) {
  std::set<int> first_set;
  s21::set<int> second_set;
  ASSERT_EQ(first_set.empty(), second_set.empty());
}
TEST(constructor, init_list) {
  std::set<int> first_set = {1, 2, 322};
  s21::set<int> second_set = {1, 2, 322};
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  ASSERT_EQ(first_set.size(), second_set.size());
  for (; it != first_set.end(); ++it, ++it2) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(constructor, copy) {
  std::set<int> first_cpy = {322, 322, 322};
  s21::set<int> second_cpy = {322, 322, 322};
  std::set<int> first_set(first_cpy);
  s21::set<int> second_set(second_cpy);
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  ASSERT_EQ(first_set.size(), second_set.size());
  for (; it != first_set.end(); ++it, ++it2) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(constructor, move) {
  std::set<int> first_cpy = {322, 322, 322};
  s21::set<int> second_cpy = {322, 322, 322};
  std::set<int> first_set = std::move(first_cpy);
  s21::set<int> second_set = std::move(second_cpy);
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  ASSERT_EQ(first_set.size(), second_set.size());
  for (; it != first_set.end(); ++it, ++it2) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(constructor, move_chr) {
  std::set<const char *> first_cpy = {"322", "192", "123"};
  s21::set<const char *> second_cpy = {"322", "192", "123"};
  std::set<const char *> first_set = std::move(first_cpy);
  s21::set<const char *> second_set = std::move(second_cpy);
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  ASSERT_EQ(first_set.size(), second_set.size());
  for (; it != first_set.end(); ++it, ++it2) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(iterator, iterators) {
  std::set<const char *> first_set = {"322", "192", "123", "1232", "hello"};
  s21::set<const char *> second_set = {"322", "192", "123", "1232", "hello"};
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  for (; it2 != second_set.end(); ++it, ++it2) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(iterator, minus) {
  std::set<int> first_set;
  s21::set<int> second_set;
  for (int i = 0; i < 100; i++) {
    first_set.insert(i);
    second_set.insert(i);
  }
  auto it = first_set.end();
  auto it2 = second_set.end();
  it--;
  it2--;
  for (int i = 0; i < 99; i++) {
    ASSERT_EQ(*it, *it2);
    --it;
    --it2;
  }
}
TEST(iterator, deminus) {
  std::set<int> first_set;
  s21::set<int> second_set;
  for (int i = 0; i < 100; i++) {
    first_set.insert(i);
    second_set.insert(i);
  }
  auto it = first_set.end();
  auto it2 = second_set.end();
  it--;
  it2--;
  for (int i = 0; i < 99; i++) {
    ASSERT_EQ(*it, *it2);
    it--;
    it2--;
  }
}
TEST(const_iterator, single) {
  std::set<const char *> first_set = {"322", "192", "123", "1232", "hello"};
  s21::set<const char *> second_set = {"322", "192", "123", "1232", "hello"};
  auto it = first_set.cbegin();
  auto it2 = second_set.cbegin();
  for (; it2 != second_set.cend(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(empty, true_check) {
  std::set<char> first_set;
  s21::set<char> second_set;
  ASSERT_EQ(first_set.empty(), second_set.empty());
}
TEST(empty, false_check) {
  std::set<int> first_set = {2, 3, 5};
  s21::set<int> second_set = {3, 322, 322};
  ASSERT_EQ(first_set.empty(), second_set.empty());
}
TEST(size, empty) {
  std::set<char> first_set;
  s21::set<char> second_set;
  ASSERT_EQ(first_set.size(), second_set.size());
}
TEST(size, not_empty) {
  std::set<int> first_set = {32, 124, 3211};
  s21::set<int> second_set = {322, 125, 1233};
  ASSERT_EQ(first_set.size(), second_set.size());
}
TEST(max_size, max) {
  std::set<int> first_set = {32, 124, 3211};
  s21::set<int> second_set = {322, 125, 1233};
  ASSERT_EQ(first_set.max_size(), second_set.max_size());
}
TEST(clear, clear) {
  std::set<int> first_set = {32, 124, 3211};
  s21::set<int> second_set = {322, 125, 1233};
  first_set.clear();
  second_set.clear();
  ASSERT_EQ(first_set.size(), second_set.size());
  ASSERT_EQ(first_set.empty(), second_set.empty());
}
TEST(insert, true_test) {
  std::set<int> first_set = {32, 124, 3211};
  s21::set<int> second_set = {322, 125, 1233};
  std::pair<std::set<int>::iterator, bool> first_res = first_set.insert(5);
  std::pair<s21::set<int>::iterator, bool> second_res = second_set.insert(5);
  ASSERT_EQ(*first_res.first, *second_res.first);
  ASSERT_EQ(first_res.second, second_res.second);
}
TEST(erase, single) {
  std::set<int> first_set = {32, 124, 3211};
  s21::set<int> second_set = {32, 124, 3211};
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
TEST(erase, many) {
  s21::set<int> set;
  for (int i = 0; i < 100; i++) {
    set.insert(i);
  }
  for (int i = 0; i < 100; i++) {
    set.erase(set.begin());
  }
  ASSERT_EQ(set.empty(), true);
}
TEST(swap, single) {
  std::set<const char *> first_set = {"hello, school, 21"};
  s21::set<const char *> second_set = {"hello, school, 21"};
  std::set<const char *> swap_for_first = {"you, are, welcome"};
  s21::set<const char *> swap_for_second = {"you, are, welcome"};
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
  std::set<int> first_set = {1, 50, 322};
  s21::set<int> second_set = {1, 50, 322};
  std::set<int> first_merge = {32, 124, 3211};
  s21::set<int> second_merge = {32, 124, 3211};
  first_set.merge(first_merge);
  second_set.merge(second_merge);
  auto it = first_set.begin();
  auto it2 = second_set.begin();
  for (; it != first_set.end(); it++, it2++) {
    ASSERT_EQ(*it, *it2);
  }
}
TEST(find, true_test) {
  std::set<const char *> first_set = {"hello", "world", "i'm", "here"};
  s21::set<const char *> second_set = {"hello", "world", "i'm", "here"};
  auto it = first_set.find("world");
  auto it2 = second_set.find("world");
  EXPECT_STREQ(*it, *it2);
}
TEST(contains, true_test) {
  s21::set<int> second_set = {1, 50, 322, 215, 32322, 12314};
  ASSERT_EQ(true, second_set.contains(50));
}
TEST(contains, false_test) {
  s21::set<int> second_set = {1, 50, 322, 215, 32322, 12314};
  ASSERT_EQ(false, second_set.contains(323));
}
TEST(insert_many, single) {
  s21::set<int> my_set = {1, 2, 3};
  s21::vector<int> cmp_vector = {4, 7, 8};
  s21::vector<std::pair<s21::set<int>::iterator, bool>> res =
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
