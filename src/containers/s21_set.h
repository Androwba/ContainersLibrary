#ifndef CPP2_S21_CONTAINERS_2_CONTAINERS_S21_SET_H_
#define CPP2_S21_CONTAINERS_2_CONTAINERS_S21_SET_H_

#include "RBTree.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key>
class Set : public RBTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using size_type = std::size_t;
  using const_reference = const Key &;
  using reference = Key &;
  using const_iterator =
      typename s21::RBTree<key_type, value_type>::const_iterator;
  using iterator = typename s21::RBTree<key_type, value_type>::iterator;

  Set() = default;
  explicit Set(std::initializer_list<value_type> const &items);
  Set(const Set &s);
  Set &operator=(const Set &other);
  Set(Set &&s) noexcept;
  Set operator=(Set &&s);
  ~Set() = default;

  std::pair<iterator, bool> insert(const value_type &value);
  void erase(const_reference value);
  int size() const;
  void clear();
  bool empty() const;
  size_type max_size();
  void swap(Set<Key> &other);
  bool contains(const_reference value) const;
  iterator find(const_reference value) const;
  iterator begin() const;
  iterator end() const;
  void merge(Set &other);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args &&...args);

 private:
  RBTree<key_type, value_type> tree_;
  using s21::RBTree<key_type, value_type>::root_;
  size_type size_{};
};

template <class value_type>
Set<value_type>::Set(const Set<value_type> &s) {
  for (iterator it = s.begin(); it != s.end(); ++it) {
    insert((*it).key);
  }
}

template <class value_type>
Set<value_type>::Set(const std::initializer_list<value_type> &items) {
  for (const auto &item : items) {
    insert(item);
  }
}

template <class value_type>
Set<value_type> &Set<value_type>::operator=(const Set<value_type> &other) {
  if (this != &other) {
    Set<value_type> temp(other);
    swap(temp);
  }
  return *this;
}

template <class value_type>
Set<value_type>::Set(Set<value_type> &&s) noexcept {
  swap(s);
  s.clear();
}

template <class value_type>
Set<value_type> Set<value_type>::operator=(Set<value_type> &&s) {
  if (this != &s) {
    swap(s);
    s.clear();
  }
  return *this;
}

template <class value_type>
void Set<value_type>::clear() {
  s21::RBTree<value_type, value_type>::DeleteTree(root_);
  size_ = 0;
  root_ = nullptr;
}

template <typename value_type>
void Set<value_type>::swap(Set<value_type> &other) {
  tree_.swap(other.tree_);
  std::swap(size_, other.size_);
}

template <class value_type>
std::pair<typename Set<value_type>::iterator, bool> Set<value_type>::insert(
    const value_type &value) {
  std::pair<iterator, bool> result;
  if (!contains(value)) {
    tree_.Insert(value, value);
    ++size_;
    result.second = true;
  } else {
    result.second = false;
  }
  result.first = find(value);
  return result;
}

template <class value_type>
void Set<value_type>::erase(const_reference value) {
  Node<value_type, value_type> *node = tree_.Find(tree_.GetRoot(), value);
  if (node != nullptr) {
    tree_.Erase(node);
    --size_;
  }
}

template <typename value_type>
int Set<value_type>::size() const {
  return size_;
}

template <typename value_type>
bool Set<value_type>::empty() const {
  return size_ == 0;
}

template <class value_type>
typename Set<value_type>::iterator Set<value_type>::find(
    const_reference value) const {
  return iterator(tree_.Find(tree_.GetRoot(), value));
}

template <typename value_type>
bool Set<value_type>::contains(const_reference value) const {
  return tree_.Contains(value);
}

template <class value_type>
typename Set<value_type>::iterator Set<value_type>::begin() const {
  Node<key_type, value_type> *node = tree_.GetRoot();
  while (node != nullptr && node->left != nullptr) {
    node = node->left;
  }
  return iterator(node);
}

template <class value_type>
typename Set<value_type>::iterator Set<value_type>::end() const {
  return iterator(nullptr);
}

template <class value_type>
std::size_t Set<value_type>::max_size() {
  return SIZE_MAX / ((sizeof(size_t) * 5) * 2);
}

template <class value_type>
void Set<value_type>::merge(Set<value_type> &other) {
  if (this == &other) {
    return;
  }
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(it->key);
  }
  other.clear();
}

template <typename value_type>
template <typename... Args>
s21::vector<std::pair<typename Set<value_type>::iterator, bool>>
Set<value_type>::emplace(Args &&...args) {
  s21::vector<value_type> argsVector{std::forward<Args>(args)...};
  s21::vector<std::pair<iterator, bool>> results;
  for (const auto &arg : argsVector) {
    results.push_back(insert(arg));
  }
  return results;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_CONTAINERS_S21_SET_H_
