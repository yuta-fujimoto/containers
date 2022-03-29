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

  ft::map<int, int>::reverse_iterator it;
  for (it = a.rbegin(); it != a.rend(); ++it)
  {
      std::cout << it->first << std::endl;
      // std::cout << it._M_node->_M_color << std::endl;
  }
  std::cout << "end" << std::endl;
  std::cout << a.lower_bound(4)->first << std::endl;
  std::cout << a.upper_bound(9)->first << std::endl;

  auto c = a.equal_range(3);
  std::cout << (c.first)->first << std::endl;
  std::cout << (c.second)->first << std::endl;
}
