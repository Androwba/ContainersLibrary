#include <gtest/gtest.h>

#include <stack>

#include "../containers.h"

template <typename T>
void compare_stack(s21::stack<T>& s21_stack, std::stack<T>& std_stack) {
  ASSERT_EQ(s21_stack.size(), std_stack.size());
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
  while (!(s21_stack.empty()) && !(std_stack.empty())) {
    try {
      ASSERT_EQ(s21_stack.top(), std_stack.top());
      s21_stack.pop();
      std_stack.pop();
    } catch (const std::exception& e) {
      std::cerr << e.what() << '\n';
    }
  }
  ASSERT_EQ(s21_stack.size(), std_stack.size());
  ASSERT_EQ(s21_stack.empty(), std_stack.empty());
}

TEST(stack_create_and_remove_suit, initialazer_constructor_and_default) {
  s21::stack<int> a({1, 2, 3, 4, -9, 0});
  std::stack<int> b({1, 2, 3, 4, -9, 0});
  compare_stack(a, b);
  a.emplace_front(9, 8, 7);
  b.push(9);
  b.push(8);
  b.push(7);
  a.pop();
  b.pop();
  a.push(6);
  b.push(6);
  compare_stack(a, b);

  s21::stack<double> a1{1., 2., 3., 4., -9., 0.};
  std::stack<double> b1;
  b1.push(1.);
  b1.push(2.);
  b1.push(3.);
  b1.push(4.);
  b1.push(-9.);
  b1.push(0.);
  compare_stack(a1, b1);

  s21::stack<std::string> a2;
  std::stack<std::string> b2;
  a2.push("afag");
  b2.push("afag");
  compare_stack(a2, b2);

  a2.push("afag");
  b2.push("afag");
  a2.pop();
  b2.pop();
  compare_stack(a2, b2);
}

TEST(stack_create_and_remove_suit, emplace) {
  s21::stack<int> a({1, 2, 3, 4, -9, 0});
  std::stack<int> b({1, 2, 3, 4, -9, 0});
  a.emplace_front(9, 8, 7);
  b.push(9);
  b.push(8);
  b.push(7);
  a.pop();
  b.pop();
  a.push(6);
  b.push(6);
  compare_stack(a, b);
}

TEST(stack_create_and_remove_suit, copy_and_move_constructor_1) {
  s21::stack<double> a1{1, 2, 3, 4, -9, 0};
  std::stack<double> b1;
  b1.push(1);
  b1.push(2);
  b1.push(3);
  b1.push(4);
  b1.push(-9);
  b1.push(0);
  s21::stack<double> c1;
  c1 = (s21::stack<double> &&) a1;
  compare_stack(c1, b1);
}

TEST(stack_create_and_remove_suit, copy_and_move_constructor_2) {
  s21::stack<int> a{1, 2, 3, 4, -9, 0};
  std::stack<int> b;
  b.push(1);
  b.push(2);
  b.push(3);
  b.push(4);
  b.push(-9);
  b.push(0);
  s21::stack<int> c(a);
  compare_stack(c, b);
}

TEST(stack_create_and_remove_suit, swap_1) {
  s21::stack<int> a({1000});
  s21::stack<int> b({0});
  s21::stack<int> c({0});

  std::stack<int> astd({1000});
  std::stack<int> bstd({0});
  std::stack<int> cstd({0});

  a.swap(c);
  astd.swap(cstd);
  compare_stack(a, astd);
}

TEST(stack_create_and_remove_suit, swap_2) {
  s21::stack<bool> a1({true});
  std::stack<bool> b1;
  b1.push({false});
  s21::stack<bool> c1;
  c1.push({false});
  a1.swap(c1);
  compare_stack(a1, b1);
}

TEST(stack_create_and_remove_suit, equal) {
  s21::stack<bool> a1{1};
  std::stack<bool> b1;
  b1.push(0);
  s21::stack<bool> c1;
  c1.push(0);
  a1 = (s21::stack<bool> &&) c1;
  compare_stack(a1, b1);
}

