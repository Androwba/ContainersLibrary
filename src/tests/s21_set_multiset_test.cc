#include "../containers/s21_IteratorTree.h"
#include "../containers/s21_set.h"
#include "../s21_containersplus.h"
#include "gtest/gtest.h"

TEST(MultisetTest, Insert) {
  s21::Multiset<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(2);
  s.insert(3);
  EXPECT_EQ(s.size(), 4);
}

TEST(MultisetTest, InsertAndEraseStringTest) {
  s21::Multiset<std::string> ms;
  ms.insert("apple");
  ms.insert("banana");
  ms.insert("orange");
  ASSERT_EQ(ms.size(), 3);

  ASSERT_TRUE(ms.contains("apple"));
  ASSERT_FALSE(ms.contains("grape"));

  ASSERT_EQ(ms.count("apple"), 1);
  ASSERT_EQ(ms.count("grape"), 0);

  ASSERT_TRUE(ms.contains("banana"));

  ms.erase("banana");
  ASSERT_FALSE(ms.contains("banana"));
}

TEST(MultisetTest, Erase) {
  s21::Multiset<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(2);
  s.insert(3);
  s.erase(2);
  EXPECT_EQ(s.size(), 3);
  s.erase(2);
  EXPECT_EQ(s.size(), 2);
}

TEST(MultisetTest, Size) {
  s21::Multiset<int> s;
  EXPECT_EQ(s.size(), 0);
  s.insert(1);
  s.insert(2);
  s.insert(2);
  s.insert(3);
  EXPECT_EQ(s.size(), 4);
  s.erase(2);
  EXPECT_EQ(s.size(), 3);
}

TEST(MultisetTest, Iterator) {
  s21::Multiset<int> ms;

  ms.insert(3);
  ms.insert(1);
  ms.insert(2);

  auto it = ms.begin();
  EXPECT_EQ((*it).key, 1);
  EXPECT_EQ(it->value, 1);

  ++it;
  EXPECT_EQ(it->key, 2);

  ++it;
  EXPECT_EQ(it->key, 3);

  ++it;
  EXPECT_EQ(it, ms.end());

  EXPECT_THROW(++it, std::out_of_range);
}

// RBTreeIterator constructor sets current_ to the leftmost node
TEST(MultisetTest, IteratorConstructor) {
  s21::Multiset<int> set;
  set.insert(3);
  set.insert(1);
  set.insert(5);
  set.insert(2);
  set.insert(4);

  s21::RBTreeIterator<int, int> it = set.begin();
  EXPECT_EQ((*it).key, 1);
}

// RBTreeIterator prefix increment operator returns the next node
TEST(MultisetTest, IteratorPrefixIncrement) {
  s21::Multiset<int> set;
  set.insert(3);
  set.insert(1);
  set.insert(5);

  s21::RBTreeIterator<int, int> it = set.begin();
  ++it;
  ++it;
  EXPECT_EQ(it->key, 5);
}

TEST(MultisetTest, SetIteratorBeginTest) {
  s21::Multiset<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);
  set.insert(4);

  ASSERT_EQ(set.size(), 4);
}

TEST(RBTreeIteratorTest, PreIncrement) {
  s21::Multiset<int> mset;
  mset.insert(3);
  s21::RBTreeIterator<int, int> it = mset.begin();
  EXPECT_EQ(it.current()->key, 3);
  ++it;
  EXPECT_EQ(it.current(), nullptr);
}

TEST(RBTreeIteratorTest, PostIncrement) {
  s21::Multiset<int> mset;
  mset.insert(3);
  s21::RBTreeIterator<int, int> it = mset.begin();
  EXPECT_EQ((it++).current()->key, 3);
  EXPECT_EQ(it.current(), nullptr);
}

TEST(RBTreeIteratorTest, Leftmostplusplus) {
  s21::RBTree<int, int> tree;
  tree.Insert(4, 4);
  tree.Insert(2, 2);
  tree.Insert(6, 6);
  tree.Insert(1, 1);
  tree.Insert(3, 3);
  tree.Insert(5, 5);
  tree.Insert(7, 7);

  // Start at the node with key 3
  s21::RBTreeIterator<int, int> iter(tree.GetRoot()->left->right);

  ++iter;
  EXPECT_EQ(iter.current()->key, 4);

  // hit the current_ = current_->left line
  ++iter;
  EXPECT_EQ(iter.current()->key, 5);

  ++iter;
  EXPECT_EQ(iter.current()->key, 6);

  ++iter;
  EXPECT_EQ(iter.current()->key, 7);

  ++iter;
  EXPECT_EQ(nullptr, iter.current());
}

