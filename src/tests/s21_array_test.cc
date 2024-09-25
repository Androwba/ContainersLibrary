#include "../s21_containersplus.h"
#include "gtest/gtest.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::Array<int, 7> arr;
  EXPECT_EQ((int)arr.size(), 7);
  for (auto &elem : arr) {
    EXPECT_EQ((int)elem, 0);
  }
}

TEST(ArrayTest, InitializerListConstructor) {
  s21::Array<int, 5> arr{1, 2, 3};
  EXPECT_EQ((int)arr.size(), 5);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  for (size_t i = 3; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }

  s21::Array<int, 5> arr1{1, 2, 3};
  ASSERT_EQ(arr1.size(), 5);
  ASSERT_EQ(arr1[0], 1);
  ASSERT_EQ(arr1[1], 2);
  ASSERT_EQ(arr1[2], 3);
  ASSERT_EQ(arr1[3], 0);
  ASSERT_EQ(arr1[4], 0);

  s21::Array<double, 4> arr2{4.5, 3.2};
  ASSERT_EQ(arr2.size(), 4);
  ASSERT_EQ(arr2[0], 4.5);
  ASSERT_EQ(arr2[1], 3.2);
  ASSERT_EQ(arr2[2], 0);
  ASSERT_EQ(arr2[3], 0);
}

TEST(ArrayTest, StringConstructorTest) {
  s21::Array<std::string, 2> input{std::string("aaaa"), "b"};
  s21::Array<std::string, 2> arr(input);

  ASSERT_EQ(arr.size(), 2);
  ASSERT_EQ(arr[0], "aaaa");
  ASSERT_EQ(arr[1], "b");
}

TEST(ArrayTest, CopyConstructorTest) {
  s21::Array<int, 3> arr1{1, 2, 3};
  s21::Array<int, 3> arr2{arr1};

  ASSERT_EQ(arr1.size(), 3);
  ASSERT_EQ(arr2.size(), 3);
  ASSERT_EQ(arr2[0], 1);
  ASSERT_EQ(arr2[1], 2);
  ASSERT_EQ(arr2[2], 3);

  arr1[0] = 10;
  ASSERT_EQ(arr1[0], 10);
  ASSERT_EQ(arr2[0], 1);
}

TEST(ArrayTest, CopyAssignmentOperator) {
  s21::Array<int, 5> arr1{1, 2, 3, 4, 5};
  s21::Array<int, 5> arr2{10, 20, 30, 40, 50};

  arr2 = arr1;
  EXPECT_EQ(arr1[0], arr2[0]);
  EXPECT_EQ(arr1[1], arr2[1]);
  EXPECT_EQ(arr1[2], arr2[2]);
  EXPECT_EQ(arr1[3], arr2[3]);
  EXPECT_EQ(arr1[4], arr2[4]);

  arr1[0] = 100;

  EXPECT_NE(arr1[0], arr2[0]);
  EXPECT_EQ(arr1[1], arr2[1]);
  EXPECT_EQ(arr1[2], arr2[2]);
  EXPECT_EQ(arr1[3], arr2[3]);
  EXPECT_EQ(arr1[4], arr2[4]);
}

TEST(ArrayTest, MoveConstructor) {
  s21::Array<int, 5> arr1{1, 2, 3, 4, 5};
  s21::Array<int, 5> arr2{std::move(arr1)};
  ASSERT_EQ(arr2.size(), 5);
  ASSERT_EQ(arr2[0], 1);
  ASSERT_EQ(arr2[1], 2);
  ASSERT_EQ(arr2[2], 3);
  ASSERT_EQ(arr2[3], 4);
  ASSERT_EQ(arr2[4], 5);

  s21::Array<std::string, 3> arr3{"Hello", "World", "!"};
  s21::Array<std::string, 3> arr4{std::move(arr3)};
  ASSERT_EQ(arr4.size(), 3);
  ASSERT_EQ(arr4[0], "Hello");
  ASSERT_EQ(arr4[1], "World");
  ASSERT_EQ(arr4[2], "!");
  EXPECT_EQ(arr3.data(), nullptr);
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::Array<int, 5> arr1{1, 2, 3, 4, 5};
  s21::Array<int, 5> arr2{};

  arr2 = std::move(arr1);

  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr2[i], i + 1);
  }
  EXPECT_EQ(arr1.data(), nullptr);
}

