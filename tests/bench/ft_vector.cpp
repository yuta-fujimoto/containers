#include "vector.hpp"
#include "timer.hpp"

int main() {
  int a;
  ft::vector<int> v;
  ft::vector<int>::iterator it;
  ft::vector<int>::reverse_iterator rit;
  ft::vector<int>::size_type s;
  ft::vector<int>::reference r = a;
  bool b;
  timer t;

  ft::vector<int> temp;
  temp.push_back(1);
  temp.push_back(2);

  t.start();
  for (int i = 0; i < REPEAT; ++i) {
    ft::vector<int> new_v(temp.begin(), temp.end());
  }
  t.record("CONSTRUCT");

  for (int i = 0; i < REPEAT; ++i) {
    v = temp;
  }
  t.record("=");

  for (int i = 0; i < REPEAT; ++i) {
    it = v.begin();
  }
  t.record("BEGIN");
  for (int i = 0; i < REPEAT; ++i) {
    it = v.end();
  }
  t.record("END");
  for (int i = 0; i < REPEAT; ++i) {
    rit = v.rbegin();
  }
  t.record("RBEGIN");
  for (int i = 0; i < REPEAT; ++i) {
    rit = v.rend();
  }
  t.record("REND");

  for (int i = 0; i < REPEAT; ++i) {
    s = v.size();
  }
  t.record("SIZE");
  for (int i = 0; i < REPEAT; ++i) {
    s = v.max_size();
  }
  t.record("MAX_SIZE");
  for (int i = 0; i < REPEAT / 2; ++i) {
    v.resize(i);
  }
  for (int i = REPEAT / 2 - 1; i >= 0; --i) {
    v.resize(i);
  }
  t.record("RESIZE");

  for (int i = 0; i < REPEAT; ++i) {
    s = v.capacity();
  }
  t.record("CAPACITY");

  for (int i = 0; i < REPEAT; ++i) {
    b = v.empty();
  }
  t.record("EMPTY");

  for (int i = 0; i < REPEAT / 2; ++i) {
    v.resize(i);
  }
  for (int i = REPEAT / 2 - 1; i >= 0; --i) {
    v.resize(i);
  }
  t.record("RESERVE");

  v.push_back(1);
  t.start();
  for (int i = 0; i < REPEAT; ++i) {
    v[0];
  }
  t.record("[]");

  for (int i = 0; i < REPEAT; ++i) {
    r = v.front();
  }
  t.record("FRONT");

  for (int i = 0; i < REPEAT; ++i) {
    r = v.back();
  }
  t.record("BACK");

  for (int i = 0; i < REPEAT; ++i) {
    v.assign(temp.begin(), temp.end());
  }
  t.record("ASSIGN-1");

  for (int i = 0; i < REPEAT; ++i) {
    v.assign(i, i);
  }
  t.record("ASSIGN-2");

  for (int i = 0; i < REPEAT; ++i) {
    v.push_back(i);
  }
  t.record("PUSH_BACK");

  for (int i = 0; i < REPEAT; ++i) {
    v.pop_back();
  }
  t.record("POP_BACK");

  {
    ft::vector<std::string> v_str(1);
    ft::vector<std::string> temp_str;
    temp_str.push_back("HELLO");

    t.start();
    for (int i = 0; i < REPEAT; ++i) {
      v_str.insert(v_str.begin(), "HELLO");
    }
    t.record("INSERT-1-S");

    for (int i = 0; i < REPEAT; ++i) {
      v_str.insert(v_str.begin(), 5, "HELLO");
    }
    t.record("INSERT-2-S");
    for (int i = 0; i < REPEAT; ++i) {
      v_str.insert(v_str.begin(), temp_str.begin(), temp_str.end());
    }
    t.record("INSERT-3-S");
  }
  t.start();

  for (int i = 0; i < REPEAT; ++i) {
    v.insert(v.begin(), i);
  }
  t.record("INSERT-1");

  for (int i = 0; i < REPEAT; ++i) {
    v.insert(v.begin(), 5, i);
  }
  t.record("INSERT-2");
  for (int i = 0; i < REPEAT; ++i) {
    v.insert(v.begin(), temp.begin(), temp.end());
  }
  t.record("INSERT-3");

  for (int i = 0; i < REPEAT; ++i) {
    v.erase(v.end() - 1);
  }
  t.record("ERASE-1");
  for (int i = 0; i < REPEAT; ++i) {
    v.erase(v.end() - 1, v.end());
  }
  t.record("ERASE-2");

  for (int i = 0; i < REPEAT; ++i) {
    v.swap(temp);
  }
  t.record("SWAP");
  for (int i = 0; i < 1; ++i) {
    v.clear();
  }
  t.record("CLEAR");

  for (int i = 0; i < REPEAT; i++) {
    b = (v == temp);
  }
  t.record("COMPARE");
}
