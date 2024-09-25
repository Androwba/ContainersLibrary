#ifndef CPP2_S21_CONTAINERS_2_CONTAINERS_S21_LIST_H_
#define CPP2_S21_CONTAINERS_2_CONTAINERS_S21_LIST_H_

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <utility>

#include "s21_vector.h"

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  class listNode {
   public:
    T data_;
    listNode *p_next_;
    listNode *p_prev_;

    explicit listNode(const T &data = T(), listNode *p_next = nullptr,
                      listNode *p_prev = nullptr)
        : data_(data), p_next_(p_next), p_prev_(p_prev) {}
    explicit listNode(listNode *p_next, listNode *p_prev = nullptr,
                      T &&data = T())
        : data_(std::forward<T>(data)), p_next_(nullptr), p_prev_(p_prev) {
      p_next_ = p_next;
    }

    ~listNode() {
      p_next_ = nullptr;
      p_prev_ = nullptr;
    }
  };
  using Node = list<T>::listNode;

 public:
  class ListIterator {
   private:
    Node *p_node_;

   public:
    ListIterator() : p_node_(nullptr) {}
    ListIterator(Node *ptr) : p_node_(ptr) {}
    ListIterator(const list<T>::ListIterator &other) : p_node_(other.p_node_) {}
    ~ListIterator() { p_node_ = nullptr; }

    ListIterator &operator=(const list<T>::ListIterator &other);
    T &operator*() const;
    ListIterator &operator++();
    ListIterator &operator--();
    bool operator==(const list<T>::ListIterator &other);
    bool operator!=(const list<T>::ListIterator &other);

    friend class list;
  };
  using iterator = list<T>::ListIterator;
  friend class ListIterator;

  class ListConstIterator {
   private:
    iterator iter_;

   public:
    ListConstIterator() {}
    ListConstIterator(const list<T>::ListIterator &other) : iter_(other) {}
    ListConstIterator(const list<T>::ListConstIterator &other)
        : iter_(other.iter_) {}
    ~ListConstIterator() {}

    ListConstIterator &operator=(const list<T>::ListIterator &other);
    ListConstIterator &operator=(const list<T>::ListConstIterator &other);
    T operator*() const { return T(*iter_); }
    ListConstIterator &operator++();
    ListConstIterator &operator--();
    bool operator==(const list<T>::ListIterator &other);
    bool operator==(const list<T>::ListConstIterator &other);
    bool operator!=(const list<T>::ListIterator &other);
    bool operator!=(const list<T>::ListConstIterator &other);

    friend class list;
  };
  using const_iterator = list<T>::ListConstIterator;

  // Constructors
  list();
  explicit list(size_type n);
  explicit list(std::initializer_list<T> const &items);
  list(const list<T> &l);
  list(list<T> &&l);
  ~list();
  list &operator=(list<T> &&l);

  const_reference front();
  const_reference back();

  iterator begin() const;
  const_iterator cbegin() const { return (const_iterator)begin(); }
  iterator end() const;
  const_iterator cend() const { return (const_iterator)end(); }

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);

  template <typename... Args>
  void emplace_back(Args &&...args);

  template <typename... Args>
  void emplace_front(Args &&...args);

 private:
  size_type size_;
  Node *p_head_;
  Node *p_back_;
  Node *p_fantome_;

  iterator PositionToInsert(const_reference value, const iterator &last_sorted);
};

template <typename T>
list<T>::list() : size_(0), p_head_(nullptr), p_back_(nullptr) {
  p_fantome_ = new Node();
}

