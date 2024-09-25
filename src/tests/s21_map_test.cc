#include "../containers.h"
#include "gtest/gtest.h"

TEST(MapTest, DefaultConstructor) {
  s21::Map<int, std::string> map;
  EXPECT_EQ(map.size(), 0);
}

TEST(MapTest, InitializerConstructor) {
  s21::Map<int, double> my_map{
      {-100, 12.01},
      {1, 98765.123},
      {2, 123456789.1},
      {2, 77.77},
  };
  std::map<int, double> standart{
      {-100, 12.01},
      {1, 98765.123},
      {2, 123456789.1},
      {2, 77.77},
  };
  EXPECT_EQ(standart.size(), my_map.size());
  EXPECT_EQ(my_map.size(), 3);
}

TEST(MapTest, InsertDuplicate) {
  s21::Map<int, std::string> my_map{{1, "one"}, {2, "two"}};
  auto result = my_map.insert({1, "new_one"});
  EXPECT_FALSE(result.second);
}

TEST(MapTest, InsertKeyValuePair) {
  s21::Map<int, std::string> map;
  EXPECT_TRUE(map.empty());
  auto result = map.insert(1, "one");
  EXPECT_TRUE(result.second);

  EXPECT_EQ(map.size(), 1);
  EXPECT_FALSE(map.empty());

  result = map.insert(1, "one");
  EXPECT_FALSE(result.second);
  EXPECT_EQ(map.size(), 1);

  auto it = map.find(1);
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->key, 1);
  EXPECT_EQ(it->value, "one");

  result = map.insert(2, "two");
  EXPECT_TRUE(result.second);
  EXPECT_EQ(map.size(), 2);

  it = map.find(2);
  EXPECT_NE(it, map.end());
  EXPECT_EQ(it->key, 2);
  EXPECT_EQ(it->value, "two");
}

TEST(MapTest, CopyConstructor0) {
  s21::Map<int, int> original_map;
  original_map.insert(std::make_pair(1, 100));
  original_map.insert(2, 200);
  original_map.insert(std::make_pair(3, 300));

  s21::Map<int, int> copied_map(original_map);

  EXPECT_EQ(copied_map.size(), original_map.size());

  for (auto it = original_map.begin(); it != original_map.end(); ++it) {
    EXPECT_EQ(copied_map.at(it->key), it->value);
  }
}

TEST(MapTest, CopyConstructor1) {
  s21::Map<int, std::string> map1;
  map1.insert(1, "one");
  map1.insert(2, "two");
  map1.insert(3, "three");

  s21::Map<int, std::string> copied(map1);

  EXPECT_EQ(map1.size(), copied.size());

  for (auto it1 = map1.begin(), it2 = copied.begin();
       it1 != map1.end() && it2 != copied.end(); ++it1, ++it2) {
    EXPECT_EQ(it1->key, it2->key);
    EXPECT_EQ(it1->value, it2->value);
  }
}

TEST(MapTest, CopyConstructor2) {
  s21::Map<int, std::string> map1{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::Map<int, std::string> map2(map1);
  EXPECT_EQ(map1.size(), 3);
  EXPECT_EQ(map2.size(), 3);
  EXPECT_EQ(map1[1], "one");
  EXPECT_EQ(map1[2], "two");
  EXPECT_EQ(map1[3], "three");
  EXPECT_EQ(map2[1], "one");
  EXPECT_EQ(map2[2], "two");
  EXPECT_EQ(map2[3], "three");
}

TEST(MapTest, MoveConstructor) {
  s21::Map<int, std::string> map1{{1, "one"}, {2, "two"}};
  EXPECT_EQ(map1.size(), 2);
  s21::Map<int, std::string> map2(std::move(map1));
  EXPECT_EQ(map1.size(), 0);
  EXPECT_EQ(map2.size(), 2);
  EXPECT_EQ(map2.at(1), "one");
  EXPECT_EQ(map2.at(2), "two");
  EXPECT_THROW(map2.at(3), std::out_of_range);
}

TEST(MapTest, MoveAssignmentOperator) {
  s21::Map<int, std::string> map1{{1, "one"}, {2, "two"}};
  s21::Map<int, std::string> map2{{3, "three"}, {4, "four"}};

  map1 = std::move(map2);

  EXPECT_EQ(map1.size(), 2);
  EXPECT_EQ(map1[3], "three");
  EXPECT_EQ(map1[4], "four");

  EXPECT_EQ(map2.size(), 0);
}

TEST(MapTest, BeginAndEnd) {
  s21::Map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};

  auto it = map.begin();
  ASSERT_NE(it, map.end());
  EXPECT_EQ((*it).key, 1);
  EXPECT_EQ((*it).value, "one");

  it = map.end();
  ASSERT_EQ(it, nullptr);
  ASSERT_THROW(++it, std::out_of_range);
}

