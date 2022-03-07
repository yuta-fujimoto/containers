#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

// pair
template <typename T1, typename T2>
struct pair {
  typedef T1 first_type;
  typedef T2 second_type;

  T1 first;
  T2 second;

  // no default/copy constructor
  pair(const T1 &a, const T2 &b) : first(a), second(b) {}
  ~pair() {}
  pair &operator=(pair const &rhs) {
    if (this != &rhs) {
      first = rhs.first;
      second = rhs.second;
    }
    return (*this);
  }
  void swap(pair &p) {
    T1 temp1 = first;
    T2 temp2 = second;
    first = p.first;
    second = p.second;
    p.first = temp1;
    p.second = temp2;
  }
  bool operator>(const pair &obj) { return (this->first > obj.first); }

  bool operator<(const pair &obj) { return (this->first < obj.first); }

  bool operator>=(const pair &obj) { return (this->first >= obj.first); }

  bool operator<=(const pair &obj) { return (this->first <= obj.first); }

  bool operator==(const pair &obj) { return (this->first == obj.first); }

  bool operator!=(const pair &obj) { return (this->first != obj.first); }
};

template <class T1, class T2>
pair<T1, T2> make_pair(T1 first, T2 second) {
  return (pair<T1, T2>(first, second));
}
}// namespace ft
#endif
