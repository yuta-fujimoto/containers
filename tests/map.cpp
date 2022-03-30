#include "../map.hpp"
#include <map>
#include "test_common.hpp"

template <typename T, typename U>
void check_all_value(ft::map<T, U>& ft_m, std::map<T, U>& m) {
  CHECK_EQ(ft_m.size(), m.size());

  std::size_t s = ft_m.size();

  typename std::map<T, U>::iterator m_it = m.begin();
  typename ft::map<T, U>::iterator ft_m_it = ft_m.begin();
  for (std::size_t i = 0; i < s; i++) {
    INFO(i);
    CHECK_EQ(m_it->first, ft_m_it->first);
    CHECK_EQ(m_it->second, ft_m_it->second);
  }
}

TEST_CASE("MAP") {
  ft::map<double, double> ft_test;
  std::map<double, double> test;

  ft_test.insert(ft::make_pair(1.0, 1.0));
  test.insert(std::make_pair(1.0, 1.0));
  check_all_value(ft_test, test);
}
