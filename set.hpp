#ifndef SET_H_
#define SET_H_

#include "_Rb_tree.hpp"
#include "common.hpp"
#include "function.hpp"
#include "pair.hpp"

namespace ft {
template <typename _Key, typename _Compare = std::less<_Key>,
          typename _Alloc = std::allocator<_Key> >
class set {
 public:
  typedef _Key key_type;
  typedef _Key value_type;
  typedef _Compare key_compare;
  typedef _Compare value_compare;
  typedef _Alloc allocator_type;

 private:
  typedef _Rb_tree<key_type, value_type, _Identity<value_type>, value_compare,
                   allocator_type>
      _Rep_type;
  _Rep_type _M_t;

 public:
  typedef typename _Alloc::pointer pointer;
  typedef typename _Alloc::const_pointer const_pointer;
  typedef typename _Alloc::reference reference;
  typedef typename _Alloc::const_reference const_reference;
  typedef typename _Rep_type::const_iterator iterator;
  typedef typename _Rep_type::const_iterator const_iterator;
  typedef typename _Rep_type::const_reverse_iterator reverse_iterator;
  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;
  typedef typename _Rep_type::size_type size_type;
  typedef typename _Rep_type::difference_type difference_type;

  set() : _M_t() {}
  explicit set(const _Compare& _comp,
               const allocator_type& _a = allocator_type())
      : _M_t(_comp, _a) {}
  template <typename _InputIterator>
  set(_InputIterator __first, _InputIterator __last) : _M_t() {
    _M_t._Rb_insert_range(__first, __last);
  }
  /**
   * copy constructor
   */
  set(const set& __x) : _M_t(__x._M_t) {}

  /**
   * assignment operator
   */
  set& operator=(const set& __x) {
    _M_t = __x._M_t;
    return *this;
  }

  key_compare key_comp() const { return _M_t.key_comp(); }
  value_compare value_comp() const { return _M_t.key_comp(); }
  allocator_type get_allocator() const {
    return allocator_type(_M_t.get_allocator());
  }
  iterator begin() const { return (_M_t.begin()); }
  iterator end() const { return (_M_t.end()); }
  reverse_iterator rbegin() const { return (_M_t.rbegin()); }
  reverse_iterator rend() const { return (_M_t.rend()); }
  bool empty() const { return (_M_t.size() == 0); }
  size_type size() const { return _M_t.size(); }
  size_type max_size() const { return _M_t.max_size(); }
  void swap(set& __x) { _M_t.swap(__x._M_t); }
  pair<iterator, bool> insert(const value_type& _x) {
    pair<typename _Rep_type::iterator, bool> _p =
        _M_t._Rb_insert(_x);
    // iterator => const_iterator
    return (pair<iterator, bool>(_p.first, _p.second));
  }
  // reference says "iterator"
  iterator insert(iterator __position, const value_type& __x) {
    return (iterator(_M_t._Rb_insert_hint(__position, __x)));
  }
  template <typename _InputIterator>
  void insert(_InputIterator __first, _InputIterator __last) {
    _M_t._Rb_insert_range(__first, __last);
  }
  void erase(iterator __position) { _M_t._Rb_erase_iter(__position); }
  size_type erase(const key_type& __x) { return (_M_t._Rb_erase(__x)); }
  template <typename _InputIterator>
  void erase(_InputIterator __first, _InputIterator __last) {
    _M_t._Rb_erase_range(__first, __last);
  }
  void clear() { _M_t._Rb_clear(); }
  size_type count(const key_type& x) const {
    return (_M_t._Rb_find(x) == _M_t.end() ? 0 : 1);
  }
  iterator find(const key_type& __x) { return (_M_t._Rb_find(__x)); }
  const_iterator find(const key_type& __x) const {
    return (_M_t._Rb_find(__x));
  }
  iterator lower_bound(const key_type& __x) { return (_M_t.lower_bound(__x)); }
  const_iterator lower_bound(const key_type& __x) const {
    return (_M_t.lower_bound(__x));
  }
  iterator upper_bound(const key_type& __x) { return _M_t.upper_bound(__x); }
  const_iterator upper_bound(const key_type& __x) const {
    return _M_t.upper_bound(__x);
  }
  pair<iterator, iterator> equal_range(const key_type& __x) {
    pair<typename _Rep_type::iterator, typename _Rep_type::iterator>
    _p = _M_t.equal_range(__x);
    return (pair<iterator, iterator>(_p.first, _p.second));
  }
  pair<const_iterator, const_iterator> equal_range(const key_type& __x) const {
    return _M_t.equal_range(__x);
  }
  template <typename _K1, typename _C1, typename _A1>
  friend bool operator==(const set<_K1, _C1, _A1>&, const set<_K1, _C1, _A1>&);

  template <typename _K1, typename _C1, typename _A1>
  friend bool operator<(const set<_K1, _C1, _A1>&, const set<_K1, _C1, _A1>&);
};

template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator==(const set<_Key, _Compare, _Alloc>& __x,
                       const set<_Key, _Compare, _Alloc>& __y) {
  return (__x._M_t == __y._M_t);
}

template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator<(const set<_Key, _Compare, _Alloc>& __x,
                      const set<_Key, _Compare, _Alloc>& __y) {
  return (__x._M_t < __y._M_t);
}

///  Returns !(x == y).
template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator!=(const set<_Key, _Compare, _Alloc>& __x,
                       const set<_Key, _Compare, _Alloc>& __y) {
  return !(__x == __y);
}

///  Returns y < x.
template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator>(const set<_Key, _Compare, _Alloc>& __x,
                      const set<_Key, _Compare, _Alloc>& __y) {
  return __y < __x;
}

///  Returns !(y < x)
template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator<=(const set<_Key, _Compare, _Alloc>& __x,
                       const set<_Key, _Compare, _Alloc>& __y) {
  return !(__y < __x);
}

///  Returns !(x < y)
template <typename _Key, typename _Compare, typename _Alloc>
inline bool operator>=(const set<_Key, _Compare, _Alloc>& __x,
                       const set<_Key, _Compare, _Alloc>& __y) {
  return !(__x < __y);
}

template <typename _Key, typename _Compare, typename _Alloc>
inline void swap(set<_Key, _Compare, _Alloc>& __x,
                 set<_Key, _Compare, _Alloc>& __y) {
  __x.swap(__y);
}

}  // namespace ft

#endif
