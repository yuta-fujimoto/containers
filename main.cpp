#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <stack>
#include <vector>

#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator_traits.hpp"
#include "map.hpp"
#include "pair.hpp"
#include "vector.hpp"

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
  ft::map<char, char> ft_charchar;
  std::map<char, char> charchar;

  ft::map<char, const char *> ft_charcchar;
  std::map<char, const char *> charcchar;

  ft::map<int, char> ft_intchar;
  std::map<int, char> intchar;

  ft::map<double, char> ft_doublechar;
  std::map<double, char> doublechar;

  ft::map<int, std::string> ft_intstring;
  std::map<int, std::string> intstring;

  ft::map<int, double> ft_test;
  std::map<int, double> test;

  std::cout << ft_charchar.max_size() << ":" << charchar.max_size()
            << "W: " << std::numeric_limits<size_type>::max() / charchar.max_size()
            << std::endl;
  std::cout << ft_charcchar.max_size() << ":" << charcchar.max_size()
            << "W: " << std::numeric_limits<size_type>::max() / charcchar.max_size()
            << std::endl;
  std::cout << ft_intchar.max_size() << ":" << intchar.max_size()
            << "W: " << std::numeric_limits<size_type>::max() / intchar.max_size()
            << std::endl;
  std::cout << ft_intstring.max_size() << ":" << intstring.max_size()
            << "W: " << std::numeric_limits<size_type>::max() / intstring.max_size()
            << std::endl;
  std::cout << ft_doublechar.max_size() << ":" << doublechar.max_size()
            << "W: " << std::numeric_limits<size_type>::max() / doublechar.max_size()
            << std::endl;
  std::cout << ft_test.max_size() << ":" << test.max_size()
            << "W: " << std::numeric_limits<size_type>::max() / test.max_size()
            << std::endl;


  std::cout << ft_test.max_size() << ":" << test.max_size()
            << "W: " << std::numeric_limits<size_type>::max() / test.max_size()
            << std::endl;
  std::cout << std::numeric_limits<size_type>::max() << std::endl;
}
