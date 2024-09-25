#include <gtest/gtest.h>

#include <queue>

#include "../containers.h"

TEST(Member_functions_queue, member_functions) {
  s21::queue<int> a;
  ASSERT_EQ(a.size(), 0);

  s21::queue<int> b({1, 2});
  ASSERT_TRUE(b.front() == 1 && b.back() == 2);

  s21::queue<int> c(b);
  ASSERT_TRUE(b.front() == c.front() && b.back() == c.back());

  s21::queue<int> d((s21::queue<int> &&) c);
  ASSERT_TRUE(c.size() == 0 && d.front() == b.front() && d.back() == b.back());

  s21::queue<int> f;
  f = (s21::queue<int> &&) d;
  ASSERT_TRUE(b.front() == f.front() && b.back() == f.back());
}

TEST(Element_access_queue, front) {
  s21::queue<int> a({1, 2, 3});
  ASSERT_EQ(a.front(), 1);
}

TEST(Element_access_queue, back) {
  s21::queue<int> a({1, 2, 3});
  ASSERT_EQ(a.back(), 3);
}

TEST(Capacity_queue, empty) {
  s21::queue<int> a({1, 2, 3});
  ASSERT_FALSE(a.empty());

  s21::queue<int> b;
  ASSERT_TRUE(b.empty());
}

TEST(Capacity_queue, size) {
  s21::queue<int> a({1, 2, 3});
  ASSERT_EQ(a.size(), 3);

  s21::queue<int> b;
  ASSERT_EQ(b.size(), 0);
}

TEST(Modifiers_queue, push) {
  s21::queue<int> a({1, 2, 3});
  a.push(4);
  ASSERT_EQ(a.back(), 4);

  s21::queue<int> b;
  b.push(0);
  ASSERT_EQ(b.back(), 0);
}

TEST(Modifiers_queue, pop) {
  s21::queue<int> a({1, 2, 3});
  a.pop();
  ASSERT_EQ(a.front(), 2);
}

TEST(Modifiers_queue, swap) {
  s21::queue<int> a({1, 2});
  s21::queue<int> b({3, 4});
  a.swap(b);
  ASSERT_TRUE(a.front() == 3 && a.back() == 4 && b.front() == 1 &&
              b.back() == 2);

  s21::queue<int> c;
  c.swap(b);
  ASSERT_TRUE(b.size() == 0 && c.front() == 1 && c.back() == 2);
}

TEST(Emplace_queue, emplace_back) {
  s21::queue<int> a({1, 2});
  a.emplace_back(3);
  ASSERT_EQ(a.back(), 3);

  s21::queue<int> b;
  b.emplace_back(1);
  ASSERT_EQ(b.back(), 1);
}

// ***** QUEUE *****
TEST(tests_queue, default_constructor) {
  // arrange and act
  s21::queue<int> aboba;
  std::queue<int> buba;

  // assert
  ASSERT_EQ(aboba.size(), buba.size());
  ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_queue, initializer_constructor) {
  // arrange and act
  s21::queue<int> aboba{1, 2, 3, 4};
  std::queue<int> buba({1, 2, 3, 4});

  // assert
  ASSERT_EQ(aboba.front(), buba.front());
  ASSERT_EQ(aboba.back(), buba.back());

  ASSERT_EQ(aboba.size(), buba.size());
  ASSERT_TRUE(!aboba.empty());
}

TEST(tests_queue, copy_constructor) {
  // arrange and act
  s21::queue<int> aboba{1, 2, 3, 4};
  s21::queue<int> aboba_copy(aboba);
  std::queue<int> buba({1, 2, 3, 4});
  std::queue<int> buba_copy(buba);

  // assert
  ASSERT_EQ(aboba_copy.front(), buba_copy.front());
  ASSERT_EQ(aboba_copy.back(), buba_copy.back());

  ASSERT_EQ(aboba.front(), buba.front());
  ASSERT_EQ(aboba.back(), buba.back());

  ASSERT_EQ(aboba_copy.size(), buba_copy.size());
  ASSERT_EQ(aboba.size(), buba.size());

  ASSERT_EQ(aboba.empty(), buba.empty());
  ASSERT_EQ(aboba_copy.empty(), buba_copy.empty());
}

TEST(tests_queue, move_constructor) {
  // arrange
  s21::queue<int> aboba{1, 2, 3, 4, 5, 6};
  std::queue<int> buba({1, 2, 3, 4, 5, 6});

  // act
  s21::queue<int> aboba_move(std::move(aboba));
  std::queue<int> buba_move(std::move(buba));

  // assert
  ASSERT_EQ(aboba_move.front(), buba_move.front());
  ASSERT_EQ(aboba_move.back(), buba_move.back());

  ASSERT_EQ(aboba_move.size(), buba_move.size());
  ASSERT_EQ(aboba.size(), buba.size());

  ASSERT_EQ(aboba.empty(), buba.empty());
  ASSERT_EQ(aboba_move.empty(), buba_move.empty());
}

