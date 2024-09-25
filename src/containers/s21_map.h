#ifndef CPP2_S21_CONTAINERS_2_CONTAINERS_S21_MAP_H_
#define CPP2_S21_CONTAINERS_2_CONTAINERS_S21_MAP_H_

#include "RBTree.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key, typename T>
class Map : public RBTree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using size_type = std::size_t;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename s21::RBTree<key_type, mapped_type>::iterator;
  using const_iterator =
      typename s21::RBTree<key_type, mapped_type>::const_iterator;
  using allocator_type = std::allocator<value_type>;

  Map();
  explicit Map(std::initializer_list<value_type> const &items);
  Map(const Map &other);
  Map(Map &&other) noexcept;
  ~Map();
  Map<key_type, mapped_type> &operator=(
      Map<key_type, mapped_type> &&other) noexcept;

  size_type size() const;
  size_type max_size();
  size_type count(const key_type &key) const;
  void clear();
  void swap(Map &other);
  bool empty() const;

  allocator_type get_allocator() const;

  mapped_type &at(const key_type &key) const;
  mapped_type &operator[](const key_type &key);

  void erase(iterator it);
  bool contains(const key_type &key) const;
  iterator find(const key_type &key) const;

  iterator begin() const;
  iterator end() const;
  iterator lower_bound(const key_type &val) const;
  iterator upper_bound(const key_type &val) const;
  std::pair<typename Map<key_type, mapped_type>::iterator,
            typename Map<key_type, mapped_type>::iterator>
  equal_range(const key_type &key) const;

  std::pair<iterator, bool> insert(const_reference value);
  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &value);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &value);

  void merge(Map &other);
  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> emplace(Args &&...args);

 private:
  RBTree<key_type, mapped_type> tree_;
  size_type size_{};
  using s21::RBTree<key_type, mapped_type>::root_;
};

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map() : tree_{}, size_{} {}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map(std::initializer_list<value_type> const &items)
    : tree_{}, size_{} {
  for (const auto &item : items) {
    insert(item);
  }
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map(const Map<key_type, mapped_type> &other) {
  for (const auto &pair : other) {
    insert(pair.key, pair.value);
  }
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::Map(Map<key_type, mapped_type> &&other) noexcept {
  clear();
  swap(other);
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type> &Map<key_type, mapped_type>::operator=(
    Map<key_type, mapped_type> &&other) noexcept {
  clear();
  swap(other);
  return *this;
}

template <typename key_type, typename mapped_type>
Map<key_type, mapped_type>::~Map() {}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert(const_reference value) {
  std::pair<iterator, bool> result;
  value_type item{value};
  if (!contains(item.first)) {
    tree_.Insert(item.first, item.second);
    result.second = true;
    ++size_;
  } else {
    result.second = false;
  }
  result.first = find(item.first);
  return result;
}

template <class key_type, class mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert(const key_type &key,
                                   const mapped_type &value) {
  std::pair<iterator, bool> result;
  if (!contains(key)) {
    tree_.Insert(key, value);
    ++size_;
    result.second = true;
  } else {
    result.second = false;
  }
  result.first = find(key);
  return result;
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator, bool>
Map<key_type, mapped_type>::insert_or_assign(const key_type &key,
                                             const mapped_type &value) {
  if (contains(key)) {
    at(key) = value;
    return std::make_pair(find(key), false);
  } else {
    insert(std::make_pair(key, value));
    return std::make_pair(find(key), true);
  }
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::erase(iterator it) {
  if (it != end()) {
    tree_.Erase(it.current());
    --size_;
  } else {
    throw std::out_of_range("The element to be erased does not exist in Map");
  }
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::iterator Map<key_type, mapped_type>::find(
    const key_type &key) const {
  Node<key_type, mapped_type> *current = tree_.GetRoot();
  while (current) {
    if (current->key == key) {
      return iterator(current);
    } else if (current->key < key) {
      current = current->right;
    } else {
      current = current->left;
    }
  }
  return end();
}

template <typename key_type, typename mapped_type>
bool Map<key_type, mapped_type>::contains(const key_type &key) const {
  return tree_.Contains(key);
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::iterator
Map<key_type, mapped_type>::begin() const {
  if (tree_.GetRoot() == nullptr) {
    return iterator(tree_.GetRoot());
  }
  Node<key_type, mapped_type> *leftmost = tree_.GetRoot();
  while (leftmost->left != nullptr) {
    leftmost = leftmost->left;
  }

  return iterator(leftmost);
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::iterator Map<key_type, mapped_type>::end()
    const {
  return iterator(nullptr);
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::allocator_type
Map<key_type, mapped_type>::get_allocator() const {
  return allocator_type();
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::size_type
Map<key_type, mapped_type>::count(const key_type &key) const {
  return find(key) != end() ? 1 : 0;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::size_type
Map<key_type, mapped_type>::size() const {
  return size_;
}

template <class key_type, class mapped_type>
std::size_t Map<key_type, mapped_type>::max_size() {
  return SIZE_MAX / (sizeof(Node<key_type, mapped_type>) * 2);
}

template <typename key_type, typename mapped_type>
bool Map<key_type, mapped_type>::empty() const {
  return size_ == 0;
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::clear() {
  s21::RBTree<key_type, mapped_type>::DeleteTree(root_);
  size_ = 0;
  root_ = nullptr;
}

template <typename key_type, typename mapped_type>
void Map<key_type, mapped_type>::swap(Map<key_type, mapped_type> &other) {
  std::swap(size_, other.size_);
  tree_.swap(other.tree_);
}

template <typename key_type, typename mapped_type>
mapped_type &Map<key_type, mapped_type>::at(const key_type &key) const {
  auto it = find(key);
  if (it == end()) {
    throw std::out_of_range("key not found in Map");
  }
  return it->value;
}

template <typename key_type, typename mapped_type>
mapped_type &Map<key_type, mapped_type>::operator[](const key_type &key) {
  if (contains(key)) {
    return at(key);
  } else {
    auto [it, inserted] = insert(std::make_pair(key, mapped_type{}));
    return it->value;
  }
}

template <class key_type, class mapped_type>
void Map<key_type, mapped_type>::merge(Map<key_type, mapped_type> &other) {
  iterator it_begin = other.begin();
  iterator it_end = other.end();
  while (it_begin != it_end) {
    if (!contains(it_begin.current()->key)) {
      insert(it_begin.current()->key, it_begin.current()->value);
    } else {
      at(it_begin.current()->key) = it_begin.current()->value;
    }
    ++it_begin;
  }
  other.clear();
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::iterator
Map<key_type, mapped_type>::lower_bound(const key_type &val) const {
  auto it = begin();
  while (it != end() && it->key < val) {
    ++it;
  }
  return it;
}

template <typename key_type, typename mapped_type>
typename Map<key_type, mapped_type>::iterator
Map<key_type, mapped_type>::upper_bound(const key_type &val) const {
  auto it = begin();
  while (it != end() && it->key <= val) {
    ++it;
  }
  return it;
}

template <typename key_type, typename mapped_type>
std::pair<typename Map<key_type, mapped_type>::iterator,
          typename Map<key_type, mapped_type>::iterator>
Map<key_type, mapped_type>::equal_range(const key_type &key) const {
  iterator lower = lower_bound(key);
  iterator upper = upper_bound(key);
  return std::make_pair(lower, upper);
}

template <class key_type, class mapped_type>
template <class... Args>
s21::vector<std::pair<typename Map<key_type, mapped_type>::iterator, bool>>
Map<key_type, mapped_type>::emplace(Args &&...args) {
  std::initializer_list<value_type> argsVector{std::forward<Args>(args)...};
  s21::vector<std::pair<iterator, bool>> result;
  std::pair<iterator, bool> element;
  for (value_type value : argsVector) {
    element = insert(value);
    result.push_back(element);
  }
  return result;
}

}  //  namespace s21

#endif  // CPP2_S21_CONTAINERS_2_CONTAINERS_S21_MAP_H_
