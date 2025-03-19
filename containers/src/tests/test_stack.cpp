#include <gtest/gtest.h>

#include <stack>

#include "../templates/s21_containers.h"

class test_stack {
 private:
  int size = 0;

 public:
  test_stack() {}
  test_stack(const test_stack &val) {
    if (val.size != 0) {
      throw std::exception();
    }
  }
  void set_size() { this->size = 100; }
};

TEST(constructor, def) {
  std::stack<int> origin;
  s21::stack<int> my;
  ASSERT_EQ(origin.size(), my.size());
  ASSERT_EQ(origin.empty(), my.empty());
}
TEST(constructor, init_list) {
  s21::vector<int> check_my = {421, 56, 4, 3, 1};
  s21::stack<int> my = {1, 3, 4, 56, 421};
  ASSERT_EQ(5, my.size());
  ASSERT_EQ(0, my.empty());
  for (auto it = check_my.begin(); it != check_my.end(); it++) {
    ASSERT_EQ(*it, my.top());
    my.pop();
  }
}
TEST(constructor, copy) {
  s21::vector<int> check_my = {421, 56, 4, 3, 1};
  s21::stack<int> my = {1, 3, 4, 56, 421};
  s21::stack<int> cpy_my{my};
  ASSERT_EQ(5, cpy_my.size());
  ASSERT_EQ(0, cpy_my.empty());
  for (auto it = check_my.begin(); it != check_my.end(); it++) {
    ASSERT_EQ(*it, cpy_my.top());
    cpy_my.pop();
  }
}
TEST(eq, copy) {
  s21::vector<int> check_my = {421, 56, 4, 3, 1};
  s21::stack<int> my = {1, 3, 4, 56, 421};
  s21::stack<int> cpy_my;
  cpy_my = my;
  ASSERT_EQ(5, cpy_my.size());
  ASSERT_EQ(0, cpy_my.empty());
  for (auto it = check_my.begin(); it != check_my.end(); it++) {
    ASSERT_EQ(*it, cpy_my.top());
    cpy_my.pop();
  }
}
TEST(eq, copy2) {
  s21::vector<int> check_my = {421, 56, 4, 3, 1};
  s21::stack<int> my = {1, 3, 4, 56, 421};
  s21::stack<int> cpy_my = {2, 3};
  cpy_my = my;
  ASSERT_EQ(5, cpy_my.size());
  ASSERT_EQ(0, cpy_my.empty());
  for (auto it = check_my.begin(); it != check_my.end(); it++) {
    ASSERT_EQ(*it, cpy_my.top());
    cpy_my.pop();
  }
}
TEST(constructor, cpy_eq) {
  test_stack b;
  test_stack c;
  s21::stack<test_stack> a = {b, c};
  a[0].set_size();
  s21::stack<test_stack> d;
  ASSERT_ANY_THROW(d = a);
}
TEST(constructor, cpy) {
  test_stack b;
  test_stack c;
  s21::stack<test_stack> a = {b, c};
  a[0].set_size();
  ASSERT_ANY_THROW(s21::stack<test_stack> d{a});
}
TEST(push, exc) {
  test_stack b;
  test_stack c;
  s21::stack<test_stack> a = {b, c};
  a[0].set_size();
  ASSERT_ANY_THROW(a.push(a[0]));
}
TEST(push, exc2) {
  test_stack b;
  test_stack c;
  s21::stack<test_stack> a = {b, c};
  b.set_size();
  ASSERT_ANY_THROW(a.push(b));
}
TEST(constructor, move) {
  s21::vector<int> check_my = {421, 56, 4, 3, 1};
  s21::stack<int> my = {1, 3, 4, 56, 421};
  s21::stack<int> move_my = std::move(my);
  ASSERT_EQ(5, move_my.size());
  ASSERT_EQ(0, move_my.empty());
  for (auto it = check_my.begin(); it != check_my.end(); it++) {
    ASSERT_EQ(*it, move_my.top());
    move_my.pop();
  }
  ASSERT_EQ(1, my.empty());
}
TEST(top, single) {
  std::stack<int> origin;
  s21::stack<int> my = {1, 2, 3, 4, 5};
  for (int i = 1; i < 6; i++) {
    origin.push(i);
  }
  ASSERT_EQ(origin.top(), my.top());
}
TEST(empty, true_test) {
  std::stack<int> origin;
  s21::stack<int> my;
  ASSERT_EQ(origin.empty(), my.empty());
}
TEST(empty, false_test) {
  std::stack<int> origin;
  s21::stack<int> my = {1, 2, 3};
  for (int i = 1; i < 6; i++) {
    origin.push(i);
  }
  ASSERT_EQ(origin.empty(), my.empty());
}
TEST(size, single) {
  std::stack<int> origin;
  s21::stack<int> my = {1, 2, 3, 4, 5, 6};
  for (int i = 1; i < 7; i++) {
    origin.push(i);
  }
  ASSERT_EQ(origin.size(), my.size());
}
TEST(push, single) {
  std::stack<int> origin;
  s21::stack<int> my;
  for (int i = 1; i < 100; i++) {
    origin.push(i);
    my.push(i);
    ASSERT_EQ(origin.top(), my.top());
  }
}
TEST(pop, single) {
  std::stack<int> origin;
  s21::stack<int> my;
  for (int i = 1; i < 100; i++) {
    origin.push(i);
    my.push(i);
  }
  for (int i = 1; i < 99; i++) {
    origin.pop();
    my.pop();
    ASSERT_EQ(origin.top(), my.top());
  }
}
TEST(swap, single) {
  s21::stack<int> first = {1, 2, 3, 4, 5};
  s21::stack<int> second = {22, 33, 44, 55, 66};
  s21::vector<int> check_first = {66, 55, 44, 33, 22};
  s21::vector<int> check_second = {5, 4, 3, 2, 1};
  first.swap(second);
  for (auto it = check_first.begin(); it != check_first.end(); it++) {
    ASSERT_EQ(*it, first.top());
    first.pop();
  }
  for (auto it = check_second.begin(); it != check_second.end(); it++) {
    ASSERT_EQ(*it, second.top());
    second.pop();
  }
}
TEST(insert_many, single) {
  s21::stack<int> my;
  s21::vector<int> check = {5, 4, 3, 2, 1};
  my.insert_many_back(1, 2, 3, 4, 5);
  for (auto it = check.begin(); it != check.end(); it++) {
    ASSERT_EQ(my.top(), *it);
    my.pop();
  }
}
int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