TEST(tests_queue, assignment_operator) {
  // arrange
  s21::queue<int> aboba{1, 2, 3, 4, 5, 6};
  std::queue<int> buba({1, 2, 3, 4, 5, 6});

  // act
  // s21::queue<int> aboba_move = std::move(aboba);
  s21::queue<int> aboba_move;
  aboba_move = std::move(aboba);
  std::queue<int> buba_move = std::move(buba);

  // assert
  ASSERT_EQ(aboba_move.front(), buba_move.front());
  ASSERT_EQ(aboba_move.back(), buba_move.back());

  ASSERT_EQ(aboba_move.size(), buba_move.size());
  ASSERT_EQ(aboba.size(), buba.size());

  ASSERT_EQ(aboba.empty(), buba.empty());
  ASSERT_EQ(aboba_move.empty(), buba_move.empty());
}

TEST(tests_queue, front_back) {
  // arrange
  s21::queue<int> aboba;
  std::queue<int> buba;
  auto a = 1;
  auto b = 2;
  auto c = 3;
  auto d = 4;

  // act
  aboba.push(a);
  aboba.push(b);
  aboba.push(c);
  aboba.push(d);
  buba.push(a);
  buba.push(b);
  buba.push(c);
  buba.push(d);

  // assert
  ASSERT_EQ(aboba.front(), buba.front());
  ASSERT_EQ(aboba.back(), buba.back());
  ASSERT_EQ(aboba.size(), buba.size());
  ASSERT_TRUE(!aboba.empty());
}

TEST(tests_queue, empty) {
  // arrange
  s21::queue<int> aboba{1, 2, 3, 4, 5, 6};
  std::queue<int> buba({1, 2, 3, 4, 5, 6});
  s21::queue<int> aboba_2;
  std::queue<int> buba_2;

  // act

  // assert
  ASSERT_EQ(aboba.empty(), buba.empty());
  ASSERT_EQ(aboba_2.empty(), buba_2.empty());
}

TEST(tests_queue, size) {
  // arrange
  s21::queue<int> aboba{1, 2, 3, 4, 5, 6};
  std::queue<int> buba({1, 2, 3, 4, 5, 6});
  s21::queue<int> aboba_2;
  std::queue<int> buba_2;

  // act

  // assert
  ASSERT_EQ(aboba.size(), buba.size());
  ASSERT_EQ(aboba_2.size(), buba_2.size());
}

TEST(tests_queue, pop) {
  // arrange
  s21::queue<int> aboba;
  std::queue<int> buba;
  auto a = 1;
  auto b = 2;
  auto c = 3;
  auto d = 4;

  // act
  aboba.push(a);
  aboba.push(b);
  aboba.push(c);
  aboba.push(d);
  buba.push(a);
  buba.push(b);
  buba.push(c);
  buba.push(d);
  aboba.pop();
  buba.pop();

  // assert
  ASSERT_EQ(aboba.front(), buba.front());
  ASSERT_EQ(aboba.back(), buba.back());
  ASSERT_EQ(aboba.size(), buba.size());
  ASSERT_TRUE(!aboba.empty());
}

TEST(tests_queue, push) {
  // arrange
  s21::queue<int> aboba;
  auto a = 1;
  auto b = 2;
  auto c = 3;
  auto d = 4;

  // act
  aboba.push(a);
  aboba.push(b);
  aboba.push(c);
  aboba.push(d);

  // assert
  ASSERT_EQ(aboba.front(), a);
  ASSERT_EQ(aboba.back(), d);

  ASSERT_EQ(aboba.size(), d);
  ASSERT_TRUE(!aboba.empty());
}

TEST(tests_queue, swap) {
  // arrange
  s21::queue<int> aboba{1, 2, 3, 4, 5, 6};
  s21::queue<int> aboba_swap{5, 6, 7};
  std::queue<int> buba({1, 2, 3, 4, 5, 6});
  std::queue<int> buba_swap({5, 6, 7});

  // act
  aboba.swap(aboba_swap);
  buba.swap(buba_swap);

  // assert
  ASSERT_EQ(aboba_swap.front(), buba_swap.front());
  ASSERT_EQ(aboba_swap.back(), buba_swap.back());

  ASSERT_EQ(aboba.front(), buba.front());
  ASSERT_EQ(aboba.back(), buba.back());

  ASSERT_EQ(aboba_swap.size(), buba_swap.size());
  ASSERT_EQ(aboba.size(), buba.size());

  ASSERT_EQ(aboba.empty(), buba.empty());
  ASSERT_EQ(aboba_swap.empty(), buba_swap.empty());
}

