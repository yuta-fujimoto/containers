#include "../RBtree.hpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

int main() {
  srand(time(NULL));
  std::ofstream ofs("rb_tree.txt");
  // comment for debug
  // std::vector<int> a = {};
  // std::vector<int> b = {};

  // [RANDOM TEST]
  std::vector<int> a;
  std::vector<int> b;
  int repeat = 100000;
  for (int i = 0; i < repeat; i++) a.push_back(rand() % repeat);
  for (int i = 0; i < repeat; i++) b.push_back(rand() % repeat);
  ft::RBtree<int, ft::pair<int, int> > T;

  for (auto i : a) {
    ofs << i << ", ";
    T.RBinsert(ft::pair<int, int>(i, i));
  }
  ofs << std::endl;
  if (!T.checkTree()) {
    return (0);
  }
  for (auto i : b) {
    ofs << i <<  ", ";
    T.RBdelete(i);
  }
  ofs << std::endl;
  if (!T.checkTree()) {
    return (0);
  }
  T.RBclear();
  T.printTree(); // noting would be printed

  // [EMPTY TEST]
  T.RBinsert(ft::pair<int, int>(1, 2));
  T.RBinsert(ft::pair<int, int>(2, 2));
  T.RBinsert(ft::pair<int, int>(3, 2));
  T.RBinsert(ft::pair<int, int>(4, 2));
  T.RBdelete(2);
  T.RBdelete(3);
  T.RBdelete(4);
  T.RBdelete(1);
  T.printTree(); // noting would be printed

  // in coverage test, Case_D2 doesn't be passed, but 
}