TEST(MapTest, EraseCase4) {
  s21::Map<int, std::string> my_map;
  my_map.insert(5, "five");
  my_map.insert(3, "three");
  my_map.insert(7, "seven");
  my_map.insert(2, "two");
  my_map.insert(4, "four");
  my_map.insert(6, "six");
  my_map.insert(8, "eight");
  my_map.insert(1, "one");
  my_map.insert(9, "nine");

  auto it = my_map.find(3);
  my_map.erase(it);
  it = my_map.find(7);
  my_map.erase(it);
  EXPECT_EQ(my_map.size(), 7);
}

TEST(MapTest, EraseOppositeCase2And4) {
  s21::Map<int, int> my_map;
  my_map.insert(5, 5);
  my_map.insert(3, 3);
  my_map.insert(6, 6);
  my_map.insert(2, 2);
  my_map.insert(4, 4);
  my_map.insert(7, 7);
  my_map.insert(1, 1);

  auto it = my_map.begin();
  while (it != my_map.end() && it->key != 5) {
    ++it;
  }
  my_map.erase(it);
  EXPECT_EQ(my_map.size(), 6);
  EXPECT_FALSE(my_map.contains(5));
}

TEST(MapTest, EraseFixRightCases1) {
  s21::Map<int, int> my_map;
  my_map.insert(1, 10);
  my_map.insert(2, 5);
  my_map.insert(3, 15);
  my_map.insert(4, 3);
  my_map.insert(5, 7);
  my_map.insert(6, 12);
  auto erased_key = my_map.begin();
  my_map.erase(erased_key);

  EXPECT_FALSE(my_map.contains(1));
}

TEST(MapTest, NodeParentRight) {
  s21::Map<int, int> map;
  map.insert(1, 1);
  map.insert(2, 2);
  map.insert(3, 3);
  map.insert(4, 4);

  auto erased_key = map.begin();
  while (erased_key != map.end() && erased_key->key != 3) {
    ++erased_key;
  }
  map.erase(erased_key);
}

TEST(MapTest, EraseFixLeftCase1) {
  s21::Map<int, int> my_map;
  my_map.insert(50, 10);
  my_map.insert(20, 5);
  my_map.insert(65, 15);
  my_map.insert(15, 3);
  my_map.insert(35, 7);
  my_map.insert(55, 12);
  my_map.insert(70, 18);
  my_map.insert(68, 1);
  my_map.insert(80, 4);
  my_map.insert(90, 6);
  my_map.insert(9, 9);
  my_map.insert(11, 11);
  my_map.insert(14, 14);
  my_map.insert(17, 17);
  my_map.insert(20, 20);
  my_map.insert(2, 2);
  my_map.insert(8, 8);
  my_map.insert(13, 13);
  my_map.insert(16, 16);
  my_map.insert(19, 19);

  auto erased_key = my_map.find(15);
  my_map.erase(erased_key);
  erased_key = my_map.find(20);
  my_map.erase(erased_key);
  erased_key = my_map.find(90);
  my_map.erase(erased_key);
  erased_key = my_map.find(80);
  my_map.erase(erased_key);
  erased_key = my_map.find(50);
  my_map.erase(erased_key);
  erased_key = my_map.find(35);
  my_map.erase(erased_key);

  EXPECT_FALSE(my_map.contains(15));
}

