#include <iostream>
#include <iterator>
#include <stack>
#include <vector>
#include <map>
#include <set>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator_traits.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include "map.hpp"


template <typename _Val>
void printTree1(ft::_RB_tree_node<_Val> *N, int level) {
  if (!N) return;
  printTree1(N->left, level + 1);
  N->print(level);
  printTree1(N->right, level + 1);
}

template <typename _Val>
void printTree(ft::_RB_tree_node<_Val> *T) {
  if (T == NULL) return;
  printTree1(T->left, 1);
  T->print(0);
  printTree1(T->right, 1);
}

struct value {
  int x;
  value(int x = 0) : x(x) {}
  int get() const { return x; }
};

int main() {
 ft::map<int, int> a;
//  auto b = ft::pair<int, int>(1, 1);
//   a.insert(b);
  a.insert(ft::pair<int, int>(1, 6));
  a.insert(ft::pair<int, int>(3, 4));
  a.insert(ft::pair<int, int>(5, 8));
  a.insert(ft::pair<int, int>(7, 10));
  a.insert(ft::pair<int, int>(9, 12));
  a.insert(ft::pair<int, int>(11, 12));
  // b = ft::pair<int, int>(-111, 12);
  // auto it = a.find(4);
  // a.insert(it, b);

  ft::map<int, int>::iterator it;
  for (it = a.begin(); it != a.end(); ++it) {
      std::cout << it->first << std::endl;
  }
  std::cout << "end" << std::endl;
  std::cout << a.lower_bound(4)->first << std::endl;
  std::cout << a.upper_bound(9)->first << std::endl;

  a.erase(a.find(5));
  for (it = a.begin(); it != a.end(); ++it) {
      std::cout << "[" << it->first << std::endl;
  }
  std::cout << "/* message */" << std::endl;
  a.erase(a.find(7), a.end());
}
