#include <gtest/gtest.h>

#include <iostream>
#include <vector>

#include "../containers.h"

template <typename T>
bool vector_cmp(s21::vector<T>& s21_, std::vector<T>& std_) {
  bool res = s21_.size() == std_.size();
  if (res) res = s21_.capacity() == std_.capacity();
  for (auto i = std_.begin(), j = s21_.begin(); i < std_.end() && res;
       i++, j++) {
    res = *i == *j;
  }
  return res;
}

TEST(end2, VECTOR) {
  std::vector<int> a{1, 2, 3, 4, 5};
  s21::vector<int> b{1, 2, 3, 4, 5};
  EXPECT_TRUE(*(a.end() - 1) == *(b.end() - 1));
}

TEST(insert, VECTOR) {
  std::vector<int> a{1, 2, 3, 4, 5};
  s21::vector<int> b{1, 2, 3, 4, 5};
  EXPECT_TRUE(*(a.insert(a.end(), 21)) == *(b.insert(b.end(), 21)));
  EXPECT_TRUE(vector_cmp(b, a));
}

TEST(insert2, VECTOR) {
  std::vector<int> a{1, 2, 3, 4, 5};
  s21::vector<int> b{1, 2, 3, 4, 5};
  EXPECT_TRUE(*(a.insert(a.begin(), 21)) == *(b.insert(b.begin(), 21)));
  EXPECT_TRUE(vector_cmp(b, a));
}

TEST(create_vector_free, VECTOR) {
  std::vector<int> a;
  s21::vector<int> b;
  EXPECT_TRUE(vector_cmp(b, a));
}

TEST(create_vector_n, VECTOR) {
  std::vector<int> b(10);
  s21::vector<int> a(10);
  EXPECT_TRUE(vector_cmp(a, b));
}

TEST(create_vector_n_fail, VECTOR) { EXPECT_ANY_THROW(s21::vector<int> b(-1)); }

TEST(create_vector_list, VECTOR) {
  std::initializer_list<int> items{1, 2, 3, 4, 5};
  std::vector<int> b(items);
  s21::vector<int> a(items);
  EXPECT_TRUE(vector_cmp(a, b));
}

TEST(create_vector_copy, VECTOR) {
  std::vector<int> a{1, 2, 3, 4, 5};
  s21::vector<int> b{1, 2, 3, 4, 5};
  std::vector<int> a2(a);
  s21::vector<int> b2(b);
  EXPECT_TRUE(vector_cmp(b2, a2));
}

TEST(create_vector_move, VECTOR) {
  std::vector<int> a(std::vector<int>{1, 2, 3, 4, 5});
  auto member = std::move(a);
  s21::vector<int> b(s21::vector<int>{1, 2, 3, 4, 5});
  auto member2 = std::move(b);
  EXPECT_TRUE(vector_cmp(member2, member));
}

TEST(create_vector_op_assign, VECTOR) {
  std::vector<int> a{1, 2, 3, 4, 5};
  s21::vector<int> b{1, 2, 3, 4, 5};
  std::vector<int> a2 = a;
  s21::vector<int> b2 = b;
  EXPECT_TRUE(vector_cmp(b2, a2));
}

TEST(create_vector_op_assign2, VECTOR) {
  std::vector<int> a{1, 2, 3, 4, 5};
  std::vector<int> b{1, 2, 3};
  s21::vector<int> a21{1, 2, 3, 4, 5};
  s21::vector<int> b21{1, 2, 3};
  a = b;
  a21 = b21;
  EXPECT_TRUE(vector_cmp(a21, a));
}

TEST(create_vector_op_assign3, VECTOR) {
  std::vector<int> a{1, 2, 3, 4, 5};
  std::vector<int> b{1, 2, 3};
  s21::vector<int> a21{1, 2, 3, 4, 5};
  s21::vector<int> b21{1, 2, 3};
  b = a;
  b21 = a21;
  EXPECT_TRUE(vector_cmp(b21, b));
}

TEST(at1, VECTOR) {
  std::vector<int> a{1, 2, 3, 4, 5};
  s21::vector<int> b{1, 2, 3, 4, 5};
  EXPECT_TRUE(a.at(2) == b.at(2));
}

TEST(at2, VECTOR) {
  std::vector<int> a{1, 2, 3, 4, 5};
  s21::vector<int> b{1, 2, 3, 4, 5};
  a.at(3) = 21;
  b.at(3) = 21;
  EXPECT_TRUE(a.at(3) == b.at(3));
}

TEST(oper_at, VECTOR) {
  std::vector<int> a{1, 2, 3, 4, 5};
  s21::vector<int> b{1, 2, 3, 4, 5};
  a[3] = 21;
  b[3] = 21;
  EXPECT_TRUE(a[3] == b[3]);
}

TEST(data, VECTOR) {
  std::vector<int> a{78, 16};
  s21::vector<int> b{78, 16};
  EXPECT_TRUE(a.data() != b.data());
  EXPECT_TRUE(*a.data() == *b.data());
}

TEST(empty_false, VECTOR) {
  std::vector<int> a{78, 16};
  s21::vector<int> b{78, 16};
  EXPECT_TRUE(a.empty() == b.empty());
}

