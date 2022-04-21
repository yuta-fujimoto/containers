#include <set>
#include "set.hpp"
#include "test_common.hpp"

#define SET_SIZE 5

TEST_CASE("SET") {
  std::set<int> test;
  ft::set<int> ft_test;

  for (int i = 0; i < SET_SIZE; ++i) {
    test.insert(i);
    ft_test.insert(i);
  }

  std::set<int>::const_iterator cit = test.begin();
  ft::set<int>::const_iterator ft_cit = ft_test.begin();

  for (; ft_cit != ft_test.end(); ++cit, ++ft_cit) {
    CHECK_EQ(*ft_cit, *cit);
  }

  std::set<int>::reverse_iterator rit = test.rbegin();
  ft::set<int>::reverse_iterator ft_rit = ft_test.rbegin();

  // iterator is read-only
  //   *rit = 12;
  //   *ft_rit = 12;
  for (; ft_rit != ft_test.rend(); ++rit, ++ft_rit) {
    CHECK_EQ(*ft_rit, *rit);
  }

  std::set<int>::const_reverse_iterator crit = test.rbegin();
  ft::set<int>::const_reverse_iterator ft_crit = ft_test.rbegin();

  for (; ft_crit != ft_test.rend(); ++crit, ++ft_crit) {
    CHECK_EQ(*ft_crit, *crit);
  }
}
