#ifndef CPP2_S21_CONTAINERS_2_CONTAINERS_NODETREE_H_
#define CPP2_S21_CONTAINERS_2_CONTAINERS_NODETREE_H_

namespace s21 {

enum class Color { Red, Black };

template <class Key, class Value>
class Node {
 public:
  Key key;                   // Node key
  Value value;               // Node value
  Node<Key, Value> *left;    // Left child pointer
  Node<Key, Value> *right;   // Right child pointer
  Node<Key, Value> *parent;  // Parent pointer
  Color color;               // Node color (Red or Black)

  bool operator>(const Key &val) const { return this->key > val; }
  bool operator>=(const Key &val) const { return this->key >= val; }

  Node(const Key &key, const Value &value)
      : key(key),
        value(value),
        left(nullptr),
        right(nullptr),
        parent(nullptr),
        color(Color::Red) {}  // Default color is Red
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_2_CONTAINERS_NODETREE_H_