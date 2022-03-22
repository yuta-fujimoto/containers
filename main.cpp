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

// 範囲の合計値を計算する
template <class Iterator>
typename ft::iterator_traits<Iterator>::value_type sum(Iterator first,
                                                       Iterator last) {
  // イテレータの型から値型を取得する
  typedef typename ft::iterator_traits<Iterator>::value_type value_type;

  // 取得した値型の変数を定義し、合計値を計算する
  value_type result = value_type();
  for (; first != last; ++first) {
    result += *first;
  }
  return result;
}

template <typename T>
void iter(const T& array, std::size_t len) {
  std::size_t i;

  i = 0;
  while (i < len) std::cout << array[i++] << std::endl;
  ;
}

struct value {
  int x;
  value(int x = 0) : x(x) {}
  int get() const { return x; }
};

int main() {
 std::map<int, int> a;
 auto b = std::pair<int, int>(1, 1);
  a.insert(b);
  a.insert(std::pair<int, int>(3, 6));
  a.insert(std::pair<int, int>(2, 4));
  a.insert(std::pair<int, int>(4, 8));
  a.insert(std::pair<int, int>(5, 10));
  a.insert(std::pair<int, int>(4, 12));

  for (std::map<int, int>::iterator it = a.begin(); it != a.end(); ++it)
  {
      std::cout << it->second << std::endl;
      // std::cout << it._M_node->_M_color << std::endl;
  }
}