TEST(MapTest, Case3LeftOppossite) {
  s21::Map<int, int> my_map;
  my_map.insert(10, 10);
  my_map.insert(5, 5);
  my_map.insert(15, 15);
  my_map.insert(3, 3);
  my_map.insert(7, 7);
  my_map.insert(12, 12);
  my_map.insert(18, 18);
  my_map.insert(1, 1);
  my_map.insert(4, 4);
  my_map.insert(6, 6);
  my_map.insert(9, 9);
  my_map.insert(11, 11);
  my_map.insert(14, 14);
  my_map.insert(17, 17);
  my_map.insert(20, 20);
  my_map.insert(2, 2);
  my_map.insert(8, 8);
  my_map.insert(13, 13);
  my_map.insert(16, 16);
  my_map.insert(19, 19);
  auto erased_key = my_map.begin();
  while (erased_key != my_map.end() && erased_key->key != 5) {
    ++erased_key;
  }
  my_map.erase(erased_key);

  EXPECT_FALSE(my_map.contains(5));
}

TEST(MapTest, FixUpCase3Right) {
  s21::Map<int, int> my_map;
  my_map.insert(10, 10);
  my_map.insert(5, 5);
  my_map.insert(30, 30);
  my_map.insert(2, 2);
  my_map.insert(9, 9);
  my_map.insert(25, 25);
  my_map.insert(40, 40);
  my_map.insert(38, 38);

  auto erased_key = my_map.begin();
  while (erased_key != my_map.end() && erased_key->key != 30) {
    ++erased_key;
  }
  my_map.erase(erased_key);

  EXPECT_FALSE(my_map.contains(30));
}

TEST(MapTest, AtMethod) {
  s21::Map<std::string, int> map;
  map.insert({"apple", 3});
  map.insert({"banana", 5});

  EXPECT_EQ(map.at("apple"), 3);
  EXPECT_EQ(map.at("banana"), 5);
  EXPECT_THROW(map.at("orange"), std::out_of_range);
}

TEST(MapTest, AtInitialized) {
  s21::Map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map.at(2), "two");
  EXPECT_EQ(map.at(3), "three");
  EXPECT_NE(map.at(3), "thre");
}

TEST(MapTest, AtCount) {
  s21::Map<int, std::string> map{{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_THROW(map.at(4), std::out_of_range);
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map.count(1), 1);
  EXPECT_EQ(map.count(2), 1);
  EXPECT_EQ(map.count(3), 1);
  EXPECT_EQ(map.count(4), 0);

  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map.at(2), "two");
  EXPECT_EQ(map.at(3), "three");
}

TEST(MapTest, OperatorBracket) {
  s21::Map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});

  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");

  //  non-existent key.
  EXPECT_EQ(map[4], "");
  EXPECT_EQ(map.size(), 4);

  // modifying an existing value.
  map[1] = "new_one";
  EXPECT_EQ(map[1], "new_one");

  // adding a new key-value pair.
  map[4] = "four";
  EXPECT_EQ(map[4], "four");
  EXPECT_EQ(map.size(), 4);
}

TEST(MapTest, BracketAccessExistingKey) {
  s21::Map<std::string, int> my_map{{"foo", 42}, {"bar", 43}};

  EXPECT_EQ(my_map["foo"], 42);
  EXPECT_EQ(my_map["bar"], 43);
}

TEST(MapTest, AccessNewKey) {
  s21::Map<std::string, int> my_map{{"foo", 42}, {"bar", 43}};

  EXPECT_EQ(my_map.size(), 2);

  int &value = my_map["baz"];

  EXPECT_EQ(my_map.size(), 3);
  EXPECT_EQ(value, 0);
  EXPECT_EQ(my_map["baz"], 0);

  value = 44;

  EXPECT_EQ(my_map["baz"], 44);
}

TEST(MapTest, GetAllocator) {
  s21::Map<int, int> my_map;
  std::allocator<std::pair<const int, int>> alloc = my_map.get_allocator();

  // allocator is not null
  EXPECT_NE(nullptr, &alloc);

  // allocator can allocate memory for a pair
  std::pair<const int, int> *pair_ptr = alloc.allocate(1);
  EXPECT_NE(nullptr, pair_ptr);

  // deallocate the memory
  alloc.destroy(pair_ptr);
  alloc.deallocate(pair_ptr, 1);

  pair_ptr = nullptr;
  EXPECT_EQ(nullptr, pair_ptr);
}