TEST(RBTreeIteratorTest, OperatorBool) {
  s21::RBTree<int, int> tree;
  tree.Insert(3, 3);
  tree.Insert(1, 1);
  tree.Insert(4, 4);
  s21::RBTreeIterator<int, int> iter(tree.GetRoot());

  EXPECT_TRUE(iter);

  ++iter;
  EXPECT_EQ(4, iter.current()->key);
  EXPECT_TRUE(iter);
}

TEST(RBTreeIteratorTest, DecrementOperator) {
  s21::RBTree<int, int> tree;
  tree.Insert(4, 40);
  tree.Insert(2, 20);
  tree.Insert(1, 10);
  tree.Insert(3, 30);
  tree.Insert(6, 60);
  tree.Insert(5, 50);
  tree.Insert(7, 70);

  s21::RBTreeIterator<int, int> iter(tree.GetRoot());
  --iter;
  EXPECT_EQ(1, iter->key);
  EXPECT_EQ(10, iter->value);

  ++iter;
  ++iter;
  ++iter;
  ++iter;
  ++iter;
  ++iter;
  EXPECT_EQ(7, iter->key);
  EXPECT_EQ(70, iter->value);

  --iter;
  EXPECT_EQ(6, iter->key);
  EXPECT_EQ(60, iter->value);

  --iter;
  EXPECT_EQ(5, iter->key);
  EXPECT_EQ(50, iter->value);

  --iter;
  EXPECT_EQ(4, iter->key);
  EXPECT_EQ(40, iter->value);

  --iter;
  EXPECT_EQ(3, iter->key);
  EXPECT_EQ(30, iter->value);

  --iter;
  EXPECT_EQ(2, iter->key);
  EXPECT_EQ(20, iter->value);

  --iter;
  EXPECT_EQ(1, iter->key);
  EXPECT_EQ(10, iter->value);

  EXPECT_THROW(--iter, std::out_of_range);
}

TEST(RBTreeIteratorTest, DecrementOperatorPostfix) {
  s21::RBTree<int, int> tree;
  tree.Insert(4, 40);
  tree.Insert(2, 20);
  tree.Insert(1, 10);
  tree.Insert(3, 30);
  tree.Insert(6, 60);
  tree.Insert(5, 50);
  tree.Insert(7, 70);

  s21::RBTreeIterator<int, int> iter(tree.GetRoot());
  EXPECT_EQ(2, iter->key);
  EXPECT_EQ(20, iter->value);
  iter--;
  EXPECT_EQ(1, iter->key);
  EXPECT_EQ(10, iter->value);
}

TEST(MultisetTest, BeginAndEnd) {
  s21::Multiset<int> ms;

  // on empty set
  EXPECT_EQ(ms.begin(), ms.end());

  ms.insert(21);
  EXPECT_EQ(*ms.begin(), 21);
  EXPECT_EQ(++ms.begin(), ms.end());

  ms.insert(13);
  ms.insert(13);
  ms.insert(7);
  EXPECT_EQ(*ms.begin(), 7);
  EXPECT_EQ(*(++ms.begin()), 13);
  EXPECT_EQ(*(++ ++ms.begin()), 13);
}

TEST(MultisetTest, CurrentIsNullptrTest) {
  s21::Multiset<int> ms;

  auto it = ms.begin();  // hit this line  if (current_ == nullptr)
  EXPECT_FALSE(--it);
}

TEST(MultisetTest, DefaultConstructor) {
  s21::Multiset<int> ms;
  EXPECT_EQ(ms.size(), 0);
}

TEST(MultisetTest, Destructor) {
  s21::Multiset<int> *ms = new s21::Multiset<int>;
  ms->insert(1);
  ms->insert(2);
  delete ms;
  EXPECT_TRUE(true);
}

TEST(RBTreeIteratorTest, Rightmost) {
  s21::RBTree<int, int> tree;
  tree.Insert(5, 5);
  tree.Insert(3, 3);
  tree.Insert(7, 7);
  tree.Insert(2, 2);
  tree.Insert(4, 4);
  tree.Insert(6, 6);
  tree.Insert(8, 8);

  s21::RBTreeIterator<int, int> it(tree.GetRoot()->right->right);
  EXPECT_EQ(8, it->key);
  --it;
  EXPECT_EQ(7, it->key);
  --it;
  EXPECT_EQ(6, it->key);
  --it;
  EXPECT_EQ(5, it->key);
  --it;  // should move to node with key 4
  --it;  // should move to node with key 3
  --it;  // should move to node with key 2
  EXPECT_EQ(2, it->key);
  EXPECT_THROW(--it, std::out_of_range);
}

