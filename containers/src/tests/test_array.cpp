#include "../templates/s21_array.h"
#include "gtest/gtest.h"

//                 ******* Constructors *******

TEST(Array_Constructor_Default, Default_Int) {
  s21::array<int, 3> arr_int1;
  s21::array<int, 5> arr_int2;

  EXPECT_EQ(arr_int1.empty(), 0);
  EXPECT_EQ(arr_int2.empty(), 0);
  EXPECT_EQ(arr_int1.size(), 3);
  EXPECT_EQ(arr_int2.size(), 5);
  EXPECT_EQ(arr_int1.max_size(), 3);
  EXPECT_EQ(arr_int2.max_size(), 5);
}

TEST(Array_Constructor_InitList, InitList_Int) {
  s21::array<int, 5> int_arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(int_arr.size(), 5);
  EXPECT_EQ(int_arr.max_size(), 5);
  EXPECT_FALSE(int_arr.empty());
  EXPECT_EQ(int_arr.front(), 1);
  EXPECT_EQ(int_arr.back(), 5);
}

TEST(Array_Constructor_InitList, InitList_Float) {
  s21::array<float, 5> arr = {0.1, 0.2, 0.3, 0.4, 0.5};
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr.max_size(), 5);
  EXPECT_FALSE(arr.empty());
  EXPECT_FLOAT_EQ(arr.front(), 0.1);
  EXPECT_FLOAT_EQ(arr.back(), 0.5);
}

TEST(Array_Constructor_InitList, InitList_String) {
  s21::array<std::string, 5> arr = {"Apple", "Orange", "Watermelon", "Banana",
                                    "Cherry"};
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr.max_size(), 5);
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(arr.front(), "Apple");
  EXPECT_EQ(arr.back(), "Cherry");
}

TEST(Array_Constructor_InitList, InitList_Throw) {
  s21::array<int, 2> int_arr1;
  s21::array<int, 3> int_arr2 = {1, 2, 3};
  EXPECT_THROW((int_arr1 = {1, 2, 3}), std::out_of_range);
  EXPECT_THROW((int_arr2.at(3)), std::out_of_range);
  EXPECT_THROW((int_arr2[3]), std::out_of_range);
}

TEST(Array_Copy_Constructor, Copy_Constructor_Int) {
  s21::array<int, 5> int_arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> int_arr2(int_arr1);
  EXPECT_EQ(int_arr1[0], int_arr2[0]);
  EXPECT_EQ(int_arr1[1], int_arr2[1]);
  EXPECT_EQ(int_arr1[2], int_arr2[2]);
  EXPECT_EQ(int_arr1[3], int_arr2[3]);
  EXPECT_EQ(int_arr1[4], int_arr2[4]);
}

TEST(Array_Move_Constructor, Move_Constructor_Int) {
  s21::array<int, 5> int_arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> int_arr2(std::move(int_arr1));

  EXPECT_EQ(int_arr2.at(0), 1);
  EXPECT_EQ(int_arr2[0], 1);
  EXPECT_EQ(int_arr2[1], 2);
  EXPECT_EQ(int_arr2[2], 3);
  EXPECT_EQ(int_arr2[3], 4);
  EXPECT_EQ(int_arr2[4], 5);
}

TEST(Array_Move_Constructor, Move_Constructor_String) {
  s21::array<std::string, 5> arr1 = {"Apple", "Orange", "Watermelon", "Banana",
                                     "Cherry"};
  s21::array<std::string, 5> arr2(std::move(arr1));

  EXPECT_EQ(arr2.front(), "Apple");
  EXPECT_EQ(arr2.back(), "Cherry");
  EXPECT_THROW((arr1[3]), std::out_of_range);
}

TEST(Array_Assignment_Operator, Assign_Int) {
  s21::array<int, 5> int_arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> int_arr2;
  int_arr2 = std::move(int_arr1);
  EXPECT_EQ(int_arr2[0], 1);
  EXPECT_EQ(int_arr2[1], 2);
  EXPECT_EQ(int_arr2[2], 3);
  EXPECT_EQ(int_arr2[3], 4);
  EXPECT_EQ(int_arr2[4], 5);
}

TEST(Array_Assignment_Operator, Assign_String) {
  s21::array<std::string, 5> arr1 = {"Apple", "Orange", "Watermelon", "Banana",
                                     "Cherry"};
  s21::array<std::string, 5> arr2;
  arr2 = std::move(arr1);

  EXPECT_EQ(arr2.front(), "Apple");
  EXPECT_EQ(arr2.back(), "Cherry");
  EXPECT_THROW((arr1[3]), std::out_of_range);
}

//                 ******* Array access *******
TEST(Array_Size, Size_Int) {
  s21::array<int, 3> arr_int1;
  s21::array<int, 5> arr_int2;

  EXPECT_EQ(arr_int1.size(), 3);
  EXPECT_EQ(arr_int2.size(), 5);
}

TEST(Array_Size, Size_Float) {
  s21::array<float, 3> arr_int1;
  s21::array<float, 5> arr_int2;

  EXPECT_EQ(arr_int1.size(), 3);
  EXPECT_EQ(arr_int2.size(), 5);
}

TEST(Array_Size, Size_String) {
  s21::array<std::string, 3> arr_string1;
  s21::array<std::string, 7> arr_string2;

  EXPECT_EQ(arr_string1.size(), 3);
  EXPECT_EQ(arr_string2.size(), 7);
}

TEST(Array_Modifier, Modifier_fill_int) {
  s21::array<int, 5> arr;
  arr.fill(42);

  EXPECT_EQ(arr[0], 42);
  EXPECT_EQ(arr[1], 42);
  EXPECT_EQ(arr[2], 42);
  EXPECT_EQ(arr[3], 42);
  EXPECT_EQ(arr[4], 42);
}

TEST(Array_Modifier, Modifier_fill_float) {
  s21::array<float, 5> arr;
  arr.fill(3.141595);
  EXPECT_FLOAT_EQ(arr.at(0), 3.141595);
  EXPECT_FLOAT_EQ(arr.at(1), 3.141595);
  EXPECT_FLOAT_EQ(arr.at(2), 3.141595);
  EXPECT_FLOAT_EQ(arr.at(3), 3.141595);
  EXPECT_FLOAT_EQ(arr.at(4), 3.141595);
}

TEST(Array_Modifier, Modifier_fill_String) {
  s21::array<std::string, 5> arr;
  std::string s = "Apple";
  arr.fill(s);

  EXPECT_EQ(arr.front(), "Apple");
  EXPECT_EQ(arr.at(3), "Apple");
  EXPECT_EQ(arr.back(), "Apple");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
