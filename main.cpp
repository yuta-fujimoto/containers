#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <unistd.h>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator_traits.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "vector.hpp"
#include "set.hpp"

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

#define REPEAT 1

void ft_vector_insert()
{
  ft::vector<int> test;

  for (size_t i = 0; i < REPEAT; ++i)
    test.push_back(i);
}


void std_vector_insert()
{
  std::vector<int> test;

  for (size_t i = 0; i < REPEAT; ++i)
    test.push_back(i);

}

// void hello_sleep()
// {
//   usleep(1000000);
// }

int main() {
  ft_vector_insert();
  std_vector_insert();
  // hello_sleep();
  return (0);
}