TEST(MultisetTest, ParameterizedConstructor) {
  s21::Multiset<int> ms({1, 2, 3});
  ASSERT_EQ(ms.size(), 3);
  ASSERT_TRUE(ms.find(1) != ms.end());
  ASSERT_TRUE(ms.find(2) != ms.end());
  ASSERT_TRUE(ms.find(3) != ms.end());
}

TEST(MultisetTest, FindAndInsertStringTest) {
  s21::Multiset<std::string> ms;

  ms.insert("hello");
  ms.insert("world");
  ms.insert("hello");
  ms.insert("again");

  EXPECT_EQ(ms.size(), 4);
  EXPECT_NE(ms.find("hello"), ms.end());
  EXPECT_NE(ms.find("world"), ms.end());
  EXPECT_NE(ms.find("again"), ms.end());

  ms.insert("foo");

  EXPECT_EQ(ms.size(), 5);
  EXPECT_NE(ms.find("foo"), ms.end());
}

TEST(MultisetTest, FindExistingKey) {
  s21::Multiset<int> ms{1, 2, 3, 3, 4};
  auto node = ms.find(3);
  ASSERT_TRUE(node != nullptr);
  ASSERT_EQ(node->key, 3);
}

TEST(MultisetTest, FindNonExistingKey) {
  s21::Multiset<int> ms{1, 2, 3, 3, 4};
  EXPECT_THROW(ms.find(5), std::out_of_range);
}

TEST(MultisetTest, EraseExistingElement) {
  s21::Multiset<int> multiset{1, 2, 3};
  multiset.erase(2);
  ASSERT_EQ(multiset.size(), 2);
}

TEST(MultisetTest, EraseNonExistingElement) {
  s21::Multiset<int> multiset{1, 2, 3};
  EXPECT_THROW(multiset.erase(4), std::out_of_range);
  ASSERT_EQ(multiset.size(), 3);
}

TEST(MultisetTest, EraseAllElements) {
  s21::Multiset<int> multiset{1, 2, 2, 3};
  multiset.erase(1);
  multiset.erase(2);
  multiset.erase(2);
  multiset.erase(3);
  ASSERT_EQ(multiset.size(), 0);
  ASSERT_EQ(multiset.begin(), multiset.end());
}

TEST(MultisetTest, Empty) {
  s21::Multiset<int> ms;
  EXPECT_TRUE(ms.empty());

  ms.insert(42);
  EXPECT_FALSE(ms.empty());

  ms.erase(42);
  EXPECT_TRUE(ms.empty());

  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  EXPECT_FALSE(ms.empty());

  ms.erase(2);
  EXPECT_FALSE(ms.empty());

  ms.erase(1);
  ms.erase(2);
  EXPECT_TRUE(ms.empty());
}

TEST(MultisetTest, Contains) {
  s21::Multiset<int> ms{1, 2, 2, 3};
  EXPECT_TRUE(ms.contains(3));
  EXPECT_FALSE(ms.contains(5));
}

TEST(MultisetTest, MaxSizeTest) {
  s21::Multiset<int> s;
  std::size_t expected_max_size =
      std::numeric_limits<std::size_t>::max() / ((sizeof(std::size_t) * 5) * 2);
  ASSERT_EQ(s.max_size(), expected_max_size);
}

TEST(MultisetTest, MaxSizeWithInt) {
  s21::Multiset<int> s;
  EXPECT_EQ(s.max_size(), SIZE_MAX / ((sizeof(size_t) * 5) * 2));
}

TEST(MultisetTest, MaxSizeWithString) {
  s21::Multiset<std::string> s;
  const std::size_t max_string_size =
      std::numeric_limits<std::string::size_type>::max();
  const std::size_t max_elements =
      std::numeric_limits<std::size_t>::max() / ((sizeof(std::size_t) * 5) * 2);
  const std::size_t expected_max_size = std::min(max_string_size, max_elements);
  EXPECT_EQ(s.max_size(), expected_max_size);
}

TEST(MultisetTest, MaxSizeWithChar) {
  s21::Multiset<char> s;
  EXPECT_EQ(s.max_size(), SIZE_MAX / ((sizeof(size_t) * 5) * 2) / sizeof(char));
}

TEST(MultisetTest, CountTest) {
  s21::Multiset<int> ms{1, 2, 2, 3, 3, 3};
  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 3);
  EXPECT_EQ(ms.count(4), 0);
}

TEST(MultisetTest, CopyAssignmentOperatorTest0) {
  s21::Multiset<int> ms1;
  s21::Multiset<int> ms2;
  ms1.insert(7);
  ms1 = ms2;
  EXPECT_EQ(ms2.size(), ms1.size());
}

