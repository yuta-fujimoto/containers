#include "../_Rb_tree.hpp"
// #include "rb_tree_test.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

template <typename _Val>
void printTree1(ft::_RB_tree_node<_Val> *N, int level) {
  if (!N) return;
  printTree1(N->left, level + 1);
  N->print(level);
  printTree1(N->right, level + 1);
}

template <typename _Val>
int checkTree1(ft::_RB_tree_node<_Val> *N, int len) {
  int ldep;
  int rdep;

  if (!N) return (len + 1);
  if (N->color == ft::RED) {
    if ((N->left == NIL || N->left->color == ft::BLACK) &&
        (N->right == NIL || N->right->color == ft::BLACK)) {
      ldep = checkTree1(N->left, len);
      rdep = checkTree1(N->right, len);
      if (ldep != -1 && rdep == ldep) return (ldep);
      std::cout << "CURRENT: " << N->getKey() << " LEFT: " << ldep
                << " RIGHT: " << rdep << std::endl;
    }
    printTree1(N, 0);
    return (-1);
  }
  ldep = checkTree1(N->left, len + 1);
  rdep = checkTree1(N->right, len + 1);
  if (ldep != -1 && rdep == ldep) return (ldep);
  std::cout << "CURRENT: " << N->getKey() << " LEFT: " << ldep
            << " RIGHT: " << rdep << std::endl;
  printTree1(N, 0);
  return (-1);
}

template <typename _Val>
void printTree(ft::_RB_tree_node<_Val> *T) {
  if (T == NIL) return;
  printTree1(T->left, 1);
  T->print(0);
  printTree1(T->right, 1);
}

template <typename _Val>
bool checkTree(ft::_RB_tree_node<_Val> *T) {
  int dep = checkTree1(T, 0);

  if (dep == -1)
    std::cout << "ERROR!" << std::endl;
  else
    std::cout << "SUCCESS: " << dep << std::endl;
  return (dep != -1);
}

int main() {
  srand(time(NULL));
  std::ofstream ofs("Rb_tree.txt");
  // comment for debug
  std::vector<int> a = {};
  std::vector<int> b = {};

  // [RANDOM TEST]
  // std::vector<int> a;
  // std::vector<int> b;
  // int repeat = 100;
  // for (int i = 0; i < repeat; i++) a.push_back(rand() % repeat);
  // for (int i = 0; i < repeat; i++) b.push_back(rand() % repeat);
  ft::_Rb_tree<int, ft::pair<int, int>, std::less<int> > T;

  for (auto i : a) {
    ofs << i << ", ";
    T._Rb_insert(ft::pair<int, int>(i, i));
  }
  ofs << std::endl;
  if (!checkTree(T._M_root())) {
    return (0);
  }
  for (auto i : b) {
    T._Rb_erase(i);
  }
  ofs << std::endl;
  if (!checkTree(T._M_root())) {
    return (0);
  }
  T._Rb_clear();
  printTree(T._M_root());  // noting would be printed

  // [EMPTY TEST]
  T._Rb_insert(ft::pair<int, int>(1, 2));
  T._Rb_insert(ft::pair<int, int>(2, 2));
  T._Rb_insert(ft::pair<int, int>(3, 2));
  T._Rb_insert(ft::pair<int, int>(4, 2));
  T._Rb_erase(2);
  T._Rb_erase(3);
  T._Rb_erase(4);
  T._Rb_erase(1);
  printTree(T._M_root());  // noting would be printed

  // in coverage test, Case_D2 doesn't be passed, but(TODO)
  ft::_Rb_tree_iterator<ft::pair<int, int>> it;
  int i = 0;
  int check_size = 10;
  for (i = 0; i < check_size; ++i) {
    T._Rb_insert(ft::pair<int, int>(i, i));
  }
  i = 0;
  for (it = T.begin(); it != T.end(); ++it) {
    if (it->first != i)
      std::cout << "[ERROR(++)] WANT: " << i << " GOT: " << it->first
                << std::endl;
    i++;
  }
  if (check_size != i) {
    std::cout << "ERROR(++): " << i << std::endl;
    return (0);
  }
  for (it = T.end(); it != T.begin();) {
    --it;
    i--;
    if (it->first != i)
      std::cout << "[ERROR(--)] WANT: " << i << " GOT: " << it->first
                << std::endl;
  }
  if (i != 0) {
    std::cout << "ERROR(--): " << i << std::endl;
    return (0);
  }
  // ERROR
  // it->first = 12;
}