TEST(MapTest, MaxSizeTest0) {
  s21::Map<int, int> my_map;
  EXPECT_GE(my_map.max_size(), 0);
  my_map.insert({1, 10});
  my_map.insert({2, 20});
  my_map.insert({3, 30});

  EXPECT_EQ(my_map.size(), 3);
  EXPECT_GE(my_map.max_size(), 3);
}

TEST(MapTest, MaxSizeTest1) {
  std::map<int, int> standart_int;
  s21::Map<int, int> my_map_int;
  std::map<double, double> standart_double;
  s21::Map<double, double> my_map_double;

  ASSERT_EQ(standart_int.max_size(), my_map_int.max_size());
  ASSERT_EQ(standart_double.max_size(), my_map_double.max_size());
}

TEST(MapTest, InsertOrAssign) {
  s21::Map<int, std::string> map;

  auto [it1, inserted1] = map.insert_or_assign(1, "one");
  EXPECT_EQ("one", it1->value);
  EXPECT_TRUE(inserted1);

  auto [it2, inserted2] = map.insert_or_assign(1, "ONE");
  EXPECT_EQ("ONE", it1->value);
  EXPECT_FALSE(inserted2);
}

TEST(MapTest, InsertOrAssignTest2) {
  s21::Map<int, std::string> map;
  auto [it1, inserted1] = map.insert_or_assign(1, "one");
  auto [it2, inserted2] = map.insert_or_assign(2, "two");
  auto [it3, inserted3] = map.insert_or_assign(3, "three");

  ASSERT_TRUE(inserted1);
  ASSERT_TRUE(inserted2);
  ASSERT_TRUE(inserted3);
  ASSERT_EQ(map.size(), 3);
  ASSERT_EQ(it1->key, 1);
  ASSERT_EQ(it1->value, "one");
  ASSERT_EQ(it2->key, 2);
  ASSERT_EQ(it2->value, "two");
  ASSERT_EQ(it3->key, 3);
  ASSERT_EQ(it3->value, "three");

  auto [it4, inserted4] = map.insert_or_assign(2, "new_two");
  ASSERT_FALSE(inserted4);
  ASSERT_EQ(map.size(), 3);
  ASSERT_EQ(it2, it4);
  ASSERT_EQ(it4->key, 2);
  ASSERT_EQ(it4->value, "new_two");
  ASSERT_EQ(it2->value, "new_two");
}

TEST(MapTest, InsertOrAssign3) {
  s21::Map<int, int> map{{1, 2}, {2, 7}, {3, 6}};
  ASSERT_EQ(map.size(), 3);

  auto [iter1, inserted1] = map.insert_or_assign(2, 5);
  ASSERT_FALSE(inserted1);
  ASSERT_EQ(iter1->value, 5);
  ASSERT_EQ(map.size(), 3);

  auto [iter2, inserted2] = map.insert_or_assign(4, 8);
  ASSERT_TRUE(inserted2);
  ASSERT_EQ(iter2->value, 8);
  ASSERT_EQ(map.size(), 4);

  auto [iter3, inserted3] = map.insert_or_assign(5, 10);
  ASSERT_TRUE(inserted3);
  ASSERT_EQ(iter3->value, 10);
  ASSERT_EQ(map.size(), 5);

  auto [iter4, inserted4] = map.insert_or_assign(6, 12);
  ASSERT_TRUE(inserted4);
  ASSERT_EQ(iter4->value, 12);
  ASSERT_EQ(map.size(), 6);

  ASSERT_EQ(map.at(2), 5);
  ASSERT_EQ(map.at(4), 8);
  ASSERT_EQ(map.at(5), 10);
  ASSERT_EQ(map.at(6), 12);
  ASSERT_EQ(map.at(1), 2);
  ASSERT_EQ(map.at(3), 6);
}

