#include "set.hpp"

#include <set>

#include "test_common.hpp"

template <typename _Tp>
void set_check_all_value(ft::set<_Tp>& ft_s, std::set<_Tp>& s) {
  CHECK_EQ(ft_s.size(), s.size());
  CHECK_EQ(ft_s.empty(), s.empty());

  std::size_t size = ft_s.size();

  typename std::set<_Tp>::iterator s_it = s.begin();
  typename ft::set<_Tp>::iterator ft_s_it = ft_s.begin();
  for (std::size_t i = 0; i < size; i++, ++ft_s_it, ++s_it) {
    CHECK_EQ(*s_it, *ft_s_it);
    CHECK_EQ(*s_it, *ft_s_it);
  }
}

TEST_CASE("SET") {
  TITLE("SET");
  SUBTITLE("SIZE");
  SUBTITLE("EMPTY");

  typedef std::string Key;
  ft::set<Key> ft_test;
  std::set<Key> test;

  ft::pair<ft::set<Key>::iterator, ft::set<Key>::iterator> ft_p;
  std::pair<std::set<Key>::iterator, std::set<Key>::iterator> p;
  ft::pair<ft::set<Key>::const_iterator, ft::set<Key>::const_iterator> ft_cp;
  std::pair<std::set<Key>::const_iterator, std::set<Key>::const_iterator> cp;
  ft::set<Key>::iterator ft_it;
  std::set<Key>::iterator it;
  ft::set<Key>::const_iterator ft_cit;
  std::set<Key>::const_iterator cit;

  std::string a("A");

  SUBTITLE("INSERT");

  ft::pair<ft::set<Key>::iterator, bool> ft_ins_pair = ft_test.insert(a);
  std::pair<std::set<Key>::iterator, bool> ins_pair = test.insert(a);
  CHECK_EQ(*ft_ins_pair.first, *ins_pair.first);
  CHECK_EQ(ft_ins_pair.second, ins_pair.second);

  // same value
  ft_ins_pair = ft_test.insert(a);
  ins_pair = test.insert(a);
  CHECK_EQ(*ft_ins_pair.first, *ins_pair.first);
  CHECK_EQ(ft_ins_pair.second, ins_pair.second);

  set_check_all_value(ft_test, test);

  SUBTITLE("INSERT WITH HINT");
  std::string A("A");
  std::string c("c");
  std::string d("d");

  ft_test.insert(ft_test.begin(), A);
  test.insert(test.begin(), A);

  ft_test.insert(ft_test.end(), c);
  test.insert(test.end(), c);

  // already inserted
  ft_test.insert(ft_test.end(), a);
  test.insert(test.end(), a);

  // invalid hint
  ft_test.insert(ft_test.begin(), A);
  test.insert(test.begin(), A);

  set_check_all_value(ft_test, test);

  SUBTITLE("INSERT WITH RANGE");
  std::set<Key> range;
  ft::set<Key> ft_range;

  std::string b("b");
  range.insert(b);
  ft_range.insert(b);

  test.insert(range.begin(), range.end());
  ft_test.insert(ft_range.begin(), ft_range.end());
  set_check_all_value(ft_test, test);

  SUBTITLE("FIND");
  Key no("no");

  ft_it = ft_test.find(a);
  it = test.find(a);
  CHECK_EQ(*ft_it, *it);

  // not found(return end)
  ft_it = ft_test.find(no);
  it = test.find(no);
  CHECK(it == test.end());
  CHECK(ft_it == ft_test.end());

  SUBTITLE("COUNT");

  CHECK_EQ(ft_test.count(a), test.count(a));
  CHECK_EQ(ft_test.count(no), test.count(no));

  SUBTITLE("EQUAL RANGE");
  ft_p = ft_test.equal_range(a);
  p = test.equal_range(a);
  CHECK_EQ(*ft_p.first, *p.first);
  CHECK_EQ(*ft_p.second, *p.second);

  ft_p = ft_test.equal_range(no);
  p = test.equal_range(no);
  CHECK(ft_p.first == ft_test.end());
  CHECK(p.first == test.end());
  CHECK(ft_p.second == ft_test.end());
  CHECK(p.second == test.end());

  // const
  ft_cp = ft_test.equal_range(a);
  cp = test.equal_range(a);
  CHECK_EQ(*ft_cp.first, *cp.first);
  CHECK_EQ(*ft_cp.second, *cp.second);

  SUBTITLE("LOWER BOUND");
  ft_it = ft_test.lower_bound(a);
  it = test.lower_bound(a);
  CHECK_EQ(*ft_it, *it);

  ft_it = ft_test.lower_bound(no);
  it = test.lower_bound(no);
  CHECK(ft_it == ft_test.end());
  CHECK(it == test.end());

  // const
  ft_cit = ft_test.lower_bound(a);
  cit = test.lower_bound(a);
  CHECK_EQ(*ft_cit, *cit);

  SUBTITLE("UPPER BOUND");
  ft_it = ft_test.upper_bound(a);
  it = test.upper_bound(a);
  CHECK_EQ(*ft_it, *it);

  ft_it = ft_test.upper_bound(no);
  it = test.upper_bound(no);
  CHECK(ft_it == ft_test.end());
  CHECK(it == test.end());

  // const
  ft_cit = ft_test.upper_bound(a);
  cit = test.upper_bound(a);
  CHECK_EQ(*ft_cit, *cit);

  SUBTITLE("SWAP");
  std::set<Key> swaped;
  ft::set<Key> ft_swaped;

  swaped.swap(test);
  ft_swaped.swap(ft_test);

  set_check_all_value(ft_swaped, swaped);
  set_check_all_value(ft_test, test);

  test.swap(swaped);
  ft_test.swap(ft_swaped);

  SUBTITLE("ERASE");
  std::size_t ft_erase_cnt;
  std::size_t erase_cnt;

  // no return value
  ft_test.erase(ft_test.begin());
  test.erase(test.begin());

  ft_erase_cnt = ft_test.erase(b);
  erase_cnt = test.erase(b);
  CHECK_EQ(ft_erase_cnt, erase_cnt);

  ft_erase_cnt = ft_test.erase(b);
  erase_cnt = test.erase(b);
  CHECK_EQ(ft_erase_cnt, erase_cnt);

  ft_test.erase(ft_test.find(d), ft_test.end());
  test.erase(test.find(d), test.end());

  set_check_all_value(ft_test, test);

  SUBTITLE("CLEAR");
  ft_test.clear();
  test.clear();

  set_check_all_value(ft_test, test);

  SUBTITLE("MAX SIZE");
  ft::set<char, char> ft_charchar;
  std::set<char, char> charchar;
  
  ft::set<char, const char*> ft_charcchar;
  std::set<char, const char*> charcchar;
  
  ft::set<double, char> ft_doublechar;
  std::set<double, char> doublechar;
  
  ft::set<int, char> ft_intchar;
  std::set<int, char> intchar;
  
  CHECK_EQ(ft_charchar.max_size(), charchar.max_size());
  CHECK_EQ(ft_charcchar.max_size(), charcchar.max_size());
  CHECK_EQ(ft_intchar.max_size(), intchar.max_size());
  CHECK_EQ(ft_doublechar.max_size(), doublechar.max_size());
  CHECK_EQ(ft_test.max_size(), test.max_size());

  SUBTITLE("VALUE COMP");
  std::set<Key>::key_compare comp = test.key_comp();
  ft::set<Key>::key_compare ft_comp = ft_test.key_comp();
  std::string s1("HELLO");
  std::string s2("FELLO");

  CHECK_EQ(comp(s1, s2), ft_comp(s1, s2));
  CHECK_EQ(comp(s2, s1), ft_comp(s2, s1));

  std::set<Key>::value_compare val_comp = test.value_comp();
  ft::set<Key>::value_compare ft_val_comp = ft_test.value_comp();

  CHECK_EQ(val_comp(s1, s2), ft_val_comp(s1, s2));
  CHECK_EQ(val_comp(s2, s1), ft_val_comp(s2, s1));

  SUBTITLE("GET ALLOCATOR");
  std::set<int> s_int;
  ft::set<int> ft_s_int;

  int* pointer = s_int.get_allocator().allocate(2);
  int* ft_pointer = ft_s_int.get_allocator().allocate(2);

  pointer[0] = 100;
  pointer[1] = 200;
  ft_pointer[0] = 100;
  ft_pointer[1] = 200;

  CHECK_EQ(pointer[0], ft_pointer[0]);
  CHECK_EQ(pointer[1], ft_pointer[1]);

  s_int.get_allocator().deallocate(pointer, 2);
  ft_s_int.get_allocator().deallocate(ft_pointer, 2);

  SUBTITLE("COMPARISON OPERATOR");
  std::set<int> c1;
  std::set<int> c2;
  ft::set<int> ft_c1;
  ft::set<int> ft_c2;

  c1.insert(1);
  ft_c1.insert(1);

  c2.insert(2);
  ft_c2.insert(2);

  CHECK_EQ((c1 == c2), (ft_c1 == ft_c2));
  CHECK_EQ((c1 != c2), (ft_c1 != ft_c2));
  CHECK_EQ((c1 < c2), (ft_c1 < ft_c2));
  CHECK_EQ((c1 <= c2), (ft_c1 <= ft_c2));
  CHECK_EQ((c1 > c2), (ft_c1 > ft_c2));
  CHECK_EQ((c1 >= c2), (ft_c1 >= ft_c2));

  SUBTITLE("CONSTRUCTOR");
  ft::set<int> ft_con(ft_c1);
  std::set<int> con(c1);

  set_check_all_value(ft_con, con);

  ft::set<int, std::greater<int> > ft_con2(ft_c1.begin(), ft_c1.end());
  std::set<int, std::greater<int> > con2(c1.begin(), c1.end());

  con2.insert(0);
  ft_con2.insert(0);

  CHECK_EQ(*ft_con2.begin(), *con2.begin());
  CHECK_EQ(*(++ft_con2.begin()), *(++con2.begin()));

  SUBTITLE("ASSIGNATION OPERATOR");
  ft::set<int, std::greater<int> > ft_assign;
  std::set<int, std::greater<int> > assign;

  ft_assign = ft_con2;
  assign = con2;

  // check if assign is deep
  // [TODO]
  // *ft_con2.find(0) = 3;
  // *con2.find(0) = 3;
  CHECK_EQ(*ft_assign.begin(), *assign.begin());
  CHECK_EQ(*(++ft_assign.begin()), *(++assign.begin()));
}
