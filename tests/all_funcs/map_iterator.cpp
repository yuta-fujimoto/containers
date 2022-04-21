#include <map>

#include "map.hpp"
#include "test_common.hpp"

#define MAP_SIZE 5

TEST_CASE("MAP ITERATOR") {
  std::map<int, int> test;
  ft::map<int, int> ft_test;

  for (int i = 0; i < MAP_SIZE; ++i) {
    test.insert(std::make_pair(i, i * 2));
    ft_test.insert(ft::make_pair(i, i * 2));
  }

  std::map<int, int>::const_iterator cit = test.begin();
  ft::map<int, int>::const_iterator ft_cit = ft_test.begin();

  for (; ft_cit != ft_test.end(); ++cit, ++ft_cit) {
    CHECK_EQ(ft_cit->first, cit->first);
    CHECK_EQ(ft_cit->second, cit->second);
  }

  std::map<int, int>::reverse_iterator rit = test.rbegin();
  ft::map<int, int>::reverse_iterator ft_rit = ft_test.rbegin();

  for (; ft_rit != ft_test.rend(); ++rit, ++ft_rit) {
    CHECK_EQ(ft_rit->first, rit->first);
    CHECK_EQ(ft_rit->second, rit->second);
  }

  std::map<int, int>::const_reverse_iterator crit = test.rbegin();
  ft::map<int, int>::const_reverse_iterator ft_crit = ft_test.rbegin();

  for (; ft_crit != ft_test.rend(); ++crit, ++ft_crit) {
    CHECK_EQ(ft_crit->first, crit->first);
    CHECK_EQ(ft_crit->second, crit->second);
  }
}
