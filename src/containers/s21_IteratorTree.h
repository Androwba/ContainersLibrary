#ifndef CPP2_S21_CONTAINERS_2_CONTAINERS_S21_ITERATORTREE_H_
#define CPP2_S21_CONTAINERS_2_CONTAINERS_S21_ITERATORTREE_H_

#include <stdexcept>

#include "NodeTree.h"

namespace s21 {

template <class Key, class Value>
class RBTreeIterator {
 public:
  using key_type = Key;
  using value_type = Value;
  typedef Node<key_type, value_type> Nodes;

  RBTreeIterator(Nodes *node = nullptr);
  RBTreeIterator<Key, Value> &operator++();
  RBTreeIterator<Key, Value> operator++(int);
  RBTreeIterator<Key, Value> &operator--();
  RBTreeIterator<Key, Value> operator--(int);
  Node<Key, Value> &operator*() const;
  Nodes *operator->() const;
  bool operator==(const RBTreeIterator<Key, Value> &other) const;
  bool operator!=(const RBTreeIterator<Key, Value> &other) const;
  explicit operator bool() const;
  Node<Key, Value> *current() const;

 private:
  Nodes *current_{nullptr};
};

template <class Key, class Value>
RBTreeIterator<Key, Value>::RBTreeIterator(Nodes *node) : current_(node) {}

template <class Key, class Value>
Node<Key, Value> *RBTreeIterator<Key, Value>::current() const {
  return current_;
}

template <class Key, class Value>
RBTreeIterator<Key, Value> &RBTreeIterator<Key, Value>::operator++() {
  if (!current_) {
    throw std::out_of_range("Iterator has gone out of bounds");
  }
  if (current_->right) {
    current_ = current_->right;
    while (current_->left) {
      current_ = current_->left;
    }
  } else {
    if (!current_->parent) {
      current_ = nullptr;
    } else {
      Node<Key, Value> *p = current_->parent;
      while (p && current_ == p->right) {
        current_ = p;
        p = p->parent;
      }
      current_ = p;
    }
  }
  return *this;
}

template <class Key, class Value>
RBTreeIterator<Key, Value> RBTreeIterator<Key, Value>::operator++(int) {
  RBTreeIterator<Key, Value> temp(*this);
  ++(*this);
  return temp;
}

template <class Key, class Value>
RBTreeIterator<Key, Value> &RBTreeIterator<Key, Value>::operator--() {
  if (current_ == nullptr) {
    return *this;
  }
  if (current_->left != nullptr) {
    // find the rightmost(biggest) node in the left subtree
    current_ = current_->left;
    while (current_->right != nullptr) {
      current_ = current_->right;
    }
  } else {
    // find the nearest ancestor whose right child is also an ancestor
    while (current_->parent != nullptr && current_ == current_->parent->left) {
      current_ = current_->parent;
    }
    current_ = current_->parent;
  }

  if (current_ == nullptr) {
    throw std::out_of_range("Iterator has gone out of bounds");
  }

  return *this;
}

template <class Key, class Value>
RBTreeIterator<Key, Value> RBTreeIterator<Key, Value>::operator--(int) {
  RBTreeIterator<Key, Value> temp(*this);
  --(*this);
  return temp;
}

template <class Key, class Value>
Node<Key, Value> &RBTreeIterator<Key, Value>::operator*() const {
  return *current_;
}

template <class Key, class Value>
Node<Key, Value> *RBTreeIterator<Key, Value>::operator->() const {
  return current_;
}

template <class Key, class Value>
bool RBTreeIterator<Key, Value>::operator==(
    const RBTreeIterator<Key, Value> &other) const {
  if (current_ == nullptr && other.current_ == nullptr) {
    return true;
  } else if (current_ == nullptr || other.current_ == nullptr) {
    return false;
  } else {
    return current_->key == other.current_->key;
  }
}

template <typename Key, typename Value>
bool operator==(const Node<Key, Value> &lhs, const Node<Key, Value> &rhs) {
  return lhs.key == rhs.key;
}

template <typename Key>
bool operator==(const Node<Key, Key> &lhs, const Key &rhs) {
  return lhs.key == rhs;
}

template <class Key, class Value>
bool RBTreeIterator<Key, Value>::operator!=(
    const RBTreeIterator<Key, Value> &other) const {
  return !(*this == other);
}

template <class Key, class Value>
RBTreeIterator<Key, Value>::operator bool() const {
  return current_ != nullptr;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_CONTAINERS_S21_ITERATORTREE_H_