TEST(MapTest, InsertOrAssignReassigning) {
  s21::Map<int, int> map;
  map.insert(2, 5);
  map.insert_or_assign(2, 7);
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.at(2), 7);
}

TEST(MapTest, InsertOrAssignFind) {
  s21::Map<int, int> map;
  map.insert_or_assign(2, 7);
  auto it = map.find(2);
  EXPECT_NE(it, map.end());
  EXPECT_EQ((*it).value, 7);
  EXPECT_EQ((*it).key, 2);
}

TEST(MapTest, ContainsExistingKey) {
  s21::Map<int, int> map;
  map.insert_or_assign(2, 7);
  EXPECT_TRUE(map.contains(2));
}

TEST(MapTest, ContainsNonExistingKey) {
  s21::Map<int, int> map;
  EXPECT_FALSE(map.contains(2));
}

TEST(MapTest, FindTest) {
  s21::Map<int, int> map{{4, 44}, {3, 30}, {2, 20}};
  auto it = map.find(2);
  EXPECT_EQ(it->key, 2);
  EXPECT_EQ(it->value, 20);
}

TEST(MapTest, FindExistingKeyDifferentOrder) {
  s21::Map<std::string, int> my_map;
  my_map.insert("one", 1);
  my_map.insert("three", 3);
  my_map.insert("two", 2);

  auto it = my_map.find("one");
  EXPECT_NE(it, my_map.end());
  EXPECT_EQ(it->value, 1);

  it = my_map.find("two");
  EXPECT_NE(it, my_map.end());
  EXPECT_EQ(it->value, 2);

  auto it1 = my_map.find("three");
  EXPECT_NE(it1, my_map.end());
  EXPECT_EQ(it1->value, 3);

  it = my_map.find("four");
  EXPECT_EQ(it, my_map.end());
}

TEST(MapTest, FindInEmptyMap) {
  s21::Map<int, std::string> map;

  auto it = map.find(1);
  EXPECT_EQ(it, map.end());
}

TEST(MapTest, MergeTest) {
  s21::Map<int, int> map1{{1, 10}, {2, 20}, {3, 30}};
  s21::Map<int, int> map2{{4, 40}, {5, 50}, {6, 60}};

  map1.merge(map2);

  EXPECT_EQ(map1.size(), 6);
  EXPECT_TRUE(map1.contains(4));
  EXPECT_TRUE(map1.contains(5));
  EXPECT_TRUE(map1.contains(6));
  EXPECT_EQ(map1.at(4), 40);
  EXPECT_EQ(map1.at(5), 50);
  EXPECT_EQ(map1.at(6), 60);

  EXPECT_EQ(map2.size(), 0);
  EXPECT_TRUE(map2.empty());
}

TEST(MapTest, MergeCompareWithStdMap) {
  s21::Map<int, int> s21_map1{{1, 10}, {2, 20}, {3, 30}};
  s21::Map<int, int> s21_map2{{4, 40}, {5, 50}};
  std::map<int, int> std_map1{{1, 10}, {2, 20}, {3, 30}};
  std::map<int, int> std_map2{{4, 40}, {5, 50}};

  s21_map1.merge(s21_map2);
  std_map1.merge(std_map2);

  ASSERT_EQ(s21_map1.size(), std_map1.size());
}

TEST(MapTest, MergeAndOverwriteValues) {
  s21::Map<int, std::string> map1{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::Map<int, std::string> map2{{3, "THREE"}, {4, "four"}, {5, "five"}};

  map1.merge(map2);

  EXPECT_EQ(map1.size(), 5);
  EXPECT_EQ(map2.size(), 0);

  EXPECT_EQ(map1.at(1), "one");
  EXPECT_EQ(map1.at(2), "two");
  EXPECT_EQ(map1.at(3), "THREE");
  EXPECT_EQ(map1.at(4), "four");
  EXPECT_EQ(map1.at(5), "five");
}

TEST(MapTest, EraseTest) {
  s21::Map<int, std::string> map;
  map.insert(1, "One");
  map.insert(2, "Two");
  map.insert(3, "Three");

  auto it = map.find(1);
  EXPECT_NE(it, map.end());
  map.erase(it);
  EXPECT_EQ(map.size(), 2u);
  EXPECT_FALSE(map.contains(1));
  EXPECT_EQ(map[2], "Two");
  EXPECT_EQ(map.at(3), "Three");
  EXPECT_TRUE(map.contains(3));
  EXPECT_TRUE(map.contains(2));
}

TEST(MapTest, EraseNonExistingElement) {
  s21::Map<int, std::string> map;
  map.insert({1, "one"});
  map.insert({2, "two"});

  auto it = map.begin();
  while (it != map.end() && it->key != 3) {
    ++it;
  }

  EXPECT_THROW(map.erase(it), std::out_of_range);
  EXPECT_EQ(map.size(), 2);

  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map[2], "two");
}