TEST(ArrayTest, ConstBracketOperator) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  const s21::Array<int, 5> &const_arr = arr;

  EXPECT_EQ(const_arr[0], 1);
  EXPECT_EQ(const_arr[2], 3);
  EXPECT_EQ(const_arr[4], 5);
}

TEST(ArrayTest, AtThrowsException) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST(ArrayTest, AtTest) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(4), 5);
}

TEST(ArrayTest, AtConstTest) {
  const s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(4), 5);
}

TEST(ArrayTest, AtConstThrowsException) {
  const s21::Array<int, 2> arr{1, 7};
  EXPECT_THROW(arr.at(3), std::out_of_range);
}

TEST(ArrayTest, Begin) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  EXPECT_EQ(&arr[0], arr.begin());
}

TEST(ArrayTest, End) {
  s21::Array<int, 7> arr{1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(&arr[7], arr.end());
}

TEST(ArrayTest, Rbegin) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  auto rbeg = arr.rbegin();
  ASSERT_EQ(*rbeg, 5);
}

TEST(ArrayTest, RendTest) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};

  auto rbegin = arr.rbegin();
  auto rend = arr.rend();

  ASSERT_EQ(*rbegin, 5);
  ASSERT_EQ(*(rend - 1), 1);
}

TEST(ArrayTest, RendIterator) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};

  auto rbegin = arr.rbegin();
  auto rend = arr.rend();
  for (int i{5}; rbegin != rend; ++rbegin, --i) {
    EXPECT_EQ(*rbegin, i);
  }

  auto begin = arr.begin();
  EXPECT_EQ(arr.rend().base(), begin);
}

TEST(ArrayTest, FrontReturnsCorrectReference) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  EXPECT_EQ(arr.front(), 1);
  arr.front() = 10;
  EXPECT_EQ(arr.front(), 10);
}

TEST(ArrayTest, ConstFrontTest) {
  const s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  EXPECT_EQ(arr.front(), 1);
}

TEST(ArrayTest, BackReturnsCorrectReference) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  EXPECT_EQ(arr.back(), 5);
  arr.back() = 20;
  EXPECT_EQ(arr.back(), 20);
}

TEST(ArrayTest, ConstBacktest) {
  const s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  EXPECT_EQ(arr.back(), 5);
}

TEST(ArrayTest, Data) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
  EXPECT_EQ(arr[4], 5);

  // Modify the array through the pointer returned by data()
  int *ptr = arr.data();
  for (int i{}; i < 5; ++i) {
    ptr[i] *= 2;
  }
  EXPECT_EQ(arr[0], 2);
  EXPECT_EQ(arr[1], 4);
  EXPECT_EQ(arr[2], 6);
  EXPECT_EQ(arr[3], 8);
  EXPECT_EQ(arr[4], 10);
}

TEST(ArrayTest, ConstDatatest) {
  const s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  EXPECT_EQ(arr.data(), &arr[0]);
}

TEST(ArrayTest, Empty) {
  s21::Array<int, 5> arr;
  EXPECT_TRUE(arr.empty());

  arr.fill(21);
  EXPECT_EQ(arr[0], 21);
  EXPECT_FALSE(arr.empty());

  s21::Array<int, 0> empty_arr;
  EXPECT_TRUE(empty_arr.empty());
}

TEST(ArrayTest, MaxSize) {
  s21::Array<int, 5> arr;
  EXPECT_EQ(arr.max_size(), 5);
}

TEST(ArrayTest, FillTest) {
  s21::Array<int, 5> arr{1, 2, 3, 4, 5};
  arr.fill(7);
  for (auto element : arr) {
    EXPECT_EQ(element, 7);
  }
}

TEST(ArrayTest, SwapTest) {
  s21::Array<int, 4> a{1, 2, 3, 4};
  s21::Array<int, 4> b{5, 6, 7, 8};

  a.swap(b);

  EXPECT_EQ(a[0], 5);
  EXPECT_EQ(a[1], 6);
  EXPECT_EQ(a[2], 7);
  EXPECT_EQ(a[3], 8);

  EXPECT_EQ(b[0], 1);
  EXPECT_EQ(b[1], 2);
  EXPECT_EQ(b[2], 3);
  EXPECT_EQ(b[3], 4);
}