TEST(tests_stack, default_constructor) {
  // arrange and act
  s21::stack<int> aboba;
  std::stack<int> buba;

  // assert
  ASSERT_EQ(aboba.size(), buba.size());
  ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_stack, init_constructor) {
  // arrange and act
  s21::stack<int> aboba{1, 2, 3, 4, 5};
  std::stack<int> buba({1, 2, 3, 4, 5});

  // assert
  ASSERT_EQ(aboba.top(), buba.top());
  ASSERT_EQ(aboba.size(), buba.size());
}

TEST(tests_stack, copy_constructor) {
  // arrange and act
  s21::stack<int> aboba{1, 2, 3, 4, 5};
  s21::stack<int> aboba_copy(aboba);
  std::stack<int> buba({1, 2, 3, 4, 5});
  std::stack<int> buba_copy(buba);

  // assert
  ASSERT_EQ(aboba_copy.top(), buba_copy.top());
  ASSERT_EQ(aboba.top(), buba.top());
  ASSERT_EQ(aboba_copy.size(), buba_copy.size());
  ASSERT_EQ(aboba.size(), buba.size());
}

TEST(tests_stack, move_constructor) {
  // arrange and act
  s21::stack<int> aboba{1, 2, 3, 4, 5};
  s21::stack<int> aboba_move(std::move(aboba));
  std::stack<int> buba({1, 2, 3, 4, 5});
  std::stack<int> buba_move(std::move(buba));

  // assert
  ASSERT_EQ(aboba_move.top(), buba_move.top());
  ASSERT_EQ(aboba_move.size(), buba_move.size());
  ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_stack, assignment_operator) {
  // arrange and act
  s21::stack<int> aboba{1, 2, 3, 4, 5};
  // s21::stack<int> aboba_2 = std::move(aboba);
  s21::stack<int> aboba_2;
  aboba_2 = (s21::stack<int> &&) aboba;
  std::stack<int> buba({1, 2, 3, 4, 5});
  std::stack<int> buba_2 = std::move(buba);

  // assert
  ASSERT_EQ(aboba_2.top(), buba_2.top());
  ASSERT_EQ(aboba_2.size(), buba_2.size());
  ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_stack, empty) {
  // arrange
  s21::stack<int> aboba{1, 2, 3, 4, 5};
  std::stack<int> buba({1, 2, 3, 4, 5});

  // act and assert
  ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_stack, size) {
  // arrange
  s21::stack<int> aboba{1, 2, 3, 4, 5};

  // act and assert
  ASSERT_EQ(aboba.size(), 5);
}

TEST(tests_stack, push) {
  // arrange
  s21::stack<int> aboba;
  std::stack<int> buba;
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
  ASSERT_EQ(aboba.top(), buba.top());
  ASSERT_EQ(aboba.size(), buba.size());
}

