#ifndef CPP2_S21_CONTAINERS_2_CONTAINERS_S21_STACK_H_
#define CPP2_S21_CONTAINERS_2_CONTAINERS_S21_STACK_H_

#include "s21_list.h"

namespace s21 {
template <typename T, class Container = list<T>>
class stack {
 private:
  Container cont_stack;

 public:
  stack() = default;
  stack(std::initializer_list<T> const &items) : cont_stack(items) {}
  stack(const stack &s) = default;
  stack(stack &&s) = default;
  stack &operator=(const stack &s) = default;
  stack &operator=(stack &&s) = default;

  typename Container::const_reference top() { return cont_stack.back(); }
  typename Container::size_type size() { return cont_stack.size(); }
  bool empty() { return cont_stack.empty(); }
  void pop() { cont_stack.pop_back(); }
  void push(typename Container::const_reference value) {
    cont_stack.push_back(value);
  }
  void swap(stack &other) { cont_stack.swap(other.cont_stack); }

  template <typename... Args>
  void emplace_front(Args &&...args) {
    cont_stack.emplace_back(args...);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_CONTAINERS_S21_STACK_H_