template <typename T>
list<T>::list(size_type n) : list() {
  for (size_t i = 0; i < n; ++i) {
    push_back(T());
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items) : list() {
  for (const auto &element : items) {
    push_back(element);
  }
}

template <typename T>
list<T>::list(const list<T> &l) : list() {
  const_iterator it = l.cbegin();
  for (size_t i = 0; i < l.size() && it != l.cend(); ++i, ++it) {
    push_back(*it);
  }
}

template <typename T>
list<T>::list(list<T> &&l)
    : size_(l.size_),
      p_head_(l.p_head_),
      p_back_(l.p_back_),
      p_fantome_(l.p_fantome_) {
  l.size_ = 0;
  l.p_head_ = nullptr;
  l.p_back_ = nullptr;
  l.p_fantome_ = new Node();
}

template <typename T>
list<T>::~list() {
  clear();
  delete p_fantome_;
  p_fantome_ = nullptr;
}

template <typename T>
list<T> &list<T>::operator=(list<T> &&l) {
  if (this->p_head_ != l.p_head_) {
    clear();
    p_head_ = l.p_head_;
    l.p_head_ = nullptr;
    p_back_ = l.p_back_;
    l.p_back_ = nullptr;
    p_fantome_->p_prev_ = p_back_;
    l.p_fantome_->p_prev_ = nullptr;
    size_ = l.size_;
    l.size_ = 0;
  }
  return *this;
}

template <typename T>
typename list<T>::const_reference list<T>::front() {
  iterator it = this->begin();
  return *it;
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  iterator it = this->end();
  return *(--it);
}

template <typename T>
typename list<T>::iterator list<T>::begin() const {
  iterator it;
  if (size_ == 0) {
    it = this->end();
  } else {
    it.p_node_ = this->p_head_;
  }
  return it;
}

template <typename T>
typename list<T>::iterator list<T>::end() const {
  iterator it(this->p_fantome_);
  return it;
}

template <typename T>
bool list<T>::empty() const {
  return size() == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
  return ((powl(2, 64) / sizeof(Node)) / 2);
}

template <typename T>
void list<T>::clear() {
  Node *tmp;
  for (size_t i = size_; i > 0; --i) {
    tmp = p_back_->p_prev_;
    delete p_back_;
    p_back_ = tmp;
  }
  if (p_fantome_ != nullptr) {
    p_fantome_->p_prev_ = nullptr;
  }
  p_head_ = nullptr;
  p_back_ = nullptr;
  size_ = 0;
}

template <typename T>
typename list<T>::iterator list<T>::insert(list<T>::iterator pos,
                                           list<T>::const_reference value) {
  if (pos == this->end()) {
    push_back(value);
    --pos;
  } else if (pos == this->begin()) {
    push_front(value);
    --pos;
  } else {
    Node *new_node = new Node(value);
    Node *prev = pos.p_node_->p_prev_;
    prev->p_next_ = new_node;
    new_node->p_prev_ = prev;
    new_node->p_next_ = pos.p_node_;
    pos.p_node_->p_prev_ = new_node;
    --pos;
    ++size_;
  }
  return pos;
}

template <typename T>
void list<T>::erase(list<T>::iterator pos) {
  if (pos == this->end()) {
    throw std::invalid_argument("Invalid pointer");
  }

  if (pos == this->begin()) {
    pop_front();
  } else if (pos == --(this->end())) {
    pop_back();
  } else {
    iterator pos_prev = --iterator(pos);
    iterator pos_next = ++iterator(pos);
    pos_prev.p_node_->p_next_ = pos_next.p_node_;
    pos_next.p_node_->p_prev_ = pos_prev.p_node_;
    delete pos.p_node_;
    --size_;
  }
}

template <typename T>
void list<T>::push_back(const_reference value) {
  if (size_ == 0) {
    p_head_ = new Node(value);
    p_back_ = p_head_;
    p_back_->p_next_ = p_fantome_;
    p_fantome_->p_prev_ = p_back_;
  } else {
    Node *tmp = new Node(value);
    tmp->p_next_ = p_fantome_;
    tmp->p_prev_ = p_back_;
    p_back_->p_next_ = tmp;
    p_back_ = tmp;
    p_fantome_->p_prev_ = p_back_;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_back() {
  if (!empty()) {
    if (size_ == 1) {
      delete p_head_;
      p_head_ = nullptr;
      p_back_ = nullptr;
      p_fantome_->p_prev_ = nullptr;
    } else {
      p_back_ = p_back_->p_prev_;
      delete p_back_->p_next_;
      p_back_->p_next_ = p_fantome_;
      p_fantome_->p_prev_ = p_back_;
    }
    --size_;
  }
}

template <typename T>
void list<T>::pop_front() {
  if (!empty()) {
    if (size_ == 1) {
      pop_back();
    } else {
      p_head_ = p_head_->p_next_;
      delete p_head_->p_prev_;
      --size_;
    }
  }
}

template <typename T>
void list<T>::push_front(const_reference value) {
  if (size_ == 0) {
    push_back(value);
  } else {
    Node *tmp = new Node(value);
    tmp->p_next_ = p_head_;
    p_head_->p_prev_ = tmp;
    p_head_ = tmp;
    ++size_;
  }
}

template <typename T>
void list<T>::swap(list &other) {
  if (this != &other) {
    list tmp = std::move(*this);
    *this = std::move(other);
    other = std::move(tmp);
  }
}

template <typename T>
void list<T>::merge(list &other) {
  if (this != &other && other.empty() == false) {
    this->p_back_->p_next_ = other.p_head_;
    other.p_head_->p_prev_ = this->p_back_;
    this->p_back_ = other.p_back_;
    this->p_back_->p_next_ = this->p_fantome_;
    this->p_fantome_->p_prev_ = this->p_back_;
    this->size_ += other.size_;

    other.size_ = 0;
    other.p_back_ = nullptr;
    other.p_head_ = nullptr;
    other.p_fantome_->p_prev_ = nullptr;
  }
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (other.empty()) {
    return;
  }
  if (pos == this->begin()) {
    this->p_head_->p_prev_ = other.p_back_;
    other.p_back_->p_next_ = this->p_head_;
    this->p_head_ = other.p_head_;
  } else if (pos == this->end()) {
    this->p_back_->p_next_ = other.p_head_;
    other.p_head_->p_prev_ = this->p_back_;
    this->p_back_ = other.p_back_;
  }
  this->p_back_->p_next_ = this->p_fantome_;
  this->p_fantome_->p_prev_ = this->p_back_;
  this->size_ += other.size_;

  other.size_ = 0;
  other.p_back_ = nullptr;
  other.p_head_ = nullptr;
  other.p_fantome_->p_prev_ = nullptr;
}

template <typename T>
void list<T>::reverse() {
  if (size_ > 1) {
    for (iterator prev_it(begin()), it(++begin());;) {
      prev_it.p_node_->p_next_ = prev_it.p_node_->p_prev_;
      prev_it.p_node_->p_prev_ = it.p_node_;
      prev_it = it;
      ++it;
      if (it == end()) {
        prev_it.p_node_->p_next_ = prev_it.p_node_->p_prev_;
        prev_it.p_node_->p_prev_ = nullptr;

        p_head_->p_next_ = p_fantome_;
        p_fantome_->p_prev_ = p_head_;
        p_back_ = p_head_;
        p_head_ = prev_it.p_node_;
        break;
      }
    }
  }
}

template <typename T>
void list<T>::unique() {
  if (size_ > 1) {
    for (iterator it = begin(), it_next = ++begin(); it_next != end();) {
      if (*it == *it_next) {
        erase(it_next);
        it_next = it;
        ++it_next;
      } else {
        ++it;
        ++it_next;
      }
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ <= 1) {
    return;
  }

  iterator last_sorted = begin();
  for (; last_sorted != --end();) {
    iterator next = ++iterator(last_sorted);
    if (*next >= *last_sorted) {
      last_sorted = next;
    } else {
      next.p_node_->p_prev_->p_next_ = next.p_node_->p_next_;
      next.p_node_->p_next_->p_prev_ = next.p_node_->p_prev_;
      iterator insert_pos = PositionToInsert(*next, last_sorted);
      p_head_->p_prev_ = next.p_node_;
      next.p_node_->p_next_ = p_head_;
      p_head_ = next.p_node_;
      p_head_->p_prev_ = nullptr;
    }
  }
  p_back_ = last_sorted.p_node_;
}

template <typename T>
typename list<T>::iterator list<T>::PositionToInsert(
    const list<T>::value_type &value, const list<T>::iterator &last_sorted) {
  iterator pos;
  if (value > *last_sorted) {
    pos = last_sorted;
    ++pos;
  } else {
    for (pos = begin(); pos != last_sorted && *pos < value; ++pos)
      ;
  }
  return pos;
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::emplace(const_iterator pos,
                                            Args &&...args) {
  list new_list;
  iterator before = pos.iter_;
  --before;
  (new_list.push_back(std::forward<T>(args)), ...);
  this->splice(pos, new_list);
  ++before;
  return before;
}

template <typename T>
template <typename... Args>
void list<T>::emplace_back(Args &&...args) {
  s21::vector<T> temp{args...};
  auto it = temp.begin();
  for (; it != temp.end(); ++it) {
    push_back(*it);
  }
}

template <typename T>
template <typename... Args>
void list<T>::emplace_front(Args &&...args) {
  s21::vector<T> temp{args...};
  auto it = temp.begin();
  for (; it != temp.end(); ++it) {
    push_front(*it);
  }
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator++() {
  if (p_node_->p_next_ != nullptr) {
    p_node_ = p_node_->p_next_;
  } else {
    while (p_node_->p_prev_ != nullptr) {
      --(*this);
    }
  }
  return *this;
}

template <typename T>
typename list<T>::ListConstIterator &list<T>::ListConstIterator::operator++() {
  ++iter_;
  return *this;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator--() {
  if (p_node_->p_prev_ != nullptr) {
    p_node_ = p_node_->p_prev_;
  } else {
    while (p_node_->p_next_ != nullptr) {
      ++(*this);
    }
  }
  return *this;
}

template <typename T>
typename list<T>::ListConstIterator &list<T>::ListConstIterator::operator--() {
  --iter_;
  return *this;
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator=(
    const list<T>::ListIterator &other) {
  p_node_ = other.p_node_;
  return *this;
}

template <typename T>
typename list<T>::ListConstIterator &list<T>::ListConstIterator::operator=(
    const list<T>::ListIterator &other) {
  this->iter_ = other;
  return *this;
}

template <typename T>
T &list<T>::ListIterator::operator*() const {
  return p_node_->data_;
}

template <typename T>
bool list<T>::ListIterator::operator==(const list<T>::ListIterator &other) {
  return p_node_ == other.p_node_;
}

template <typename T>
bool list<T>::ListConstIterator::operator==(
    const list<T>::ListIterator &other) {
  return this->iter_ == other;
}

template <typename T>
bool list<T>::ListConstIterator::operator==(
    const list<T>::ListConstIterator &other) {
  return this->iter_ == other.iter_;
}

template <typename T>
bool list<T>::ListIterator::operator!=(const list<T>::ListIterator &other) {
  return p_node_ != other.p_node_;
}

template <typename T>
bool list<T>::ListConstIterator::operator!=(
    const list<T>::ListIterator &other) {
  return this->iter_ != other;
}

template <typename T>
bool list<T>::ListConstIterator::operator!=(
    const list<T>::ListConstIterator &other) {
  return this->iter_ != other.iter_;
}

#endif  // CPP2_S21_CONTAINERS_2_CONTAINERS_S21_LIST_H_