TEST(tests_stack, pop) {
  // arrange
  s21::stack<int> aboba{1, 2, 3, 4};
  std::stack<int> buba({1, 2, 3, 4});

  // act
  aboba.pop();
  buba.pop();

  // assert
  ASSERT_EQ(aboba.top(), buba.top());
  ASSERT_EQ(aboba.size(), buba.size());
  ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(tests_stack, swap) {
  // arrange
  s21::stack<int> aboba{1, 2, 3, 4, 5};
  s21::stack<int> aboba_2{6, 7, 8};
  std::stack<int> buba({1, 2, 3, 4, 5});
  std::stack<int> buba_2({6, 7, 8});

  // act
  aboba.swap(aboba_2);
  buba.swap(buba_2);

  // assert
  ASSERT_EQ(aboba_2.top(), buba_2.top());
  ASSERT_EQ(aboba_2.size(), buba_2.size());
  ASSERT_EQ(aboba.top(), buba.top());
  ASSERT_EQ(aboba.size(), buba.size());
}

TEST(tests_stack_bonus_suit, emplace_front) {
  // arrange
  s21::stack<int> aboba{1, 2, 3, 4, 5, 6};
  std::stack<int> buba({1, 2, 3, 4, 5, 6, 5, 9, 11, 7});

  // act
  aboba.emplace_front(5, 9, 11, 7);
  // assert
  ASSERT_EQ(aboba.top(), buba.top());
  ASSERT_EQ(aboba.size(), buba.size());
  ASSERT_EQ(aboba.empty(), buba.empty());
}

TEST(stack, stack_1) {
  s21::stack<int> stack{};
  ASSERT_TRUE(stack.empty());
}

TEST(stack, stack_2) {
  s21::stack<int> stack{};
  stack.push(45);
  ASSERT_EQ(stack.top(), 45);
}

TEST(stack, stack_3) {
  s21::stack<int> stack{1, 2, 3};
  std::stack<int> original;
  original.push(1);
  original.push(2);
  original.push(3);

  while (!stack.empty()) {
    ASSERT_EQ(stack.top(), original.top());
    stack.pop();
    original.pop();
  }
}

TEST(stack, stack_4) {
  s21::stack<int> stack{55, 44, 33};
  ASSERT_EQ(stack.size(), 3);
  ASSERT_EQ(stack.top(), 33);
  stack.pop();
  ASSERT_EQ(stack.top(), 44);
  stack.pop();
  ASSERT_EQ(stack.top(), 55);
  stack.pop();
}

TEST(stack, stack_5) {
  s21::stack<int> stack1{1, 2, 3};
  s21::stack<int> stack2{4, 5, 6, 7};
  stack1.swap(stack2);
  ASSERT_EQ(stack1.size(), 4);
  ASSERT_EQ(stack1.top(), 7);
  stack1.pop();
  ASSERT_EQ(stack1.top(), 6);
  stack1.pop();
  ASSERT_EQ(stack1.top(), 5);
  stack1.pop();
  ASSERT_EQ(stack1.top(), 4);
  stack1.pop();
  ASSERT_EQ(stack2.size(), 3);
  ASSERT_EQ(stack2.top(), 3);
  stack2.pop();
  ASSERT_EQ(stack2.top(), 2);
  stack2.pop();
  ASSERT_EQ(stack2.top(), 1);
  stack2.pop();
}

TEST(stack, stack_6) {
  s21::stack<int> stack1{1, 2, 3};
  s21::stack<int> stack2(std::move(stack1));
  ASSERT_TRUE(stack1.empty());
  ASSERT_EQ(stack2.top(), 3);
}

TEST(stack, stack_7) {
  s21::stack<int> stack1{1, 2, 3};
  s21::stack<int> stack2{};
  stack2 = std::move(stack1);
  ASSERT_TRUE(stack1.empty());
  ASSERT_EQ(stack2.top(), 3);
}

TEST(stack, stack_8) {
  s21::stack<std::string> stack{"a", "b", "c"};
  ASSERT_EQ(stack.size(), 3);
  ASSERT_EQ(stack.top(), "c");
  stack.pop();
  ASSERT_EQ(stack.top(), "b");
  stack.pop();
  ASSERT_EQ(stack.top(), "a");
  stack.pop();
}

TEST(stack, stack_9) {
  s21::stack<double> stack1{67, 56, 45};
  s21::stack<double> stack2(stack1);
  stack2.swap(stack1);
  ASSERT_EQ(stack1.size(), stack2.size());
  ASSERT_EQ(stack2.top(), 45);
  stack2.pop();
  ASSERT_EQ(stack2.top(), 56);
  stack2.pop();
  ASSERT_EQ(stack2.top(), 67);
  stack2.pop();
}

TEST(stack, test_emplace_front) {
  s21::stack<double> test{1.11, 2.22, 3.33, 4.44, 5.55};
  test.emplace_front(3.0, 42.0, 5.0);
  s21::stack<double> check{3.0, 42.0, 5.0, 1.11, 2.22, 3.33, 4.44, 5.55};
  check.emplace_front(3.0, 42.0, 5.0);
  ASSERT_EQ(test.top(), check.top());
}
