#include "../set.hpp"
#include "timer.hpp"

int main() {
  ft::set<int> m;
  ft::set<int>::size_type size;
  ft::set<int>::iterator it;
  ft::set<int>::reverse_iterator rit;
  ft::set<int>::allocator_type alloc;
  ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> equal;
  ft::set<int>::key_compare key_c;
  ft::set<int>::value_compare value_c = m.value_comp();
  bool b;
  timer t;

  ft::set<int> temp;
  temp.insert(-1);
  temp.insert(-2);

  t.start();

  for (int i = 0; i < REPEAT; ++i) {
    ft::set<int> new_s(temp.begin(), temp.end());
  }
  t.record("CONST-1");

  for (int i = 0; i < REPEAT; ++i) {
    ft::set<int> new_s(temp);
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
    m.insert(i);
  }
  t.record("INSERT-1");
  for (int i = 0; i < REPEAT; ++i) {
    m.insert(m.end(), i + REPEAT);
  }
  t.record("INSERT-2");
  for (int i = 0; i < REPEAT; ++i) {
    m.insert(temp.begin(), temp.end());
  }
  t.record("INSERT-3");

  for (int i = 0; i < REPEAT; ++i) {
    m.erase(i);
  }
  t.record("ERASE-1");

  for (int i = 0; i < REPEAT; ++i) {
    m.erase(m.begin());
  }
  t.record("ERASE-2");

  for (int i = 0; i < 1; ++i) {
    m.erase(m.begin(), m.end());
  }
  t.record("ERASE-3");

  // reinsert for test
  for (int i = 0; i < REPEAT; ++i) {
    m.insert(i);
  }
  t.start();

  for (int i = 0; i < REPEAT; ++i) {
    m.swap(temp);
  }
  t.record("SWAP");

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