TEST(MapTest, LowerUpperBounds) {
  s21::Map<int, std::string> my_map;

  my_map.insert(std::make_pair(1, "one"));
  my_map.insert(std::make_pair(2, "two"));
  my_map.insert(std::make_pair(3, "three"));
  my_map.insert(std::make_pair(4, "four"));

  EXPECT_EQ(my_map.lower_bound(0), my_map.begin());
  EXPECT_EQ(my_map.lower_bound(1)->value, "one");
  EXPECT_EQ(my_map.lower_bound(2)->value, "two");
  EXPECT_EQ(my_map.lower_bound(5), my_map.end());

  EXPECT_EQ(my_map.upper_bound(0), my_map.begin());
  EXPECT_EQ(my_map.upper_bound(1)->value, "two");
  EXPECT_EQ(my_map.upper_bound(2)->value, "three");
  EXPECT_EQ(my_map.upper_bound(5), my_map.end());
}

TEST(MapTest, EqualRange) {
  s21::Map<int, int> m{{1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50}};

  auto range = m.equal_range(3);
  ASSERT_EQ(range.first->value, 30);
  ASSERT_EQ(range.second->value, 40);

  range = m.equal_range(6);
  ASSERT_EQ(range.first, m.end());
  ASSERT_EQ(range.second, m.end());

  range = m.equal_range(1);
  ASSERT_EQ(range.first->value, 10);
  ASSERT_EQ(range.second->value, 20);

  range = m.equal_range(5);
  ASSERT_EQ(range.first->value, 50);
  ASSERT_EQ(range.second, m.end());

  range = m.equal_range(6);
  ASSERT_EQ(range.first, m.end());
  ASSERT_EQ(range.second, m.end());
}

TEST(MapTest, EqualRangeEmpty) {
  s21::Map<int, std::string> empty_map;
  auto range = empty_map.equal_range(1);
  EXPECT_EQ(range.first, empty_map.end());
  EXPECT_EQ(range.second, empty_map.end());
}

TEST(MapTest, EmplaceEmpty) {
  s21::Map<int, std::string> map;
  map.emplace();
  EXPECT_EQ(map.size(), 0);
}

TEST(MapTest, EmplaceTest) {
  s21::Map<int, int> map;

  auto result =
      map.emplace(std::pair<int, int>(1, 7), std::pair<int, int>(2, 10),
                  std::pair<int, int>(3, 8), std::pair<int, int>(4, 9),
                  std::pair<int, int>(5, 0), std::pair<int, int>(1, 8));
  ASSERT_EQ(map.size(), 5);
  ASSERT_EQ(map.contains(1), true);
  EXPECT_FALSE(result[5].second);
  EXPECT_EQ(result[1].second, true);
  EXPECT_EQ(*(result[1].first), 2);
}

TEST(MapTest, EmplaceSecond) {
  s21::Map<int, std::string> map;
  auto pair1 = std::make_pair(1, "one");
  auto pair2 = std::make_pair(2, "two");
  auto pair3 = std::make_pair(1, "uno");
  map.emplace(pair1);
  map.emplace(pair2);
  map.emplace(pair3);
  auto [it3, inserted3] = map.insert(pair3);
  EXPECT_FALSE(inserted3);

  EXPECT_EQ(map.size(), 2);

  EXPECT_EQ(pair1.second, "one");
  EXPECT_EQ(pair2.second, "two");
  EXPECT_EQ(pair2.first, 2);
}