TEST(MultisetTest, CopyAssignmentOperatorTest1) {
  s21::Multiset<int> ms1;
  ms1.insert(1);
  ms1.insert(2);
  ms1.insert(2);
  ms1.insert(3);

  s21::Multiset<int> ms2;
  ms2.insert(2);
  ms2.insert(3);
  ms2.insert(3);
  ms2.insert(4);

  ms1 = ms2;

  ASSERT_EQ(ms1.size(), 4);
  ASSERT_EQ(ms2.size(), 4);

  s21::Multiset<int>::iterator it1 = ms1.begin();
  s21::Multiset<int>::iterator it2 = ms2.begin();
  while (it1 != ms1.end() && it2 != ms2.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  ASSERT_EQ(it1, ms1.end());
  ASSERT_EQ(it2, ms2.end());
}

TEST(MultisetTest, CopyConstructorTest0) {
  s21::Multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(3);
  ms.insert(3);
  s21::Multiset<int> ms_copy(ms);
  ASSERT_EQ(ms.size(), ms_copy.size());
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    EXPECT_EQ(ms.count(it->key), ms_copy.count(it->key));
  }
}

TEST(MultisetTest, CopyConstructorTest1) {
  s21::Multiset<int> ms1{1, 2, 3, 3, 4};
  s21::Multiset<int> ms2{ms1};

  EXPECT_EQ(ms1.size(), ms2.size());

  auto it1 = ms1.begin();
  auto it2 = ms2.begin();
  while (it1 != ms1.end() && it2 != ms2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  for (auto it = ms1.begin(); it != ms1.end(); ++it) {
    EXPECT_TRUE(ms2.contains(it->key));
  }
}

TEST(MultisetTest, CopyConstructorTest2) {
  s21::Multiset<std::string> ms1({"yo", "hey", "hi"});
  s21::Multiset<std::string> ms2(ms1);
  ASSERT_EQ(ms1.size(), ms2.size());
  auto it1 = ms1.begin(), it2 = ms2.begin();
  while (it1 != ms1.end() && it2 != ms2.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(MultisetTest, MoveConstructor) {
  s21::Multiset<int> a{1, 2, 2, 3, 4, 4, 4};
  s21::Multiset<int> b{std::move(a)};
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(b.size(), 7);
  EXPECT_TRUE(b.contains(1));
  EXPECT_TRUE(b.contains(2));
  EXPECT_TRUE(b.contains(3));
  EXPECT_TRUE(b.contains(4));
}

TEST(MultisetTest, MoveAssignmentOperator) {
  s21::Multiset<int> ms1{1, 2, 3, 2, 4};
  s21::Multiset<int> ms2{5, 6, 7};

  ms2 = std::move(ms1);

  EXPECT_EQ(ms2.size(), 5);
  EXPECT_EQ(ms2.count(1), 1);
  EXPECT_EQ(ms2.count(2), 2);
  EXPECT_EQ(ms2.count(3), 1);
  EXPECT_EQ(ms2.count(4), 1);
}

TEST(MultisetTest, Merge) {
  s21::Multiset<int> ms1{1, 2, 2, 3, 4, 4, 4, 5};
  s21::Multiset<int> ms2{1, 2, 2, 3, 3, 4, 6, 7};

  ms1.merge(ms2);

  EXPECT_EQ(ms1.size(), 16);
  EXPECT_EQ(ms1.count(1), 2);
  EXPECT_EQ(ms1.count(2), 4);
  EXPECT_EQ(ms1.count(3), 3);
  EXPECT_EQ(ms1.count(4), 4);
  EXPECT_EQ(ms1.count(5), 1);
  EXPECT_EQ(ms1.count(6), 1);
  EXPECT_EQ(ms1.count(7), 1);

  EXPECT_EQ(ms2.size(), 0);
}

TEST(MultisetTest, MergeEmpty) {
  s21::Multiset<int> ms1{1, 2, 3};
  s21::Multiset<int> ms2{};

  ms1.merge(ms2);

  EXPECT_EQ(ms1.size(), 3);
  EXPECT_EQ(ms1.count(1), 1);
  EXPECT_EQ(ms1.count(2), 1);
  EXPECT_EQ(ms1.count(3), 1);

  EXPECT_EQ(ms2.size(), 0);
}

TEST(MultisetTest, MergeEmptyMultisets) {
  s21::Multiset<int> set1, set2;
  set1.merge(set2);
  ASSERT_TRUE(set1.empty());
  ASSERT_TRUE(set2.empty());
}

TEST(MultisetTest, MergeEmptyDest) {
  s21::Multiset<int> set1, set2({1, 2, 3});
  set1.merge(set2);
  ASSERT_EQ(set1.size(), 3);
  ASSERT_TRUE(set2.empty());
}

TEST(MultisetTest, MergeSameSize) {
  s21::Multiset<int> set1({1, 2, 3}), set2({4, 5, 6});
  set1.merge(set2);
  ASSERT_EQ(set1.size(), 6);
  ASSERT_TRUE(set2.empty());
}

TEST(MultisetTest, MergeSourceLarger) {
  s21::Multiset<int> set1({1, 2, 3}), set2({4, 5, 6, 7});
  set1.merge(set2);
  ASSERT_EQ(set1.size(), 7);
  ASSERT_TRUE(set2.empty());
}

TEST(MultisetTest, MergeDestLarger) {
  s21::Multiset<int> set1({1, 2, 3, 4}), set2({5, 6, 7});
  set1.merge(set2);
  ASSERT_EQ(set1.size(), 7);
  ASSERT_TRUE(set2.empty());
}

TEST(MultisetTest, MergeDouble) {
  s21::Multiset<double> set1({1.1, 2.2, 3.3}), set2({4.4, 5.5, 6.6});
  set1.merge(set2);
  ASSERT_EQ(set1.size(), 6);
  ASSERT_TRUE(set2.empty());
}

TEST(MultisetTest, MergeDuplicateValues) {
  s21::Multiset<int> set1({1, 1, 2, 3}), set2({1, 3, 4});
  set1.merge(set2);
  ASSERT_EQ(set1.size(), 7);
  ASSERT_TRUE(set2.empty());
}

TEST(MultisetTest, MergeSameSet) {
  s21::Multiset<int> ms1{1, 2, 2, 3, 4, 4, 4, 5};

  ms1.merge(ms1);
  EXPECT_EQ(ms1.size(), ms1.size());
  EXPECT_EQ(ms1.count(1), 1);
  EXPECT_EQ(ms1.count(2), 2);
  EXPECT_EQ(ms1.count(3), 1);
  EXPECT_EQ(ms1.count(4), 3);
  EXPECT_EQ(ms1.count(5), 1);
}

TEST(MultisetTest, LowerUpperBoundsVsOriginal) {
  s21::Multiset<int> ms({0, 0, 0, 1, 3, 3, 3, 5});
  std::multiset<int> standart({0, 0, 0, 1, 3, 3, 3, 5});

  auto ms_low = ms.lower_bound(3);
  auto ms_up = ms.upper_bound(3);

  auto standart_low = standart.lower_bound(3);
  auto standart_up = standart.upper_bound(3);

  EXPECT_EQ(*ms_low, *standart_low);
  EXPECT_EQ(*ms_up, *standart_up);

  ++ms_low;
  ++standart_low;
  EXPECT_EQ(*ms_low, *standart_low);
  ++ms_low;
  ++standart_low;
  EXPECT_EQ(*ms_low, *standart_low);
  ++ms_low;
  ++standart_low;
  EXPECT_EQ(*ms_low, *standart_low);
  --ms_up;
  --standart_up;
  EXPECT_EQ(*ms_up, *standart_up);
  --ms_up;
  --standart_up;
  EXPECT_EQ(*ms_up, *standart_up);
  --ms_up;
  --standart_up;
  EXPECT_EQ(*ms_up, *standart_up);
  --ms_up;
  --standart_up;
  EXPECT_EQ(*ms_up, *standart_up);
}

TEST(MultisetTest, LowerBoundTest) {
  s21::Multiset<int> ms{2, 4, 4, 6, 8, 10};
  s21::Multiset<int>::iterator it = ms.lower_bound(4);
  EXPECT_EQ(*it, 4);

  // non-existing element
  it = ms.lower_bound(5);
  EXPECT_EQ(*it, 6);

  // smaller than all others
  it = ms.lower_bound(1);
  EXPECT_EQ(*it, 2);

  // larger than all others
  it = ms.lower_bound(11);
  EXPECT_EQ(it, ms.end());

  // equal to the largest element
  it = ms.lower_bound(10);
  EXPECT_EQ(*it, 10);
}

TEST(MultisetTest, UpperBoundTest) {
  s21::Multiset<int> ms;
  ms.insert(1);
  ms.insert(3);
  ms.insert(3);
  ms.insert(5);
  ms.insert(5);
  ms.insert(5);

  auto it1 = ms.upper_bound(1);
  EXPECT_EQ(*it1, 3);

  auto it2 = ms.upper_bound(2);
  EXPECT_EQ(*it2, 3);

  auto it3 = ms.upper_bound(5);
  EXPECT_EQ(it3, ms.end());
}

TEST(MultisetTest, EqualRangeTest) {
  s21::Multiset<int> ms;

  ms.insert(1);
  ms.insert(3);
  ms.insert(0);
  ms.insert(5);
  ms.insert(0);
  ms.insert(0);

  auto iter = ms.equal_range(0);

  int count = 0;
  while (*iter.first == 0) {
    ++count;
    ++iter.first;
  }
  EXPECT_EQ(count, 3);

  EXPECT_EQ(*iter.second, 1);
  --iter.second;
  EXPECT_EQ(*iter.second, 0);
}

TEST(MultisetTest, EqualRangeDistance) {
  // empty multiset
  s21::Multiset<int> mset_empty;
  auto range_empty = mset_empty.equal_range(21);
  ASSERT_EQ(range_empty.first, range_empty.second);

  s21::Multiset<int> mset{1, 1, 2, 3, 3, 3, 3, 3, 4, 5, 5};
  auto range = mset.equal_range(3);

  ASSERT_EQ(*range.first, 3);
  ASSERT_EQ(*range.second, 4);

  // distance between iterators
  int count = 0;
  for (auto iter = range.first; iter != range.second; ++iter) {
    ASSERT_EQ(*iter, 3);
    ++count;
  }
  ASSERT_EQ(count, 5);

  // key not present in multiset
  auto range_not_found = mset.equal_range(21);
  ASSERT_EQ(range_not_found.first, range_not_found.second);
}

TEST(MultisetTest, Emplace0) {
  s21::Multiset<int> ms;
  auto result1 = ms.emplace(1);
  ASSERT_EQ((int)result1.size(), 1);
  ASSERT_EQ(result1[0].second, true);
  ASSERT_EQ(*result1[0].first, 1);

  auto result2 = ms.emplace(2, 3, 4);
  ASSERT_EQ((int)result2.size(), 3);
  ASSERT_EQ(result2[0].second, true);
  ASSERT_EQ(*result2[0].first, 2);
  ASSERT_EQ(result2[1].second, true);
  ASSERT_EQ(*result2[1].first, 3);
  ASSERT_EQ(result2[2].second, true);
  ASSERT_EQ(*result2[2].first, 4);

  auto result3 = ms.emplace(1, 5, 6);
  ASSERT_EQ((int)result3.size(), 3);
  ASSERT_EQ(result3[0].second, true);
  ASSERT_EQ(*result3[0].first, 1);
  ASSERT_EQ(result3[1].second, true);
  ASSERT_EQ(*result3[1].first, 5);
  ASSERT_EQ(result3[2].second, true);
  ASSERT_EQ(*result3[2].first, 6);
}

TEST(MultisetTest, Emplace1) {
  s21::Multiset<int> ms;
  auto res1 = ms.emplace(5);
  EXPECT_EQ((int)res1.size(), 1);
  EXPECT_EQ(res1[0].first, ms.begin());
  EXPECT_EQ(res1[0].second, true);

  auto res2 = ms.emplace(3, 3);
  EXPECT_EQ((int)res2.size(), 2);
  EXPECT_EQ(res2[0].first, ms.begin());
  EXPECT_EQ(res2[0].second, true);

  auto res3 = ms.emplace(8);
  EXPECT_EQ((int)res3.size(), 1);
  EXPECT_EQ(*res3[0].first, 8);
  EXPECT_EQ(res3[0].second, true);

  auto res4 = ms.emplace(3);
  EXPECT_EQ((int)res4.size(), 1);
  EXPECT_EQ(res4[0].first, ++ms.begin());
  EXPECT_EQ(res4[0].second, true);

  auto res5 = ms.emplace();
  EXPECT_EQ((int)res5.size(), 0);

  auto res6 = ms.emplace(5);
  EXPECT_EQ((int)res6.size(), 1);
  EXPECT_EQ(res6[0].first, ms.find(5));
  EXPECT_EQ(res6[0].second, true);

  auto res7 = ms.emplace(1);
  EXPECT_EQ((int)res7.size(), 1);
  EXPECT_EQ(res7[0].first, ms.begin());
  EXPECT_EQ(res7[0].second, true);
}

TEST(MultisetTest, Emplace2) {
  s21::Multiset<int> set;
  auto res4 = set.emplace(std::initializer_list<int>{4, 5, 6});
  EXPECT_TRUE(res4[0].second);
  EXPECT_EQ(*res4[0].first, 4);
  EXPECT_TRUE(res4[1].second);
  EXPECT_EQ(*res4[1].first, 5);
  EXPECT_TRUE(res4[2].second);
  EXPECT_EQ(*res4[2].first, 6);
}

TEST(Set, DefaultConstructor) {
  s21::Set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(Set, InitializerListConstructor) {
  s21::Set<int> s{1, 2, 3};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(Set, CopyConstructor) {
  s21::Set<int> s1{1, 2, 3};
  s21::Set<int> s2(s1);
  EXPECT_FALSE(s2.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(Set, CopyAssignmentOperator) {
  s21::Set<int> s1{1, 2, 3};
  s21::Set<int> s2;
  s2 = s1;
  EXPECT_FALSE(s2.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(Set, MoveConstructor) {
  s21::Set<int> s1{1, 2, 3};
  s21::Set<int> s2(std::move(s1));
  EXPECT_FALSE(s2.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(Set, MoveAssignmentOperator) {
  s21::Set<int> s1{1, 2, 3};
  s21::Set<int> s2;
  s2 = std::move(s1);
  EXPECT_FALSE(s2.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(Set, Erase) {
  s21::Set<int> s{1, 2, 3};
  s.erase(2);
  EXPECT_EQ(s.size(), 2);
  EXPECT_TRUE(s.contains(1));
  EXPECT_FALSE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(Set, Clear) {
  s21::Set<int> s{1, 2, 3};
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(Set, MaxSizeTest) {
  s21::Set<int> set;
  std::vector<int> vec;
  EXPECT_LT(set.max_size(), vec.max_size());
}

TEST(Set, InsertTest) {
  s21::Set<int> s;

  auto [it, success] = s.insert(21);
  EXPECT_TRUE(success);
  EXPECT_EQ(*it, 21);

  // Insert an existing element into the set
  auto [it2, success2] = s.insert(21);
  EXPECT_FALSE(success2);
  EXPECT_EQ(*it2, 21);
}

TEST(Set, InsertStringTest) {
  s21::Set<std::string> s;

  auto [it1, success1] = s.insert("hello");
  auto [it2, success2] = s.insert("world");
  auto [it3, success3] = s.insert("foo");
  auto [it4, success4] = s.insert("bar");

  EXPECT_TRUE(success1);
  EXPECT_EQ(it1->key, "hello");
  EXPECT_TRUE(success2);
  EXPECT_EQ(it2->key, "world");
  EXPECT_TRUE(success3);
  EXPECT_EQ(it3->key, "foo");
  EXPECT_TRUE(success4);
  EXPECT_EQ(it4->key, "bar");

  // Try to insert an element that already exists in the set
  auto [it5, success5] = s.insert("foo");

  // insertion failed and returned an iterator to the existing
  // element
  EXPECT_FALSE(success5);
  EXPECT_EQ(it5->key, "foo");

  // Try to insert a new element
  auto [it6, success6] = s.insert("set");

  EXPECT_TRUE(s.contains("set"));
  EXPECT_TRUE(success6);
  EXPECT_EQ(s.size(), 5);
}

TEST(Set, InsertDuplicates) {
  s21::Set<int> set;

  auto [it1, inserted1] = set.insert(10);
  auto [it2, inserted2] = set.insert(20);
  auto [it3, inserted3] = set.insert(30);
  auto [it4, inserted4] = set.insert(20);  // should not be inserted

  EXPECT_EQ(3, set.size());
  EXPECT_TRUE(inserted1);
  EXPECT_TRUE(inserted2);
  EXPECT_TRUE(inserted3);
  EXPECT_FALSE(inserted4);

  EXPECT_EQ(10, it1->key);
  EXPECT_EQ(20, it2->key);
  EXPECT_EQ(30, it3->key);
}

TEST(Set, MergeTest) {
  s21::Set<int> s1{1, 2, 3};
  s21::Set<int> s2{4, 5, 6};

  s1.merge(s2);

  ASSERT_EQ((int)s1.size(), 6);
  ASSERT_TRUE(s1.contains(1));
  ASSERT_TRUE(s1.contains(2));
  ASSERT_TRUE(s1.contains(3));
  ASSERT_TRUE(s1.contains(4));
  ASSERT_TRUE(s1.contains(5));
  ASSERT_TRUE(s1.contains(6));
  ASSERT_EQ((int)s2.size(), 0);
}

TEST(Set, MergeEmptyTest) {
  s21::Set<int> s1{1, 2, 3};
  s21::Set<int> s2 = {};

  s1.merge(s2);

  ASSERT_EQ(s1.size(), 3);
  ASSERT_TRUE(s1.contains(1));
  ASSERT_TRUE(s1.contains(2));
  ASSERT_TRUE(s1.contains(3));
  ASSERT_EQ(s2.size(), 0);
}

TEST(Set, MergeSameTest) {
  s21::Set<int> s1{1, 2, 3};

  s1.merge(s1);

  ASSERT_EQ(s1.size(), 3);
  ASSERT_TRUE(s1.contains(1));
  ASSERT_TRUE(s1.contains(2));
  ASSERT_TRUE(s1.contains(3));
}

TEST(Set, MergeDuplicates) {
  s21::Set<int> set1;
  set1.insert(1);
  set1.insert(2);
  set1.insert(3);

  s21::Set<int> set2;
  set2.insert(2);
  set2.insert(3);
  set2.insert(4);

  set1.merge(set2);

  ASSERT_EQ(set1.size(), 4);
  ASSERT_TRUE(set1.contains(1));
  ASSERT_TRUE(set1.contains(2));
  ASSERT_TRUE(set1.contains(3));
  ASSERT_TRUE(set1.contains(4));
  ASSERT_EQ(set2.size(), 0);
}

TEST(Set, Emplace) {
  s21::Set<int> set;
  auto res1 = set.emplace(1);
  EXPECT_TRUE(res1[0].second);
  EXPECT_EQ(*res1[0].first, 1);

  auto res3 = set.emplace(3, 4);
  EXPECT_TRUE(res3[0].second);
  EXPECT_EQ(*res3[0].first, 3);

  auto res5 = set.emplace(1);
  EXPECT_FALSE(res5[0].second);
  EXPECT_EQ(*res5[0].first, 1);
}

TEST(Set, EmplaceEmpty) {
  s21::Set<int> st = s21::Set<int>();
  auto test = st.emplace(1, 2, 3, 4, 1);

  ASSERT_EQ(st.size(), 4);
  ASSERT_EQ(st.contains(4), true);
  EXPECT_TRUE(test[0].second);
  EXPECT_FALSE(test[4].second);
  EXPECT_EQ(*test[0].first, 1);
}

TEST(Set, Emplace0) {
  s21::Set<int> st({1, 2, 8, 4, 5});
  auto test = st.emplace(1, 2, 3, 4, 5, 6, 7);

  ASSERT_EQ(st.size(), 8);
  ASSERT_EQ(st.contains(7), true);
  EXPECT_FALSE(test[1].second);
  EXPECT_TRUE(test[2].second);
  EXPECT_EQ(*test[0].first, 1);
}

TEST(Set, Emplace1) {
  s21::Set<int> set;
  auto res4 = set.emplace(std::initializer_list<int>{4, 5, 6});
  EXPECT_TRUE(res4[0].second);
  EXPECT_EQ(*res4[0].first, 4);
  EXPECT_TRUE(res4[1].second);
  EXPECT_EQ(*res4[1].first, 5);
  EXPECT_TRUE(res4[2].second);
  EXPECT_EQ(*res4[2].first, 6);
}

TEST(Set, Emplace2) {
  s21::Set<int> set;

  // Emplace an element that doesn't already exist
  auto result = set.emplace(21);
  auto it1 = result[0].first;
  auto inserted1 = result[0].second;
  EXPECT_EQ(*it1, 21);
  EXPECT_TRUE(inserted1);
  EXPECT_EQ(set.size(), 1);

  // Emplace an element that already exists
  auto res = set.emplace(21);
  auto it2 = res[0].first;
  auto inserted2 = res[0].second;
  EXPECT_EQ(*it2, 21);
  EXPECT_FALSE(inserted2);
  EXPECT_EQ(set.size(), 1);

  // Emplace multiple elements at once
  auto results = set.emplace(1, 2, 3, 4, 5);
  EXPECT_EQ((int)results.size(), 5);
  EXPECT_EQ(set.size(), 6);
}

TEST(Set, Emplace3) {
  s21::Set<int> set;
  auto result = set.emplace(21);
  ASSERT_EQ((int)result.size(), 1);
  ASSERT_EQ(result[0].first, set.find(21));
  ASSERT_TRUE(result[0].second);

  result = set.emplace(22);
  ASSERT_EQ((int)result.size(), 1);
  ASSERT_EQ(result[0].first, set.find(22));
  ASSERT_TRUE(result[0].second);

  result = set.emplace(27, 2);
  ASSERT_EQ((int)result.size(), 2);
  ASSERT_EQ(result[0].first, set.find(27));
  ASSERT_TRUE(result[0].second);
  ASSERT_EQ(*result[0].first, 27);

  result = set.emplace();
  ASSERT_EQ(result.size(), 0);

  result = set.emplace(1);
  EXPECT_EQ((int)result.size(), 1);
  EXPECT_EQ(result[0].first, set.begin());
  EXPECT_EQ(result[0].second, true);
}
