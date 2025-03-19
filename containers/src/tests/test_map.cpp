#include <gtest/gtest.h>

#include <map>

#include "../templates/s21_containers.h"
TEST(constructor, def) {
  std::map<int, const char *> origin;
  s21::map<int, const char *> my;
  ASSERT_EQ(origin.empty(), my.empty());
  ASSERT_EQ(origin.size(), my.size());
}
TEST(constructor, init_list) {
  std::map<int, const char *> origin = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  auto it = origin.begin();
  auto it2 = my.begin();
  for (; it != origin.end(); it++, it2++) {
    ASSERT_EQ((*it).first, (*it2).first);
    ASSERT_EQ((*it).second, (*it2).second);
  }
}
TEST(constructor, copy) {
  std::map<int, const char *> origin = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  std::map<int, const char *> origin_cpy(origin);
  s21::map<int, const char *> my_cpy(my);
  auto it = origin_cpy.begin();
  auto it2 = my_cpy.begin();
  for (; it != origin_cpy.end(); it++, it2++) {
    ASSERT_EQ((*it).first, (*it2).first);
    ASSERT_EQ((*it).second, (*it2).second);
  }
}
TEST(constructor, move) {
  std::map<int, const char *> origin = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  std::map<int, const char *> origin_cpy = std::move(origin);
  s21::map<int, const char *> my_cpy = std::move(my);
  auto it = origin_cpy.begin();
  auto it2 = my_cpy.begin();
  for (; it != origin_cpy.end(); it++, it2++) {
    ASSERT_EQ((*it).first, (*it2).first);
    ASSERT_EQ((*it).second, (*it2).second);
  }
}
TEST(at, right) {
  std::map<int, const char *> origin = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  ASSERT_EQ(origin.at(2), my.at(2));
}
TEST(at, false_var) {
  std::map<int, const char *> origin = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  ASSERT_ANY_THROW(origin.at(4));
  ASSERT_ANY_THROW(my.at(4));
}
TEST(brackets, true_var) {
  std::map<int, const char *> origin = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  ASSERT_EQ(origin[3], my[3]);
}
TEST(brackets, false_var) {
  std::map<int, const char *> origin = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  origin[100] = "alilua";
  my[100] = "alilua";
  ASSERT_EQ(origin[100], my[100]);
}
TEST(iterator, iterators) {
  std::map<int, const char *> origin = {{5, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my = {{5, "Hello"}, {2, "my"}, {3, "friend"}};
  auto it = origin.begin();
  auto it2 = my.begin();
  for (; it != origin.end(); it++, it2++) {
    ASSERT_EQ((*it).first, (*it2).first);
    ASSERT_EQ((*it).second, (*it2).second);
  }
}
TEST(clear, single) {
  std::map<int, const char *> origin = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  origin.clear();
  my.clear();
  ASSERT_EQ(origin.size(), my.size());
  ASSERT_EQ(origin.empty(), my.empty());
}
TEST(insert, true_test) {
  std::map<int, const char *> origin = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  std::pair<int, const char *> pair = {5, "from"};
  origin.insert(pair);
  my.insert(pair);
  auto it = origin.begin();
  auto it2 = my.begin();
  for (; it != origin.end(); it++, it2++) {
    ASSERT_EQ((*it).first, (*it2).first);
    ASSERT_EQ((*it).second, (*it2).second);
  }
}
TEST(insert, false_test) {
  std::map<int, const char *> origin = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  std::pair<int, const char *> pair = {1, "from"};
  auto check_origin = origin.insert(pair);
  auto check_my = my.insert(pair);
  ASSERT_EQ((*check_origin.first).first, (*check_my.first).first);
  ASSERT_EQ((*check_origin.first).second, (*check_my.first).second);
  ASSERT_EQ(check_origin.second, check_my.second);
}
TEST(insert_or_assign, insert) {
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  std::pair<int, const char *> pair = {4, "from"};
  my.insert_or_assign(pair.first, pair.second);
  ASSERT_EQ(my.contains(4), true);
  ASSERT_EQ(my[4], pair.second);
}
TEST(insert_or_assign, assign) {
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  std::pair<int, const char *> pair = {1, "from"};
  my.insert_or_assign(pair.first, pair.second);
  ASSERT_EQ(my.contains(1), true);
  ASSERT_EQ(my[1], pair.second);
}
TEST(erase, single) {
  std::map<int, const char *> origin = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {3, "friend"}};
  origin.erase(origin.begin());
  my.erase(my.begin());
  auto it = origin.begin();
  auto it2 = my.begin();
  for (; it != origin.end(); it++, it2++) {
    ASSERT_EQ((*it).first, (*it2).first);
    ASSERT_EQ((*it).second, (*it2).second);
  }
}
TEST(swap, single) {
  std::map<int, const char *> origin;
  s21::map<int, const char *> my;
  std::map<int, const char *> origin_swap = {
      {1, "Hello"}, {2, "my"}, {3, "friend"}};
  s21::map<int, const char *> my_swap{{1, "Hello"}, {2, "my"}, {3, "friend"}};
  origin.swap(origin_swap);
  my.swap(my_swap);
  ASSERT_EQ(origin.empty(), false);
  ASSERT_EQ(my.empty(), false);
  ASSERT_EQ(origin.empty(), my.empty());
  auto it = origin.begin();
  auto it2 = my.begin();
  for (; it != origin.end(); it++, it2++) {
    ASSERT_EQ((*it).first, (*it2).first);
    ASSERT_EQ((*it).second, (*it2).second);
  }
}
TEST(merge, single) {
  std::map<int, const char *> origin = {{1, "Hello"}, {2, "my"}, {4, "friend"}};
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {4, "friend"}};
  std::map<int, const char *> origin_swap = {{3, "only"}};
  s21::map<int, const char *> my_swap = {{3, "only"}};
  origin.merge(origin_swap);
  my.merge(my_swap);
  ASSERT_EQ(origin.size(), my.size());
  auto it = origin.begin();
  auto it2 = my.begin();
  for (; it != origin.end(); it++, it2++) {
    ASSERT_EQ((*it).first, (*it2).first);
    ASSERT_EQ((*it).second, (*it2).second);
  }
}
TEST(contains, single) {
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {4, "friend"}};
  ASSERT_EQ(true, my.contains(1));
  ASSERT_EQ(false, my.contains(5));
}
TEST(insert_many, single) {
  s21::map<int, const char *> my = {{1, "Hello"}, {2, "my"}, {4, "friend"}};
  s21::vector<std::pair<const int, const char *>> check = {
      {5, "i"}, {6, "was"}, {7, "waited"}, {8, "for"}, {9, "you"}};
  auto res = my.insert_many(std::move(check[0]), std::move(check[1]),
                            std::move(check[2]), std::move(check[3]),
                            std::move(check[4]));
  auto it2 = check.begin();
  for (auto it = res.begin(); it != res.end(); it++, it2++) {
    ASSERT_EQ((*it->first).first, it2->first);
    ASSERT_EQ((*it->first).second, it2->second);
    ASSERT_EQ(it->second, true);
  }
}
int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
