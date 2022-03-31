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
  typedef double Key;
  typedef std::string Value;

  ft::map<Key, Value> ft_test;
  std::map<Key, Value> test;
  ft::pair<ft::map<Key, Value>::iterator, ft::map<Key, Value>::iterator>
      ft_p;
  std::pair<std::map<Key, Value>::iterator,
            std::map<Key, Value>::iterator>
      p;
  ft::pair<ft::map<Key, Value>::const_iterator,
           ft::map<Key, Value>::const_iterator>
      ft_cp;
  std::pair<std::map<Key, Value>::const_iterator,
            std::map<Key, Value>::const_iterator>
      cp;
  ft::map<Key, Value>::iterator ft_it;
  std::map<Key, Value>::iterator it;
  ft::map<Key, Value>::const_iterator ft_cit;
  std::map<Key, Value>::const_iterator cit;

  std::string a("A");
  ft_test.insert(ft::make_pair(0.0, a));
  test.insert(std::make_pair(0.0, a));

  std::string b("B");
  ft_test.insert(ft::make_pair(1.0, b));
  test.insert(std::make_pair(1.0, b));

  std::string c("C");
  ft_test.insert(ft::make_pair(2.0, c));
  test.insert(std::make_pair(2.0, c));

  // SAME VALUE
  std::string d("D");
  ft_test.insert(ft::make_pair(1.0, d));
  test.insert(std::make_pair(1.0, d));

  CHECK_EQ(ft_test.max_size(), test.max_size());

  check_all_value(ft_test, test);

  ft_it = ft_test.find(1.0);
  it = test.find(1.0);
  ft_cit = ft_test.find(1.0);
  cit = test.find(1.0);
  CHECK_EQ(ft_it->first, it->first);
  CHECK_EQ(ft_it->second, it->second);
  CHECK_EQ(ft_cit->first, cit->first);
  CHECK_EQ(ft_cit->second, cit->second);

  CHECK_EQ(ft_test.count(1.0), test.count(1.0));
  CHECK_EQ(ft_test.count(0.0), test.count(0.0));

  ft_p = ft_test.equal_range(1.0);
  p = test.equal_range(1.0);
  CHECK_EQ(ft_p.first->first, p.first->first);
  CHECK_EQ(ft_p.first->second, p.first->second);
  CHECK_EQ(ft_p.second->first, p.second->first);
  CHECK_EQ(ft_p.second->second, p.second->second);

  ft_p = ft_test.equal_range(1.1);
  p = test.equal_range(1.1);
  CHECK_EQ(ft_p.first->first, p.first->first);
  CHECK_EQ(ft_p.first->second, p.first->second);
  CHECK_EQ(ft_p.second->first, p.second->first);
  CHECK_EQ(ft_p.second->second, p.second->second);

  ft_cp = ft_test.equal_range(1.1);
  cp = test.equal_range(1.1);
  CHECK_EQ(ft_cp.first->first, cp.first->first);
  CHECK_EQ(ft_cp.first->second, cp.first->second);
  CHECK_EQ(ft_cp.second->first, cp.second->first);
  CHECK_EQ(ft_cp.second->second, cp.second->second);

  ft_it = ft_test.lower_bound(1.0);
  it = test.lower_bound(1.0);
  CHECK_EQ(ft_it->first, it->first);
  CHECK_EQ(ft_it->second, it->second);
  CHECK_EQ(ft_cit->first, cit->first);
  CHECK_EQ(ft_cit->second, cit->second);

  ft_it = ft_test.lower_bound(1.1);
  it = test.lower_bound(1.1);
  CHECK_EQ(ft_p.first->first, p.first->first);
  CHECK_EQ(ft_p.first->second, p.first->second);
  CHECK_EQ(ft_p.second->first, p.second->first);
  CHECK_EQ(ft_p.second->second, p.second->second);

  ft_cit = ft_test.lower_bound(1.0);
  cit = test.lower_bound(1.0);
  CHECK_EQ(ft_p.first->first, p.first->first);
  CHECK_EQ(ft_p.first->second, p.first->second);
  CHECK_EQ(ft_p.second->first, p.second->first);
  CHECK_EQ(ft_p.second->second, p.second->second);

  ft_it = ft_test.upper_bound(1.0);
  it = test.upper_bound(1.0);
  CHECK_EQ(ft_it->first, it->first);
  CHECK_EQ(ft_it->second, it->second);
  CHECK_EQ(ft_cit->first, cit->first);
  CHECK_EQ(ft_cit->second, cit->second);

  ft_it = ft_test.upper_bound(1.1);
  it = test.upper_bound(1.1);
  CHECK_EQ(ft_p.first->first, p.first->first);
  CHECK_EQ(ft_p.first->second, p.first->second);
  CHECK_EQ(ft_p.second->first, p.second->first);
  CHECK_EQ(ft_p.second->second, p.second->second);

  ft_cit = ft_test.upper_bound(1.0);
  cit = test.upper_bound(1.0);
  CHECK_EQ(ft_p.first->first, p.first->first);
  CHECK_EQ(ft_p.first->second, p.first->second);
  CHECK_EQ(ft_p.second->first, p.second->first);
  CHECK_EQ(ft_p.second->second, p.second->second);

  ft_test.erase(ft_test.begin());
  test.erase(test.begin());

  std::size_t f;
  std::size_t s;

  f = ft_test.erase(0.0);
  s = test.erase(0.0);
  CHECK_EQ(f, s);

  f = ft_test.erase(0.0);
  s = test.erase(0.0);
  CHECK_EQ(f, s);

  ft_test.erase(ft_test.find(1.0), ft_test.end());
  test.erase(test.find(1.0), test.end());

  check_all_value(ft_test, test);
}
