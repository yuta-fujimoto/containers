#ifndef STACK_H_
#define STACK_H_

#include "vector.hpp"

namespace ft {

template <class _Tp, class _Sequence = ft::vector<_Tp> >
class stack {
  template <typename _Tp1, typename _Seq1>
  friend bool operator==(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

  template <typename _Tp1, typename _Seq1>
  friend bool operator<(const stack<_Tp1, _Seq1>&, const stack<_Tp1, _Seq1>&);

 public:
  typedef typename _Sequence::value_type value_type;
  typedef typename _Sequence::reference reference;
  typedef typename _Sequence::const_reference const_reference;
  typedef typename _Sequence::size_type size_type;
  typedef _Sequence container_type;
  typedef typename _Sequence::iterator iterator;
  typedef typename _Sequence::const_iterator const_iterator;
  typedef typename _Sequence::reverse_iterator reverse_iterator;
  typedef typename _Sequence::const_reverse_iterator const_reverse_iterator;

 protected:
  _Sequence c;

 public:
  explicit stack(const _Sequence& _c = _Sequence()) : c(_c) {}

  bool empty() const { return c.empty(); }
  size_type size() const { return c.size(); }
  reference top() { return (c.back()); }
  const_reference top() const { return c.back(); }
  void push(const value_type& _x) { c.push_back(_x); }
  void pop() { c.pop_back(); }
};

template <typename _Tp, typename _Seq>
inline bool operator==(const stack<_Tp, _Seq>& _x, const stack<_Tp, _Seq>& _y) {
  return (_x.c == _y.c);
}

template <typename _Tp, typename _Seq>
inline bool operator<(const stack<_Tp, _Seq>& _x,
                      const stack<_Tp, _Seq>& _y) {
  return (_x.c < _y.c);
}

template <typename _Tp, typename _Seq>
inline bool operator!=(const stack<_Tp, _Seq>& _x,
                       const stack<_Tp, _Seq>& _y) {
  return !(_x == _y);
}

template <typename _Tp, typename _Seq>
inline bool operator>(const stack<_Tp, _Seq>& _x,
                      const stack<_Tp, _Seq>& _y) {
  return (_y < _x);
}

template <typename _Tp, typename _Seq>
inline bool operator<=(const stack<_Tp, _Seq>& _x,
                       const stack<_Tp, _Seq>& _y) {
  return !(_y < _x);
}

template <typename _Tp, typename _Seq>
inline bool operator>=(const stack<_Tp, _Seq>& _x,
                       const stack<_Tp, _Seq>& _y) {
  return !(_x < _y);
}
}  // namespace ft

#endif
