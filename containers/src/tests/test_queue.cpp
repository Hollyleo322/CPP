#include "../templates/s21_containers.h"
#include "gtest/gtest.h"

//                 ******* Constructors *******
TEST(Queue_Constructor, Default) {
  s21::queue<int> int_q;
  s21::queue<double> double_q;

  EXPECT_EQ(int_q.empty(), 1);
  EXPECT_EQ(double_q.empty(), 1);
}

TEST(Queue_Constructor, Initializer_List) {
  s21::queue<int> int_q = {1, 2, 3};

  EXPECT_EQ(int_q.empty(), 0);
}

TEST(Queue_Constructor, Copy) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2(int_q1);

  EXPECT_EQ(int_q2.empty(), 0);
}

TEST(Queue_Constructor, Move) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2(std::move(int_q1));

  EXPECT_EQ(int_q2.empty(), 0);
  EXPECT_EQ(int_q1.empty(), 1);
}

TEST(Queue_Constructor, Operator_eq) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2;
  int_q2 = std::move(int_q1);

  EXPECT_EQ(int_q2.empty(), 0);
}

// ****************** Queue access methods ******************

TEST(Queue_Access, ExceptionOnEmptyQueue) {
  s21::queue<int> queue;

  ASSERT_THROW(queue.front(), std::out_of_range);
  ASSERT_THROW(queue.back(), std::out_of_range);
  ASSERT_THROW(queue.pop(), std::out_of_range);
}

TEST(Queue_Access, EmptyQueue1) {
  s21::queue<int> queue;
  EXPECT_EQ(queue.empty(), 1);
  EXPECT_EQ(queue.size(), 0);
}

TEST(Queue_Access, EmptyQueue2) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2;

  EXPECT_EQ(int_q1.empty(), 0);
  EXPECT_EQ(int_q2.empty(), 1);
}

TEST(Queue_Access, FrontAndBackString) {
  s21::queue<std::string> queue;
  queue.push("Apple");
  queue.push("Orange");
  queue.push("Watermelon");

  ASSERT_EQ(queue.front(), "Apple");
  ASSERT_EQ(queue.back(), "Watermelon");

  queue.pop();
  ASSERT_EQ(queue.front(), "Orange");
  ASSERT_EQ(queue.back(), "Watermelon");

  queue.pop();
  ASSERT_EQ(queue.front(), "Watermelon");
  ASSERT_EQ(queue.back(), "Watermelon");
}

//               ******* Modifiers *******

TEST(Queue_Modifiers, Push_Empty) {
  s21::queue<int> int_q;
  int_q.push(7);

  EXPECT_EQ(int_q.empty(), 0);
  EXPECT_EQ(int_q.size(), 1);
}

TEST(Queue_Modifiers, Pop) {
  s21::queue<int> int_q = {1, 2, 3};
  int_q.pop();

  EXPECT_EQ(int_q.front(), 2);
}

TEST(Queue_Modifiers, Pop_Empty) {
  s21::queue<int> int_q;

  EXPECT_THROW(int_q.pop(), std::out_of_range);
}

TEST(Queue_Modifiers, PushAndPopString) {
  s21::queue<std::string> queue;
  queue.push("Hello");
  queue.push("World");

  ASSERT_EQ(queue.size(), 2);
  ASSERT_FALSE(queue.empty());
  ASSERT_EQ(queue.front(), "Hello");

  queue.pop();
  ASSERT_EQ(queue.size(), 1);
  ASSERT_EQ(queue.front(), "World");

  queue.pop();
  ASSERT_EQ(queue.size(), 0);
  ASSERT_TRUE(queue.empty());
}

TEST(Queue_Modifiers, SwapInt) {
  s21::queue<int> int_q1 = {1, 2, 3};
  s21::queue<int> int_q2;

  EXPECT_EQ(int_q1.empty(), 0);
  EXPECT_EQ(int_q2.empty(), 1);

  int_q1.swap(int_q2);

  EXPECT_EQ(int_q1.empty(), 1);
  EXPECT_EQ(int_q2.empty(), 0);
}

TEST(Queue_Modifiers, SwapString) {
  s21::queue<std::string> queue1 = {"Apple", "Orange", "Watermelon"};
  s21::queue<std::string> queue2 = {"Banana", "Cherry", "Grapefruit"};

  queue1.swap(queue2);

  ASSERT_EQ(queue2.size(), 3);
  ASSERT_EQ(queue2.front(), "Apple");
  ASSERT_EQ(queue2.back(), "Watermelon");

  ASSERT_EQ(queue1.size(), 3);
  ASSERT_EQ(queue1.front(), "Banana");
  ASSERT_EQ(queue1.back(), "Grapefruit");
}

TEST(Queue_Insert_Many, InsertManyBackInt) {
  s21::queue<int> queue;
  queue.insert_many_back(1, 2, 3, 4, 5);

  ASSERT_EQ(queue.size(), 5);
  ASSERT_FALSE(queue.empty());
  ASSERT_EQ(queue.front(), 1);
  ASSERT_EQ(queue.back(), 5);

  queue.pop();
  ASSERT_EQ(queue.size(), 4);
  ASSERT_EQ(queue.front(), 2);
  ASSERT_EQ(queue.back(), 5);

  queue.insert_many_back(6, 7, 8);
  ASSERT_EQ(queue.size(), 7);
  ASSERT_EQ(queue.front(), 2);
  ASSERT_EQ(queue.back(), 8);
}

TEST(Queue_Insert_Many, InsertManyBackString) {
  s21::queue<std::string> queue;
  queue.insert_many_back("Apple", "Orange", "Banana");

  ASSERT_EQ(queue.size(), 3);
  ASSERT_FALSE(queue.empty());
  ASSERT_EQ(queue.front(), "Apple");
  ASSERT_EQ(queue.back(), "Banana");

  queue.pop();
  ASSERT_EQ(queue.size(), 2);
  ASSERT_EQ(queue.front(), "Orange");
  ASSERT_EQ(queue.back(), "Banana");

  queue.insert_many_back("Cherry", "Watermelon");
  ASSERT_EQ(queue.size(), 4);
  ASSERT_EQ(queue.front(), "Orange");
  ASSERT_EQ(queue.back(), "Watermelon");
}

//            ******* Run tests *******

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
