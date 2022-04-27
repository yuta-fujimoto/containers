# containers
reimplement c++ containers (WIP)

## Features
* vector
* stack
* map
* set
* iterator, reverse_iterator, enable_if, etc...

## tests
1. make test (test all movements using doctest)
2. cd performance && bash grademe.sh (compare their perfomance with std's containers)
3. cd Rb_tree_test && make && ./a.out (test red-black tree https://ja.wikipedia.org/wiki/%E8%B5%A4%E9%BB%92%E6%9C%A8)

## 難点
1. vector insert

int, char等の場合どうしてもstdと比べても遅くなってしまう。完全に対応するのは難しそう。

コンストラクタが定義されているクラスはnot trivially constructableという理解
int, char. doubleとかいうのは全てtrivially constructable

* https://stackoverflow.com/questions/49901309/is-it-possible-to-have-a-library-implementation-of-is-trivially-constructible-wi

これに絡めて、insertなどでstd::copyやstd::fillを使う場合、std::string等でテストするとsegvになる
uninitialized_copy参照

2. 赤黒木の実装

wikipediaを参考に実装したが多少、違うところというか自分で考えないといけないところがあった
完全に実装が書いてあるものを参考にした方が良かったかも
