#ifndef CPP2_S21_CONTAINERS_2_CONTAINERS_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_2_CONTAINERS_S21_MULTISET_H_

#include "RBTree.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key>
class Multiset : public RBTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using size_type = std::size_t;
  using const_reference = const Key &;
  using reference = Key &;
  using const_iterator =
      typename s21::RBTree<key_type, value_type>::const_iterator;
  using iterator = typename s21::RBTree<key_type, value_type>::iterator;

  Multiset() = default;
  explicit Multiset(std::initializer_list<value_type> const &items);
  Multiset(const Multiset &ms);
  Multiset &operator=(const Multiset &other);
  Multiset(Multiset &&ms) noexcept;
  Multiset operator=(Multiset &&ms);
  ~Multiset() = default;

  iterator insert(const_reference value);
  iterator find(const_reference value) const;
  iterator begin() const;
  iterator end() const;
  void erase(const_reference value);

  int size() const;
  void clear();
  bool empty() const;
  size_type max_size();
  void swap(Multiset<Key> &other);
  bool contains(const_reference value) const;
  int count(const_reference value) const;

  void merge(Multiset &other);
  iterator lower_bound(const_reference key);
  iterator upper_bound(const_reference key);

  std::pair<typename Multiset<value_type>::iterator,
            typename Multiset<value_type>::iterator>
  equal_range(const_reference key);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args &&...args);

 private:
  RBTree<key_type, value_type> tree_;
  using s21::RBTree<key_type, value_type>::root_;
  size_type size_{};
};

template <class value_type>
Multiset<value_type>::Multiset(const Multiset<value_type> &ms) {
  for (iterator it = ms.begin(); it != ms.end(); ++it) {
    insert((*it).key);
  }
}

template <class value_type>
Multiset<value_type>::Multiset(const std::initializer_list<value_type> &items) {
  for (const auto &item : items) {
    insert(item);
  }
}

template <class value_type>
Multiset<value_type> &Multiset<value_type>::operator=(
    const Multiset<value_type> &other) {
  if (this != &other) {
    Multiset<value_type> temp(other);
    swap(temp);
  }
  return *this;
}

template <class value_type>
Multiset<value_type>::Multiset(Multiset<value_type> &&ms) noexcept {
  swap(ms);
  ms.clear();
}

template <class value_type>
Multiset<value_type> s21::Multiset<value_type>::operator=(
    Multiset<value_type> &&ms) {
  if (this != &ms) {
    swap(ms);
    ms.clear();
  }
  return *this;
}

template <class value_type>
void Multiset<value_type>::clear() {
  s21::RBTree<value_type, value_type>::DeleteTree(root_);
  size_ = 0;
  root_ = nullptr;
}

template <typename value_type>
void Multiset<value_type>::swap(Multiset<value_type> &other) {
  tree_.swap(other.tree_);
  std::swap(size_, other.size_);
}

template <class value_type>
typename Multiset<value_type>::iterator Multiset<value_type>::insert(
    const_reference value) {
  tree_.Insert(value, value);
  ++size_;
  iterator result = find(value);
  return result;
}

template <class value_type>
void Multiset<value_type>::erase(const_reference value) {
  Node<value_type, value_type> *node = tree_.Find(tree_.GetRoot(), value);
  if (node != nullptr) {
    tree_.Erase(node);
    --size_;
  }
}

template <class value_type>
int Multiset<value_type>::size() const {
  return size_;
}

template <class value_type>
bool Multiset<value_type>::empty() const {
  return (root_ == nullptr && size_ == 0);
}

template <class value_type>
std::size_t Multiset<value_type>::max_size() {
  return SIZE_MAX / ((sizeof(size_t) * 5) * 2);
}

template <class value_type>
bool Multiset<value_type>::contains(const_reference value) const {
  return tree_.Contains(value);
}

template <typename value_type>
int Multiset<value_type>::count(const_reference value) const {
  int count = 0;
  for (iterator it = begin(); it != end(); ++it) {
    if (it->key == value) {
      ++count;
    }
  }
  return count;
}

template <class value_type>
typename Multiset<value_type>::iterator Multiset<value_type>::begin() const {
  Node<key_type, value_type> *node = tree_.GetRoot();
  while (node != nullptr && node->left != nullptr) {
    node = node->left;
  }
  return iterator(node);
}

template <class value_type>
typename Multiset<value_type>::iterator Multiset<value_type>::end() const {
  return iterator(nullptr);
}

template <class value_type>
typename Multiset<value_type>::iterator Multiset<value_type>::find(
    const_reference value) const {
  return iterator(tree_.Find(tree_.GetRoot(), value));
}

template <class value_type>
void Multiset<value_type>::merge(Multiset<value_type> &other) {
  if (this == &other) {
    return;
  }
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(it->key);
  }
  other.clear();
}

template <class value_type>
typename Multiset<value_type>::iterator Multiset<value_type>::lower_bound(
    const_reference key) {
  iterator it = begin();
  iterator it_end = end();
  while (it != it_end) {
    if (*it >= key) {
      return it;
    }
    ++it;
  }
  return it_end;
}

template <class value_type>
typename Multiset<value_type>::iterator Multiset<value_type>::upper_bound(
    const_reference key) {
  iterator it = begin();
  iterator it_end = end();
  while (it != it_end && !(*it > key)) {
    ++it;
  }
  return it;
}

template <class value_type>
std::pair<typename Multiset<value_type>::iterator,
          typename Multiset<value_type>::iterator>
Multiset<value_type>::equal_range(const_reference key) {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename value_type>
template <typename... Args>
s21::vector<std::pair<typename Multiset<value_type>::iterator, bool>>
Multiset<value_type>::emplace(Args &&...args) {
  s21::vector<std::pair<iterator, bool>> result;
  std::pair<iterator, bool> element;
  s21::vector<typename Multiset<value_type>::key_type> argsVector{
      std::forward<Args>(args)...};
  for (auto &item : argsVector) {
    element.first = insert(item);
    element.second = true;
    result.push_back(element);
  }
  return result;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_CONTAINERS_S21_MULTISET_H_