TEST(empty_true, VECTOR) {
  std::vector<int> a;
  s21::vector<int> b;
  EXPECT_TRUE(a.empty() == b.empty());
}

TEST(reserve, VECTOR) {
  std::vector<int> a{78, 16};
  s21::vector<int> b{78, 16};
  a.reserve(5);
  b.reserve(5);
  EXPECT_TRUE(vector_cmp(b, a));
  a.reserve(5);
  b.reserve(5);
  EXPECT_TRUE(vector_cmp(b, a));
  a.reserve(1);
  b.reserve(1);
  EXPECT_TRUE(vector_cmp(b, a));
}

TEST(shrink_to_fit, VECTOR) {
  std::vector<int> a{78, 16};
  s21::vector<int> b{78, 16};
  a.pop_back();
  a.shrink_to_fit();
  b.pop_back();
  b.shrink_to_fit();
  EXPECT_TRUE(vector_cmp(b, a));
}

TEST(clear, VECTOR) {
  std::vector<int> a{78, 16};
  s21::vector<int> b{78, 16};
  a.clear();
  b.clear();
  EXPECT_TRUE(vector_cmp(b, a));
}

TEST(erase, VECTOR) {
  std::vector<int> a{78, 16, 21};
  s21::vector<int> b{78, 16, 21};
  a.erase(a.begin() + 1);
  b.erase(b.begin() + 1);
  EXPECT_TRUE(vector_cmp(b, a));
}

TEST(swap, VECTOR) {
  std::vector<int> a{78, 16, 21};
  std::vector<int> a2{7, 1};
  s21::vector<int> b{78, 16, 21};
  s21::vector<int> b2{7, 1};
  a.swap(a2);
  b.swap(b2);
  EXPECT_TRUE(vector_cmp(b, a));
}

TEST(max_size, VECTOR) {
  std::vector<int> a{78, 16, 21};
  std::vector<double> a2{7, 1};
  s21::vector<int> b{78, 16, 21};
  s21::vector<double> b2{7, 1};
  EXPECT_TRUE(a.max_size() == b.max_size());
  EXPECT_TRUE(a2.max_size() == b2.max_size());
}

TEST(emplace0, VECTOR) {
  s21::vector<int> b{78, 16, 21};
  std::vector<int> c{78, 16, 21};
  b.emplace(b.begin());
  EXPECT_TRUE(vector_cmp(b, c));
}

TEST(emplace1, VECTOR) {
  s21::vector<int> b{78, 16, 21};
  std::vector<int> c{78, 16, 21};
  b.emplace(b.begin(), 77);
  c.emplace(c.begin(), 77);
  EXPECT_TRUE(vector_cmp(b, c));
}

TEST(emplace3, VECTOR) {
  s21::vector<int> b{78, 16, 21};
  std::vector<int> c{78, 16, 21};
  b.emplace(b.begin(), 77, 15, 13);
  c.emplace(c.begin(), 77);
  c.emplace(c.begin() + 1, 15);
  c.emplace(c.begin() + 2, 13);
  EXPECT_TRUE(vector_cmp(b, c));
}

TEST(emplace5, VECTOR) {
  s21::vector<int> b{78, 16, 21};
  std::vector<int> c{78, 16, 21};
  b.emplace(b.begin(), 77, 15, 13, 5, 3);
  c.emplace(c.begin(), 77);
  c.emplace(c.begin() + 1, 15);
  c.emplace(c.begin() + 2, 13);
  c.emplace(c.begin() + 3, 5);
  c.emplace(c.begin() + 4, 3);
  EXPECT_TRUE(vector_cmp(b, c));
}

TEST(emplace_back0, VECTOR) {
  s21::vector<int> b{78, 16, 21};
  std::vector<int> c{78, 16, 21};
  b.emplace_back();
  EXPECT_TRUE(vector_cmp(b, c));
}

TEST(emplace_back1, VECTOR) {
  s21::vector<int> b{78, 16, 21};
  std::vector<int> c{78, 16, 21};
  b.emplace_back(77);
  c.emplace_back(77);
  EXPECT_TRUE(vector_cmp(b, c));
}

TEST(emplace_back3, VECTOR) {
  s21::vector<int> b{78, 16, 21};
  std::vector<int> c{78, 16, 21};
  b.emplace_back(77, 15, 13);
  c.emplace_back(77);
  c.emplace_back(15);
  c.emplace_back(13);
  EXPECT_TRUE(vector_cmp(b, c));
}

TEST(emplace_back5, VECTOR) {
  s21::vector<int> b{78, 16, 21};
  std::vector<int> c{78, 16, 21};
  b.emplace_back(77, 15, 13, 5, 3);
  c.emplace_back(77);
  c.emplace_back(15);
  c.emplace_back(13);
  c.emplace_back(5);
  c.emplace_back(3);
  EXPECT_TRUE(vector_cmp(b, c));
}

TEST(create_vector_op_assign4, VECTOR) {
  s21::vector<int> a21{1, 2, 3, 4, 5};
  a21 = s21::vector<int>{6, 7, 8};
  EXPECT_TRUE(*(a21.begin()) == 6);
  EXPECT_TRUE(*(a21.begin() + 1) == 7);
  EXPECT_TRUE(*(a21.begin() + 2) == 8);
}