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
  pair() : first(), second() {}
  pair(const T1 &__a, const T2 &__b) : first(__a), second(__b) {}
  template<typename U1, typename U2>
  pair(const pair<U1, U2> &__p) : first(__p.first), second(__p.second) {}
  ~pair() {}
  pair &operator=(pair const &__rhs) {
    if (this != &__rhs) {
      first = __rhs.first;
      second = __rhs.second;
    }
    return (*this);
  }
  template <class U, class V>
  pair &operator=(const pair<U, V> &__rhs) {
    first = __rhs.first;
    second = __rhs.second;
    return (*this);
  }
  // no swap
  // void swap(pair &p) {
  //   std::swap(first, p.first);
  //   std::swap(first, p.second);
  // }
};

template <typename _T1, typename _T2>
bool operator==(const pair<_T1, _T2> &_x, const pair<_T1, _T2> &_y) {
  return (_x.first == _y.first && _x.second == _y.second);
}
template <typename _T1, typename _T2>
bool operator!=(const pair<_T1, _T2> &_x, const pair<_T1, _T2> &_y) {
  return (!(_x == _y));
}
template <typename _T1, typename _T2>
bool operator<(const pair<_T1, _T2> &_x, const pair<_T1, _T2> &_y) {
  return (_x.first < _y.first ||
          (!(_y.first < _x.first) && _x.second < _y.second));
}
template <typename _T1, typename _T2>
bool operator<=(const pair<_T1, _T2> &_x, const pair<_T1, _T2> &_y) {
  return (!(_y < _x));
}
template <typename _T1, typename _T2>
bool operator>(const pair<_T1, _T2> &_x, const pair<_T1, _T2> &_y) {
  return (_y < _x);
}
template <typename _T1, typename _T2>
bool operator>=(const pair<_T1, _T2> &_x, const pair<_T1, _T2> &_y) {
  return (!(_x < _y));
}

template <class _T1, class _T2>
pair<_T1, _T2> make_pair(_T1 first, _T2 second) {
  return (pair<_T1, _T2>(first, second));
}

// template <class _T1, class _T2>
// void swap(pair<_T1, _T2> &_x, pair<_T1, _T2> &_y) {
//   _x.swap(_y);
// }
}  // namespace ft
#endif
