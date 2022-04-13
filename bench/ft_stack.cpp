#include "../stack.hpp"
// #include "../vector.hpp"
#include "timer.hpp"

int main() { 
  int a;
  ft::stack<int> s;
  ft::stack<int>::size_type size;
  bool b;
  timer t;

  ft::stack<int> temp_s;
  temp_s.push(1);
  temp_s.push(2);

//   ft::vector<int> temp_v;
//   temp_v.push_back(1);
//   temp_v.push_back(2);

  t.start();
  for (int i = 0; i < REPEAT; ++i) {
    ft::stack<int> new_s(temp_s);
  }
  t.record("CONST-1");

//std's container inside stack is not vector...
//   for (int i = 0; i < REPEAT; ++i) {
//     ft::stack<int> new_s(temp_v);
//   }
//   t.record("CONST-2");

  for (int i = 0; i < REPEAT; ++i) {
    s = temp_s;
  }
  t.record("=");

  for (int i = 0; i < REPEAT; ++i) {
    a = s.top();
  }
  t.record("TOP");
  for (int i = 0; i < REPEAT; ++i) {
    b = s.empty();
  }
  t.record("EMPTY");
  for (int i = 0; i < REPEAT; ++i) {
    size = s.size();
  }
  t.record("SIZE");
  for (int i = 0; i < REPEAT; ++i) {
    s.push(i);
  }
  t.record("PUSH");
  for (int i = 0; i < REPEAT; ++i) {
    s.pop();
  }
  t.record("POP");

  for (int i = 0; i < REPEAT; ++i) {
    b = (s == temp_s);
  }
  t.record("COMPARE");

  return (0);
}
