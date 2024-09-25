#include <gtest/gtest.h>

#include <list>

#include "../containers.h"

TEST(Constructor, test1) {
  list<int> a;
  std::list<int> b;
  // int rows = a.GetRows();
  // int cols = a.GetCols();
  // EXPECT_EQ(rows, 1);
  // EXPECT_EQ(cols, 1);
}

TEST(Unique, test1) {
  list<int> a;
  a.push_back(3);
  a.push_back(2);
  a.push_back(3);
  a.push_back(1);
  std::list<int> b;
  b.push_back(3);
  b.push_back(2);
  b.push_back(3);
  b.push_back(1);
  a.unique();
  b.unique();
  for (auto it = a.begin(); it != a.end(); ++it) EXPECT_EQ(b.back(), a.back());
  a.pop_back();
  b.pop_back();

  list<int> c({1, 2, 2, 3});
  c.unique();
  EXPECT_EQ(3, c.size());
}

TEST(Sort, test1) {
  list<int> a;
  a.sort();
  a.push_back(3);
  a.push_back(2);
  a.push_back(3);
  a.push_back(1);
  std::list<int> b;
  b.push_back(3);
  b.push_back(2);
  b.push_back(3);
  b.push_back(1);
  a.sort();
  b.sort();
  for (auto it = a.begin(); it != a.end(); ++it) EXPECT_EQ(b.back(), a.back());
  a.pop_back();
  b.pop_back();
}

TEST(Copy, test1) {
  list<int> a;
  a.push_back(3);
  a.push_back(2);
  a.push_back(3);
  a.push_back(1);
  list<int> b = a;
  for (auto it = a.begin(); it != a.end(); ++it) EXPECT_EQ(b.back(), a.back());
  a.pop_back();
  b.pop_back();
}

TEST(Empty, test1) {
  list<int> a(5);
  std::list<int> b(5);
  EXPECT_EQ(b.size(), a.size());
}

TEST(Max_size, test1) {
  list<int> a;
  std::list<int> b;
  EXPECT_EQ(b.max_size(), a.max_size());
}

TEST(Clear, test1) {
  list<int> a;
  a.push_front(3);
  a.push_front(1);
  a.push_front(2);
  a.push_front(2);
  a.clear();
  EXPECT_TRUE(a.empty());
}

TEST(Insert, test1) {
  list<int> a;
  a.push_back(3);
  a.push_back(2);
  a.push_back(3);
  a.push_back(1);
  std::list<int> b;
  b.push_back(3);
  b.push_back(2);
  b.push_back(3);
  b.push_back(1);
  a.insert(a.begin(), 4);
  b.insert(b.begin(), 4);
  for (auto it = a.end(); it != a.begin(); --it)
    EXPECT_EQ(b.front(), a.front());
  a.pop_front();
  b.pop_front();
}

TEST(Insert, test2) {
  list<int> a({1, 2, 3, 5});
  std::list<int> b({1, 2, 3, 5});
  a.insert(a.end(), 4);
  b.insert(b.end(), 4);
  for (auto it = a.end(); it != a.begin(); --it)
    EXPECT_EQ(b.front(), a.front());
  a.pop_front();
  b.pop_front();
}

TEST(Insert, test3) {
  list<int> a({1, 2, 3, 5});
  std::list<int> b({1, 2, 3, 5});
  int i = 0;
  for (auto it = a.end(); it != a.begin(); --it, i++)
    if (i == 2) {
      a.insert(it, 4);
    }
  for (auto it = b.end(); it != b.begin(); --it, i++)
    if (i == 2) {
      b.insert(it, 4);
    }
  for (auto it = a.end(); it != a.begin(); --it)
    EXPECT_EQ(b.front(), a.front());
  a.pop_front();
  b.pop_front();
}

TEST(Emplace, test1) {
  list<int> a({1, 2});
  a.emplace_back(3);
  ASSERT_EQ(a.back(), 3);
  list<int> b({1, 2});
  b.emplace_front(3);
  ASSERT_EQ(b.front(), 3);
}

TEST(Swap, test1) {
  list<int> a({1, 2, 3});
  list<int> b;
  a.swap(b);
  for (auto it = a.end(); it != a.begin(); --it)
    EXPECT_EQ(b.front(), a.front());
  a.pop_front();
  b.pop_front();
}

TEST(Eraise, test1) {
  list<int> a({1, 2, 3});
  a.erase(a.begin());
  EXPECT_EQ(2, a.front());
  EXPECT_EQ(3, a.back());

  list<int> b;
  EXPECT_THROW(b.erase(b.end()), std::invalid_argument);

  list<int> c({1, 2, 3});
  c.erase(--(c.end()));
  EXPECT_EQ(1, c.front());
}

TEST(Merge, test1) {
  list<int> a({1, 2, 3});
  list<int> b({4, 5, 6});
  a.merge(b);
  list<int> c({1, 2, 3, 4, 5, 6});
  for (auto it = a.end(); it != a.begin(); --it)
    EXPECT_EQ(c.front(), a.front());
  a.pop_front();
  c.pop_front();

  list<int> a_1;
  a_1.merge(b);
  for (auto it = a.end(); it != a.begin(); --it)
    EXPECT_EQ(a_1.front(), b.front());
  a_1.pop_front();
  b.pop_front();
}

TEST(Splice, test1) {
  list<int> a({1, 2, 3});
  list<int> b({4, 5, 6});
  a.splice(a.begin(), b);
  list<int> c({1, 4, 5, 6, 2, 3});
  for (auto it = a.end(); it != a.begin(); --it) EXPECT_EQ(c.back(), a.back());
  a.pop_back();
  c.pop_back();

  list<int> g;
  g.clear();
  g.splice(g.begin(), b);
}

TEST(Reverse, test1) {
  list<int> c({1, 2, 3, 4, 5, 6});
  c.reverse();
  list<int> a({6, 5, 4, 3, 2, 1});
  list<int>::const_iterator pos;
  for (pos = a.end(); pos != a.begin(); --pos) EXPECT_EQ(c.front(), a.front());
  a.pop_front();
  c.pop_front();
}

TEST(Pop, test1) {
  list<int> a({1});
  EXPECT_EQ(1, a.size());
  a.pop_front();
  EXPECT_EQ(0, a.size());
}

TEST(ConstIter, test1) {
  list<int> a;
  list<int>::const_iterator pos = a.end();
  list<int>::const_iterator pos_2 = a.end();
  EXPECT_TRUE(pos == pos_2);
}