TEST(tests_queue_bonus_suit, emplace_back) {
  // arrange
  s21::queue<int> aboba{1, 2, 3, 4, 5, 6};
  std::queue<int> buba({1, 2, 3, 4, 5, 6, 5, 9, 11, 7});

  // act
  aboba.emplace_back(5, 9, 11, 7);

  // assert
  ASSERT_EQ(aboba.front(), buba.front());
  ASSERT_EQ(aboba.back(), buba.back());
  ASSERT_EQ(aboba.size(), buba.size());
}

TEST(queue, queue_1) {
  s21::queue<int> queue{};
  ASSERT_TRUE(queue.empty());
}

TEST(queue, queue_2) {
  s21::queue<int> queue{};
  queue.push(45);
  ASSERT_EQ(queue.size(), 1);
  ASSERT_EQ(queue.front(), 45);
  ASSERT_EQ(queue.back(), 45);
}

TEST(queue, queue_3) {
  s21::queue<int> queue{1, 2, 3};
  std::queue<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  while (!queue.empty()) {
    ASSERT_EQ(queue.front(), original.front());
    ASSERT_EQ(queue.back(), original.back());
    queue.pop();
    original.pop();
  }
}

TEST(queue, queue_4) {
  s21::queue<int> queue{55, 44, 33};
  ASSERT_EQ(queue.size(), 3);
  ASSERT_EQ(queue.front(), 55);
  ASSERT_EQ(queue.back(), 33);
  queue.pop();
  ASSERT_EQ(queue.size(), 2);
  ASSERT_EQ(queue.front(), 44);
  ASSERT_EQ(queue.back(), 33);
  queue.pop();
  ASSERT_EQ(queue.size(), 1);
  ASSERT_EQ(queue.front(), 33);
  ASSERT_EQ(queue.back(), 33);
  queue.pop();
  ASSERT_EQ(queue.size(), 0);
  ASSERT_TRUE(queue.empty());
}

TEST(queue, queue_5) {
  s21::queue<int> queue1{1, 2, 3};
  s21::queue<int> queue2{4, 5, 6, 7};
  queue1.swap(queue2);
  ASSERT_EQ(queue1.size(), 4);
  ASSERT_EQ(queue1.back(), 7);
  ASSERT_EQ(queue1.front(), 4);
  queue1.pop();
  ASSERT_EQ(queue1.size(), 3);
  ASSERT_EQ(queue1.front(), 5);
  ASSERT_EQ(queue1.back(), 7);
  ASSERT_EQ(queue2.size(), 3);
  ASSERT_EQ(queue2.front(), 1);
  ASSERT_EQ(queue2.back(), 3);
  queue2.pop();
  ASSERT_EQ(queue2.size(), 2);
  ASSERT_EQ(queue2.front(), 2);
  ASSERT_EQ(queue2.back(), 3);
  queue2.pop();
  ASSERT_EQ(queue2.size(), 1);
  ASSERT_EQ(queue2.front(), 3);
  ASSERT_EQ(queue2.back(), 3);
  queue2.pop();
  ASSERT_TRUE(queue2.empty());
}

TEST(queue, queue_6) {
  s21::queue<int> queue1{1, 2, 3};
  s21::queue<int> queue2(std::move(queue1));
  ASSERT_TRUE(queue1.empty());
  ASSERT_EQ(queue2.back(), 3);
}

TEST(queue, queue_7) {
  s21::queue<int> queue1{1, 2, 3};
  s21::queue<int> queue2{};
  queue2 = std::move(queue1);
  ASSERT_TRUE(queue1.empty());
  ASSERT_EQ(queue2.back(), 3);
}

TEST(queue, queue_8) {
  s21::queue<std::string> queue{"a", "b", "c"};
  ASSERT_EQ(queue.size(), 3);
  ASSERT_EQ(queue.front(), "a");
  queue.pop();
  ASSERT_EQ(queue.front(), "b");
  queue.pop();
  ASSERT_EQ(queue.front(), "c");
  queue.pop();
  ASSERT_TRUE(queue.empty());
}

TEST(queue, queue_9) {
  s21::queue<double> queue1{67, 56, 45};
  s21::queue<double> queue2(queue1);
  queue2.swap(queue1);
  ASSERT_EQ(queue1.size(), queue2.size());
  ASSERT_EQ(queue2.front(), 67);
  queue2.pop();
  ASSERT_EQ(queue2.front(), 56);
  queue2.pop();
  ASSERT_EQ(queue2.front(), 45);
  queue2.pop();
}

TEST(queue, test_emplace_back) {
  s21::queue<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  test.emplace_back(3.0, 42.0, 5.0);
  s21::queue<double> check{3.0, 42.0, 5.0, 1.11, 2.22, 3.33, 4.44, 5.55};
  check.emplace_back(3.0, 42.0, 5.0);
  ASSERT_EQ(test.back(), check.back());
}
