#include <iostream>
#include <iterator>
#include <stack>
#include <vector>

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
  std::cout << "Constructor with initializer-list example:" << std::endl;
  std::cout << std::endl;

  std::cout << "=operator" << std::endl;
  ft::vector<int> data;
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);
  std::cout << data.size() << std::endl;
  std::cout << std::endl;

  std::vector<int> h1;
  std::vector<int> h2;

  h1.push_back(1);
  h1.push_back(2);
  h1.push_back(1);
  h2.push_back(1);  
  h2.push_back(3);
  h2.push_back(2);
  h2.push_back(1);
  std::cout << (h1 >= h2) << std::endl;
  std::cout << (h1 > h2) << std::endl;
  return 0;
}
