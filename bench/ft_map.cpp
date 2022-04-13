#include "../map.hpp"
#include "timer.hpp"

int main() {
  int a;
  ft::map<int, int> m;
  ft::map<int, int>::size_type size;
  ft::map<int, int>::iterator it;
  ft::map<int, int>::reverse_iterator rit;
  ft::map<int, int>::allocator_type alloc;
  ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> equal;
  ft::map<int, int>::key_compare key_c;
  ft::map<int, int>::value_compare value_c = m.value_comp();
  bool b;
  timer t;

  ft::map<int, int> temp;
  temp.insert(ft::make_pair(1, 1));
  temp.insert(ft::make_pair(2, 2));

  //   ft::vector<int> temp_v;
  //   temp_v.push_back(1);
  //   temp_v.push_back(2);

  t.start();

  for (int i = 0; i < REPEAT; ++i) {
    ft::map<int, int> new_s(temp.begin(), temp.end());
  }
  t.record("CONST-1");

  for (int i = 0; i < REPEAT; ++i) {
    ft::map<int, int> new_s(temp);
  }
  t.record("CONST-2");

  for (int i = 0; i < REPEAT; ++i) {
    m = temp;
  }
  t.record("=");

  for (int i = 0; i < REPEAT; ++i) {
    alloc = m.get_allocator();
  }
  t.record("GETALLOCATOR");
  for (int i = 0; i < REPEAT; ++i) {
    it = m.begin();
  }
  t.record("BEGIN");
  for (int i = 0; i < REPEAT; ++i) {
    it = m.end();
  }
  t.record("END");
  for (int i = 0; i < REPEAT; ++i) {
    rit = m.rbegin();
  }
  t.record("RBEGIN");
  for (int i = 0; i < REPEAT; ++i) {
    rit = m.rend();
  }
  t.record("REND");
  for (int i = 0; i < REPEAT; ++i) {
    b = m.empty();
  }
  t.record("EMPTY");
  for (int i = 0; i < REPEAT; ++i) {
    size = m.size();
  }
  t.record("SIZE");
  for (int i = 0; i < REPEAT; ++i) {
    size = m.max_size();
  }
  t.record("MAX_SIZE");
  for (int i = 0; i < REPEAT; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  t.record("INSERT");
  for (int i = 0; i < REPEAT; ++i) {
    m.erase(i);
  }
  t.record("ERASE");

  for (int i = 0; i < REPEAT; ++i) {
    m.insert(ft::make_pair(i, i));
  }
  t.start();

  for (int i = 0; i < REPEAT; ++i) {
    m.swap(temp);
  }
  t.record("SWAP");

  for (int i = 0; i < REPEAT; ++i) {
    a = m[i];
  }
  t.record("[]");

  for (int i = 0; i < REPEAT; ++i) {
    a = m.at(i);
  }
  t.record("AT");

  for (int i = 0; i < REPEAT; ++i) {
    it = m.find(i);
  }
  t.record("FIND");

  for (int i = 0; i < REPEAT; ++i) {
    equal = m.equal_range(i);
  }
  t.record("EQUAL_RANGE");
  for (int i = 0; i < REPEAT; ++i) {
    it = m.lower_bound(i);
  }
  t.record("LOWER_BOUND");
  for (int i = 0; i < REPEAT; ++i) {
    it = m.upper_bound(i);
  }
  t.record("UPPER_BOUND");
  for (int i = 0; i < REPEAT; ++i) {
    key_c = m.key_comp();
  }
  t.record("KEY_COMP");

  for (int i = 0; i < REPEAT; ++i) {
    value_c = m.value_comp();
  }
  t.record("VALUE_COMP");

  for (int i = 0; i < REPEAT; ++i) {
    b = (temp == m);
  }
  t.record("COMP");

  for (int i = 0; i < 1; ++i) {
    m.clear();
  }
  t.record("CLEAR");


}
