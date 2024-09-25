#ifndef CPP2_S21_CONTAINERS_2_CONTAINERS_RBTREE_H_
#define CPP2_S21_CONTAINERS_2_CONTAINERS_RBTREE_H_

#include <iostream>

#include "s21_IteratorTree.h"

namespace s21 {

template <class Key, class Value>
class RBTree {
 public:
  using iterator = RBTreeIterator<Key, Value>;
  using const_iterator = const RBTreeIterator<Key, Value>;

  RBTree() : root_(nullptr) {}

  ~RBTree() { DeleteTree(root_); }

  void Insert(const Key &key, const Value &value);
  void Erase(Node<Key, Value> *node);
  void swap(RBTree &other) noexcept;

  Node<Key, Value> *GetRoot() const;
  Node<Key, Value> *Find(Node<Key, Value> *node, const Key &key) const;
  bool Contains(const Key &key) const;

 protected:
  void DeleteTree(Node<Key, Value> *node);
  Node<Key, Value> *root_;

 private:
  void SetNewNode(Node<Key, Value> *newNode, Node<Key, Value> *parent);
  void LeftRotate(Node<Key, Value> *node);
  void RightRotate(Node<Key, Value> *node);
  void FixUpTree(Node<Key, Value> *node);
  Node<Key, Value> *FindMax(Node<Key, Value> *node) const;
};

template <class Key, class Value>
void RBTree<Key, Value>::DeleteTree(Node<Key, Value> *node) {
  if (node != nullptr) {
    DeleteTree(node->left);
    DeleteTree(node->right);
    node->left = nullptr;
    node->right = nullptr;
    delete node;
  }
}

template <class Key, class Value>
Node<Key, Value> *RBTree<Key, Value>::GetRoot() const {
  return root_;
}

template <class Key, class Value>
void RBTree<Key, Value>::swap(RBTree &other) noexcept {
  std::swap(root_, other.root_);
}

template <class Key, class Value>
Node<Key, Value> *RBTree<Key, Value>::Find(Node<Key, Value> *node,
                                           const Key &key) const {
  while (node != nullptr) {
    if (key == node->key) {
      return node;
    } else if (key < node->key) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  throw std::out_of_range("Key not found");
}

template <class Key, class Value>
void RBTree<Key, Value>::Insert(const Key &key, const Value &value) {
  Node<Key, Value> *newNode = new Node<Key, Value>(key, value);
  // If the root is null, set the new node as the root and color it black
  if (root_ == nullptr) {
    root_ = newNode;
    root_->color = Color::Black;
  } else {
    SetNewNode(newNode, root_);
    newNode->color = Color::Red;
    // Fix any violations of the Red-Black Tree properties
    Node<Key, Value> *node = newNode;
    while (node->parent != nullptr && node->parent->color == Color::Red) {
      Node<Key, Value> *parent = node->parent;
      Node<Key, Value> *grandparent = parent->parent;
      if (parent == grandparent->left) {
        Node<Key, Value> *uncle = grandparent->right;
        if (uncle != nullptr && uncle->color == Color::Red) {
          // Case 1: Recolor the parent, the sibling, and the grandparent
          parent->color = Color::Black;
          uncle->color = Color::Black;
          grandparent->color = Color::Red;
          node = grandparent;
        } else {
          if (node == parent->right) {
            // Case 2: Left rotate on the parent
            node = parent;
            LeftRotate(node);
            parent = node->parent;
            grandparent = parent->parent;
          }
          // Case 3: Recolor the parent and grandparent and right rotate on the
          // grandparent
          parent->color = Color::Black;
          grandparent->color = Color::Red;
          RightRotate(grandparent);
        }
      } else {
        Node<Key, Value> *uncle = grandparent->left;
        if (uncle != nullptr && uncle->color == Color::Red) {
          // Case 1: Recolor the parent, the sibling, and the grandparent
          parent->color = Color::Black;
          uncle->color = Color::Black;
          grandparent->color = Color::Red;
          node = grandparent;
        } else {
          if (node == parent->left) {
            // Case 2: Right rotate on the parent
            node = parent;
            RightRotate(node);
            parent = node->parent;
            grandparent = parent->parent;
          }
          // Case 3: Recolor the parent and grandparent and left rotate on the
          // grandparent
          parent->color = Color::Black;
          grandparent->color = Color::Red;
          LeftRotate(grandparent);
        }
      }
    }
    root_->color = Color::Black;
  }
}

template <class Key, class Value>
void RBTree<Key, Value>::SetNewNode(Node<Key, Value> *newNode,
                                    Node<Key, Value> *parent) {
  if (newNode->key < parent->key) {
    if (parent->left == nullptr) {
      // Set newNode as left child of parent
      parent->left = newNode;
      newNode->parent = parent;
    } else {
      // Recursively call SetNewNode with the left child of parent
      SetNewNode(newNode, parent->left);
    }
  } else {
    if (parent->right == nullptr) {
      parent->right = newNode;
      newNode->parent = parent;
    } else {
      SetNewNode(newNode, parent->right);
    }
  }
}

template <class Key, class Value>
bool RBTree<Key, Value>::Contains(const Key &key) const {
  Node<Key, Value> *node = root_;
  while (node != nullptr) {
    if (key == node->key) {
      return true;
    } else if (key < node->key) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return false;
}

template <class Key, class Value>
void RBTree<Key, Value>::LeftRotate(Node<Key, Value> *node) {
  Node<Key, Value> *rightChild = node->right;
  // Promote right child to be the parent of the node
  rightChild->parent = node->parent;
  if (node->parent == nullptr) {
    root_ = rightChild;
  } else if (node == node->parent->left) {
    node->parent->left = rightChild;
  } else {
    node->parent->right = rightChild;
  }
  // Shift nodes around
  node->right = rightChild->left;
  if (rightChild->left != nullptr) {
    rightChild->left->parent = node;
  }
  rightChild->left = node;
  node->parent = rightChild;
}

template <class Key, class Value>
void RBTree<Key, Value>::RightRotate(Node<Key, Value> *node) {
  Node<Key, Value> *leftChild = node->left;
  leftChild->parent = node->parent;
  if (node->parent == nullptr) {
    root_ = leftChild;
  } else if (node == node->parent->left) {
    node->parent->left = leftChild;
  } else {
    node->parent->right = leftChild;
  }
  node->left = leftChild->right;
  if (leftChild->right != nullptr) {
    leftChild->right->parent = node;
  }
  leftChild->right = node;
  node->parent = leftChild;
}

template <class Key, class Value>
void RBTree<Key, Value>::Erase(Node<Key, Value> *node) {
  // Case 1: Node has no children
  if (node->left == nullptr && node->right == nullptr) {
    if (node == root_) {
      root_ = nullptr;
    } else {
      if (node->color == Color::Black) {
        FixUpTree(node);
      }
      if (node->parent->left == node) {
        node->parent->left = nullptr;
      } else {
        node->parent->right = nullptr;
      }
    }
    delete node;
    return;
  }

  // Case 2: Node has one child
  if (node->left == nullptr || node->right == nullptr) {
    Node<Key, Value> *child = node->left ? node->left : node->right;
    if (node == root_) {
      root_ = child;
      root_->parent = nullptr;
      root_->color = Color::Black;
    } else {
      if (node->parent->left == node) {
        node->parent->left = child;
      } else {
        node->parent->right = child;
      }
      child->parent = node->parent;
      if (node->color == Color::Black) {
        if (child->color == Color::Red) {
          child->color = Color::Black;
        }
      }
    }
    delete node;
    return;
  }
  // Case 3: Node has two children
  Node<Key, Value> *predecessor = FindMax(node->left);
  std::swap(node->key, predecessor->key);
  std::swap(node->value, predecessor->value);
  Erase(predecessor);
}

template <class Key, class Value>
Node<Key, Value> *RBTree<Key, Value>::FindMax(Node<Key, Value> *node) const {
  while (node->right != nullptr) {
    node = node->right;
  }
  return node;
}

// Fixing double black violations in the tree
template <class Key, class Value>
void RBTree<Key, Value>::FixUpTree(Node<Key, Value> *node) {
  while (node != root_ && node->color == Color::Black) {
    if (node == node->parent->left) {
      Node<Key, Value> *sibling = node->parent->right;
      // Case 1: Sibling is red
      if (sibling != nullptr && sibling->color == Color::Red) {
        sibling->color = Color::Black;
        node->parent->color = Color::Red;
        LeftRotate(node->parent);
        sibling = node->parent->right;
      }
      // Case 2: Sibling's children are black
      if ((sibling->left == nullptr || sibling->left->color == Color::Black) &&
          (sibling->right == nullptr ||
           sibling->right->color == Color::Black)) {
        sibling->color = Color::Red;
        node = node->parent;
      } else {
        // Case 3: Sibling's right child is black
        if (sibling->right == nullptr ||
            sibling->right->color == Color::Black) {
          sibling->left->color = Color::Black;
          sibling->color = Color::Red;
          RightRotate(sibling);
          sibling = node->parent->right;
        }
        // Case 4: Sibling's right child is red
        sibling->color = node->parent->color;
        node->parent->color = Color::Black;
        sibling->right->color = Color::Black;
        LeftRotate(node->parent);
        node = root_;
      }
    } else {
      Node<Key, Value> *sibling = node->parent->left;
      // Case 1: Sibling is red
      if (sibling != nullptr && sibling->color == Color::Red) {
        sibling->color = Color::Black;
        node->parent->color = Color::Red;
        RightRotate(node->parent);
        sibling = node->parent->left;
      }
      // Case 2: Sibling's children are black
      if ((sibling->left == nullptr || sibling->left->color == Color::Black) &&
          (sibling->right == nullptr ||
           sibling->right->color == Color::Black)) {
        sibling->color = Color::Red;
        node = node->parent;
      } else {
        // Case 3: Sibling's left child is black
        if (sibling->left == nullptr || sibling->left->color == Color::Black) {
          sibling->right->color = Color::Black;
          sibling->color = Color::Red;
          LeftRotate(sibling);
          sibling = node->parent->left;
        }
        // Case 4: Sibling's left child is red
        sibling->color = node->parent->color;
        node->parent->color = Color::Black;
        sibling->left->color = Color::Black;
        RightRotate(node->parent);
        node = root_;
      }
    }
  }
  // Set root to black
  node->color = Color::Black;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_CONTAINERS_RBTREE_H_
