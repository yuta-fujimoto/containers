# containers
reimplement c++ containers (WIP)

## Features
* vector
* stack
* map
* set
* iterator, reverse_iterator, enable_if, etc...

## tests
```
1. make test (test all movements using doctest)
2. cd performance && bash grademe.sh (compare their perfomance with std's containers)
3. cd Rb_tree_test && make && ./a.out (test red-black tree https://ja.wikipedia.org/wiki/%E8%B5%A4%E9%BB%92%E6%9C%A8)
```

## 難点
1. vectorの最適化(insertやpush_backなど新しく領域を作って中身を移し替える必要がある場合)

* intやdoubleなどtrivially constructable(memsetが使える)ものはmemsetを使用した方が早い。
参考: https://stackoverflow.com/questions/49901309/is-it-possible-to-have-a-library-implementation-of-is-trivially-constructible-wi

* 下記のコードはsegvする
```
#include <iostream>
#include <memory>

struct Greeting {
  std::string msg;

  Greeting(std::string g = "") : msg(g) {}
  void say() { std::cout << msg << std::endl; }
  Greeting& operator=(Greeting const& rhs) {
    std::cout << *&msg << std::endl;
    if (this != &rhs) {
      msg = rhs.msg;
    }
    return (*this);
  }
};

int main() {
  std::allocator<Greeting> alloc;

  Greeting* dst = alloc.allocate(1);
  Greeting src("hello");

  // alloc.construct(dst, src);
  *dst = src;

  (*dst).say();
  alloc.deallocate(dst, 1);
}
```

dst内のmsgが正しく初期化されいないためstring内のassignmation operatorの処理がうまくいってない

なのでコメントアウトしたconstruct関数を使う必要がある、

stdのライブラリで便利なcopy, back_wordcopyなどは=を使っているためinsertなどで新しい領域にイテレータを割り当てる場合は使えない可能性がある。(上のコードのような問題が発生します)

内部でconstructしてくれるuninitialized_copyなどを使うとよい。

まぁfor分を使ってconstructするのが確実だと思います。

2. 赤黒木の実装

wikipediaを参考に実装したが多少、違うところというか自分で考えないといけないところがあった
完全に実装が書いてあるものを参考にした方が良かったかも
