#include "../map.hpp"

#include <map>

#include "test_common.hpp"

template <typename _Tp, typename U>
void map_check_all_value(ft::map<_Tp, U>& ft_m, std::map<_Tp, U>& m) {
  CHECK_EQ(ft_m.size(), m.size());
  CHECK_EQ(ft_m.empty(), m.empty());

  std::size_t s = ft_m.size();

  typename std::map<_Tp, U>::iterator m_it = m.begin();
  typename ft::map<_Tp, U>::iterator ft_m_it = ft_m.begin();
  for (std::size_t i = 0; i < s; i++, ++ft_m_it, ++m_it) {
    CHECK_EQ(m_it->first, ft_m_it->first);
    CHECK_EQ(m_it->second, ft_m_it->second);
  }
}

template <typename _Tp, typename U>
void print_all_value(ft::map<_Tp, U>& ft_m) {
  std::size_t s = ft_m.size();

  typename ft::map<_Tp, U>::iterator ft_m_it = ft_m.begin();
  for (std::size_t i = 0; i < s; i++, ++ft_m_it) {
    std::cout << ft_m_it->first << ": " << ft_m_it->second << std::endl;
  }
}

TEST_CASE("MAP") {
  TITLE("MAP");
  typedef double Key;
  typedef std::string Value;

  ft::map<Key, Value> ft_test;
  std::map<Key, Value> test;

  ft::pair<ft::map<Key, Value>::iterator, ft::map<Key, Value>::iterator> ft_p;
  std::pair<std::map<Key, Value>::iterator, std::map<Key, Value>::iterator> p;
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

  SUBTITLE("INSERT");
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

  std::string e("E");
  ft_test.insert(ft::make_pair(-1.0, e));
  test.insert(std::make_pair(-1.0, e));

  map_check_all_value(ft_test, test);

  SUBTITLE("INSERT WITH RANGE");
  std::map<Key, Value> range;
  ft::map<Key, Value> ft_range;

  range.insert(std::make_pair(4.0, e));
  ft_range.insert(ft::make_pair(4.0, e));

  range.insert(std::make_pair(3.0, e));
  ft_range.insert(ft::make_pair(3.0, e));

  test.insert(range.begin(), range.end());
  ft_test.insert(ft_range.begin(), ft_range.end());

  // compile error
  // ft_test.insert(100, 200);
  // test.insert(100, 200);

  map_check_all_value(ft_test, test);

  SUBTITLE("INSERT WITH HINT");
  std::map<double, int> ins_test;
  std::map<double, int>::iterator ins_it;
  ft::map<double, int> ft_ins_test;
  ft::map<double, int>::iterator ft_ins_it;

  ins_it = ins_test.insert(ins_test.begin(), std::make_pair(1.0, 1));
  ft_ins_it = ft_ins_test.insert(ft_ins_test.begin(), ft::make_pair(1.0, 1));
  CHECK_EQ(ins_it->first, ft_ins_it->first);
  CHECK_EQ(ins_it->second, ft_ins_it->second);

  // valid hint
  ins_it = ins_test.insert(ins_test.begin(), std::make_pair(0.0, 1));
  ft_ins_it = ft_ins_test.insert(ft_ins_test.begin(), ft::make_pair(0.0, 1));
  CHECK_EQ(ins_it->first, ft_ins_it->first);
  CHECK_EQ(ins_it->second, ft_ins_it->second);

  // valid hint
  ins_it = ins_test.insert(ins_test.find(1.0), std::make_pair(0.7, 1));
  ft_ins_it = ft_ins_test.insert(ft_ins_test.find(1.0), ft::make_pair(0.7, 1));
  CHECK_EQ(ins_it->first, ft_ins_it->first);
  CHECK_EQ(ins_it->second, ft_ins_it->second);

  // valid hint
  ins_it = ins_test.insert(ins_test.end(), std::make_pair(2.0, 1));
  ft_ins_it = ft_ins_test.insert(ft_ins_test.end(), ft::make_pair(2.0, 1));
  CHECK_EQ(ins_it->first, ft_ins_it->first);
  CHECK_EQ(ins_it->second, ft_ins_it->second);

  // valid hint
  ins_it = ins_test.insert(ins_test.begin(), std::make_pair(-2.0, -2));
  ft_ins_it = ft_ins_test.insert(ft_ins_test.begin(), ft::make_pair(-2.0, -2));
  CHECK_EQ(ins_it->first, ft_ins_it->first);
  CHECK_EQ(ins_it->second, ft_ins_it->second);

  // invalid hint
  ins_it = ins_test.insert(ins_test.end(), std::make_pair(-1.0, 1));
  ft_ins_it = ft_ins_test.insert(ft_ins_test.end(), ft::make_pair(-1.0, 1));
  CHECK_EQ(ins_it->first, ft_ins_it->first);
  CHECK_EQ(ins_it->second, ft_ins_it->second);

  map_check_all_value(ft_ins_test, ins_test);

  SUBTITLE("OPERATOR[]");

  Value ft_value;
  Value value;

  ft_value = ft_test[1.0];
  value = test[1.0];
  CHECK_EQ(ft_value, value);

  ft_value = ft_test[1.0];
  value = test[1.0];
  CHECK_EQ(ft_value, value);

  ft_value = ft_test[0.1];
  value = test[0.1];
  CHECK_EQ(ft_value, value);

  map_check_all_value(ft_test, test);

  SUBTITLE("AT");

  ft::map<Key, Value>::mapped_type ft_at = ft_test.at(0.1);
  std::map<Key, Value>::mapped_type at = test.at(0.1);

  CHECK_EQ(ft_at, at);

  try {
    ft_test.at(0.111);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
  try {
    test.at(0.111);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  SUBTITLE("FIND");
  ft_it = ft_test.find(1.0);
  it = test.find(1.0);
  ft_cit = ft_test.find(1.0);
  cit = test.find(1.0);

  CHECK_EQ(ft_it->first, it->first);
  CHECK_EQ(ft_it->second, it->second);
  CHECK_EQ(ft_cit->first, cit->first);
  CHECK_EQ(ft_cit->second, cit->second);

  SUBTITLE("COUNT");
  CHECK_EQ(ft_test.count(1.0), test.count(1.0));
  CHECK_EQ(ft_test.count(0.0), test.count(0.0));

  SUBTITLE("EQUAL RANGE");
  ft_p = ft_test.equal_range(-10.0);
  p = test.equal_range(-10.0);
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

  // const
  ft_cp = ft_test.equal_range(1.1);
  cp = test.equal_range(1.1);
  CHECK_EQ(ft_cp.first->first, cp.first->first);
  CHECK_EQ(ft_cp.first->second, cp.first->second);
  CHECK_EQ(ft_cp.second->first, cp.second->first);
  CHECK_EQ(ft_cp.second->second, cp.second->second);

  SUBTITLE("LOWER BOUND");
  ft_it = ft_test.lower_bound(1.0);
  it = test.lower_bound(1.0);
  CHECK_EQ(ft_it->first, it->first);
  CHECK_EQ(ft_it->second, it->second);

  ft_it = ft_test.lower_bound(1.1);
  it = test.lower_bound(1.1);
  CHECK_EQ(ft_it->first, it->first);
  CHECK_EQ(ft_it->second, it->second);

  ft_cit = ft_test.lower_bound(1.0);
  cit = test.lower_bound(1.0);
  CHECK_EQ(ft_cit->first, cit->first);
  CHECK_EQ(ft_cit->second, cit->second);

  SUBTITLE("UPPER BOUND");
  ft_it = ft_test.upper_bound(1.0);
  it = test.upper_bound(1.0);
  CHECK_EQ(ft_it->first, it->first);
  CHECK_EQ(ft_it->second, it->second);

  ft_it = ft_test.upper_bound(1.1);
  it = test.upper_bound(1.1);
  CHECK_EQ(ft_it->first, it->first);
  CHECK_EQ(ft_it->second, it->second);

  ft_cit = ft_test.upper_bound(1.0);
  cit = test.upper_bound(1.0);
  CHECK_EQ(ft_cit->first, cit->first);
  CHECK_EQ(ft_cit->second, cit->second);

  SUBTITLE("SWAP");
  std::map<Key, Value> swaped;
  ft::map<Key, Value> ft_swaped;

  swaped.swap(test);
  ft_swaped.swap(ft_test);

  map_check_all_value(ft_swaped, swaped);
  map_check_all_value(ft_test, test);

  // test.swap(swaped);
  // ft_test.swap(ft_swaped);
  std::swap(swaped, test);
  ft::swap(ft_swaped, ft_test);

  SUBTITLE("ERASE");
  std::size_t ft_erase_cnt;
  std::size_t erase_cnt;

  // no return value
  ft_test.erase(ft_test.begin());
  test.erase(test.begin());

  ft_erase_cnt = ft_test.erase(0.0);
  erase_cnt = test.erase(0.0);
  CHECK_EQ(ft_erase_cnt, erase_cnt);

  ft_erase_cnt = ft_test.erase(0.0);
  erase_cnt = test.erase(0.0);
  CHECK_EQ(ft_erase_cnt, erase_cnt);

  ft_test.erase(ft_test.find(1.0), ft_test.end());
  test.erase(test.find(1.0), test.end());

  map_check_all_value(ft_test, test);

  SUBTITLE("CLEAR");
  ft_test.clear();
  test.clear();

  map_check_all_value(ft_test, test);

  // SUBTITLE("MAX SIZE");
  // ft::map<char, char> ft_charchar;
  // std::map<char, char> charchar;

  // ft::map<char, const char*> ft_charcchar;
  // std::map<char, const char*> charcchar;

  // ft::map<double, char> ft_doublechar;
  // std::map<double, char> doublechar;

  // ft::map<int, char> ft_intchar;
  // std::map<int, char> intchar;

  // CHECK_EQ(ft_charchar.max_size(), charchar.max_size());
  // CHECK_EQ(ft_charcchar.max_size(), charcchar.max_size());
  // CHECK_EQ(ft_intchar.max_size(), intchar.max_size());
  // CHECK_EQ(ft_doublechar.max_size(), doublechar.max_size());
  // CHECK_EQ(ft_test.max_size(), test.max_size());

  SUBTITLE("VALUE COMP");
  std::map<Key, Value>::key_compare comp = test.key_comp();
  ft::map<Key, Value>::key_compare ft_comp = ft_test.key_comp();

  CHECK_EQ(comp(1, 2), ft_comp(1, 2));
  CHECK_EQ(comp(3, 2), ft_comp(3, 2));

  std::map<Key, Value>::value_compare val_comp = test.value_comp();
  ft::map<Key, Value>::value_compare ft_val_comp = ft_test.value_comp();

  std::string s1("HELLO");
  std::string s2("FELLO");
  CHECK_EQ(val_comp(std::make_pair(1.0, s1), std::make_pair(1.0, s2)),
           ft_val_comp(ft::make_pair(1.0, s1), ft::make_pair(1.0, s2)));
  CHECK_EQ(val_comp(std::make_pair(2.0, s1), std::make_pair(1.0, s2)),
           ft_val_comp(ft::make_pair(2.0, s1), ft::make_pair(1.0, s2)));
  CHECK_EQ(val_comp(std::make_pair(0.0, s1), std::make_pair(0.0, s2)),
           ft_val_comp(ft::make_pair(2.0, s1), ft::make_pair(1.0, s2)));

  SUBTITLE("GET ALLOCATOR");
  std::map<int, char> intchar;
  ft::map<int, char> ft_intchar;

  std::pair<const int, char>* pointer = intchar.get_allocator().allocate(2);
  ft::pair<const int, char>* ft_pointer =
      ft_intchar.get_allocator().allocate(2);

  pointer[0].second = 'a';
  pointer[1].second = '\0';
  ft_pointer[0].second = 'a';
  ft_pointer[1].second = '\0';

  CHECK_EQ(pointer->second, ft_pointer->second);

  intchar.get_allocator().deallocate(pointer, 2);
  ft_intchar.get_allocator().deallocate(ft_pointer, 2);

  SUBTITLE("COMPARISON OPERATOR");
  std::map<int, int> c1;
  std::map<int, int> c2;
  ft::map<int, int> ft_c1;
  ft::map<int, int> ft_c2;

  c1.insert(std::make_pair(1, 1));
  ft_c1.insert(ft::make_pair(1, 1));

  c2.insert(std::make_pair(0, 2));
  ft_c2.insert(ft::make_pair(0, 2));

  CHECK_EQ((c1 == c2), (ft_c1 == ft_c2));
  CHECK_EQ((c1 != c2), (ft_c1 != ft_c2));
  CHECK_EQ((c1 < c2), (ft_c1 < ft_c2));
  CHECK_EQ((c1 <= c2), (ft_c1 <= ft_c2));
  CHECK_EQ((c1 > c2), (ft_c1 > ft_c2));
  CHECK_EQ((c1 >= c2), (ft_c1 >= ft_c2));

  SUBTITLE("CONSTRUCTOR");
  ft::map<int, int> ft_con(ft_c1);
  std::map<int, int> con(c1);

  map_check_all_value(ft_con, con);

  ft::map<int, int, std::greater<int> > ft_con2(ft_c1.begin(), ft_c1.end());
  std::map<int, int, std::greater<int> > con2(c1.begin(), c1.end());

  con2.insert(std::make_pair(0, 2));
  ft_con2.insert(ft::make_pair(0, 2));

  CHECK_EQ(ft_con2.begin()->first, con2.begin()->first);
  CHECK_EQ((++ft_con2.begin())->first, (++con2.begin())->first);

  SUBTITLE("ASSIGNATION OPERATOR");
  ft::map<int, int, std::greater<int> > ft_assign;
  std::map<int, int, std::greater<int> > assign;

  ft_assign = ft_con2;
  assign = con2;

  ft_con2[0] = 3;
  con2[0] = 3;
  CHECK_EQ(ft_assign.begin()->first, assign.begin()->first);
  CHECK_EQ((++ft_assign.begin())->first, (++assign.begin())->first);
}
