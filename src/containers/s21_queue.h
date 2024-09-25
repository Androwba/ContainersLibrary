#ifndef CPP2_S21_CONTAINERS_2_CONTAINERS_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_2_CONTAINERS_S21_QUEUE_H_

#include <memory>

#include "s21_list.h"
namespace s21 {
template <typename T, class Container = list<T>>
class queue {
 private:
  Container cont_queue;

 public:
  queue() = default;
  queue(std::initializer_list<T> const &items) : cont_queue(items) {}
  queue(const queue &q) = default;
  queue(queue &&q) = default;
  queue &operator=(const queue &q) = default;
  queue &operator=(queue &&q) = default;

  typename Container::const_reference front() { return cont_queue.front(); }
  typename Container::const_reference back() { return cont_queue.back(); }
  bool empty() { return cont_queue.empty(); }
  typename Container::size_type size() { return cont_queue.size(); }
  void push(typename Container::const_reference value) {
    cont_queue.push_back(value);
  }
  void pop() { cont_queue.pop_front(); }
  void swap(queue &other) { cont_queue.swap(other.cont_queue); }

  template <typename... Args>
  void emplace_back(Args &&...args) {
    cont_queue.emplace_back(args...);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_CONTAINERS_S21_QUEUE_H_