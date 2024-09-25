#include "containers/s21_map.h"

// Visualisation of Red Black Tree
// https://www.cs.usfca.edu/~galles/visualization/RedBlack.html

using namespace s21;

// Function to pretty-print the tree
template <typename Key, typename Value>
void prettyPrint(Node<Key, Value> *node, const std::string &prefix = "",
                 bool isLeft = true) {
  if (node != nullptr) {
    std::cout << prefix;
    std::cout << (isLeft ? "\033[31m├──\033[0m" : "\033[32m└──\033[0m");
    std::cout << node->key << " ("
              << (node->color == Color::Red ? "\033[31mRed\033[0m"
                                            : "\033[32mBlack\033[0m")
              << ")" << std::endl;
    prettyPrint(node->left, prefix + (isLeft ? "\033[34m│   \033[0m" : " "),
                true);
    prettyPrint(node->right, prefix + (isLeft ? "\033[34m│   \033[0m" : " "),
                false);
  }
}

int main(void) {
  Map<int, std::string> tree;
  std::pair<int, std::string> nodes[] = {
      {10, "ten"},  {5, "five"},      {15, "fifteen"}, {3, "three"},
      {7, "seven"}, {13, "thirteen"}, {20, "twenty"},  {1, "one"},
      {4, "four"},  {6, "six"}};
  int nodesLength = sizeof(nodes) / sizeof(nodes[0]);
  for (int i{}; i < nodesLength; i++) {
    tree.Insert(nodes[i].first, nodes[i].second);
  }

  std::cout << "Initial tree:" << std::endl;
  prettyPrint(tree.GetRoot());

  //  Remove node
  tree.Erase(tree.Find(tree.GetRoot(), 20));

  std::cout << std::endl << "Tree after removing red child 20:" << std::endl;
  prettyPrint(tree.GetRoot());

  tree.Erase(tree.Find(tree.GetRoot(), 5));
  tree.Erase(tree.Find(tree.GetRoot(), 15));

  std::cout << std::endl << "Tree after removing 5, 15:" << std::endl;
  prettyPrint(tree.GetRoot());

  // Remove nodes from the tree
  tree.Erase(tree.Find(tree.GetRoot(), 13));
  std::cout << std::endl
            << "Tree after erasing the Black node 13: (Double Black situation)"
            << std::endl;

  prettyPrint(tree.GetRoot());

  tree.Erase(tree.Find(tree.GetRoot(), 4));
  std::cout << std::endl << "Tree after erasing the root:" << std::endl;
  prettyPrint(tree.GetRoot());

  return 0;
}