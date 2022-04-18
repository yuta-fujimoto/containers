#ifndef MAP_HPP
#define MAP_HPP

#include <functional>

#include "_Rb_tree.hpp"
#include "common.hpp"
#include "enable_if.hpp"
#include "function.hpp"
#include "normal_iterator.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"

namespace ft {

template <class Key, class _Tp, class Compare = std::less<Key>,
          typename _Alloc = std::allocator<ft::pair<const Key, _Tp> > >
class map {
 public:
  typedef Key key_type;
  typedef _Tp mapped_type;
  typedef ft::pair<key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef _Alloc allocator_type;

  // value_compare ??
  // node_type node_handle ??
  // insert_return_type

 private:
  typedef _Rb_tree<key_type, value_type, _Select1st<value_type>, Compare>
      _Rep_type;

  _Rep_type _M_t;

 public:
  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
    // get first/second value type with baluebinary funtion
    // FRIEND !!!
    friend class map<Key, _Tp, Compare, _Alloc>;

   protected:
    Compare comp_;

    value_compare(Compare __c) : comp_(__c) {}

   public:
    bool operator()(const value_type& __x, const value_type& __y) const {
      return (comp_(__x.first, __y.first));
    }
  };
  map(const Compare& __comp = Compare(),
               const allocator_type& __alloc = allocator_type())
      : _M_t(__comp, __alloc) {}
  template <class InputIterator>
  map(InputIterator __first, InputIterator __last, const Compare& __comp = Compare(),
      const allocator_type& __alloc = allocator_type())
      : _M_t(__comp, __alloc) {
    _M_t._Rb_insert_range(__first, __last);
  }
  ~map(){};
  map(map const& __rhs) : _M_t(__rhs._M_t) {}
  map& operator=(map const& __rhs) {
    if (this != &__rhs) _M_t = __rhs._M_t;
    return (*this);
  }
  typedef typename _Alloc::pointer pointer;
  typedef typename _Alloc::const_pointer const_pointer;
  typedef typename _Alloc::reference reference;
  typedef typename _Alloc::const_reference const_reference;
  typedef typename _Rep_type::iterator iterator;
  typedef typename _Rep_type::const_iterator const_iterator;
  typedef typename _Rep_type::size_type size_type;
  typedef typename _Rep_type::difference_type difference_type;
  typedef typename _Rep_type::reverse_iterator reverse_iterator;
  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;

  mapped_type& operator[](const key_type& __k) {
    // i->first >= _k
    iterator _i = lower_bound(__k);

    if (_i == end() || key_comp()(__k, _i->first)) {
      _i = insert(_i, value_type(__k, mapped_type()));
    }
    return (_i->second);
  }
  mapped_type& operator[](key_type& __k) {
    // i->first >= _k
    iterator _i = lower_bound(__k);

    if (_i == end() || key_comp()(__k, _i->first)) {
      _i = insert(_i, value_type(__k, mapped_type()));
    }
    return (_i->second);
  }
  mapped_type& at(const key_type& __k) {
    // _i >= __k
    iterator _i = lower_bound(__k);
    if (_i == end() || key_comp()(__k, _i->first)) {
      throw std::out_of_range("map::at");
    }
    return (_i->second);
  }
  const mapped_type& at(const key_type& __k) const {
    // _i >= __k
    const_iterator _i = lower_bound(__k);
    if (_i == end() || key_comp()(__k, _i->first)) {
      throw std::out_of_range("map::at");
    };
    return (_i->second);
  }
  iterator begin() { return (_M_t.begin()); }
  const_iterator begin() const { return (_M_t.begin()); }
  reverse_iterator rbegin() { return (reverse_iterator(_M_t.end())); }
  iterator end() { return (_M_t.end()); }
  const_iterator end() const { return (_M_t.end()); }
  reverse_iterator rend() { return (reverse_iterator(_M_t.begin())); }
  iterator find(const key_type& __x) { return (iterator(_M_t._Rb_find(__x))); }
  const_iterator find(const key_type& __x) const {
    return (const_iterator(_M_t._Rb_find(__x)));
  }
  pair<iterator, bool> insert(const value_type& __x) {
    return (_M_t._Rb_insert(__x));
  }
  iterator insert(iterator __pos, const value_type& __x) {
    return (_M_t._Rb_insert_hint(__pos, __x));
  }
  template <class InputIterator>
  void insert(InputIterator __first, InputIterator __last) {
    _M_t._Rb_insert_range(__first, __last);
  }
  size_type count(const key_type& __x) const {
    if (find(__x) == end()) return (0);
    return (1);
  }
  void swap(map& __x) { _M_t.swap(__x._M_t); }
  void clear() { _M_t._Rb_clear(); }
  key_compare key_comp() const { return (_M_t.key_comp()); }
  value_compare value_comp() const { return (value_compare(_M_t.key_comp())); }
  size_type max_size() const { return (_M_t.max_size()); }
  size_type size(void) const { return (_M_t.size()); }
  bool empty() const { return (_M_t.size() == 0); }
  size_type erase(const key_type& __x) { return (_M_t._Rb_erase(__x)); }
  void erase(iterator __pos) { _M_t._Rb_erase_iter(__pos); }
  void erase(iterator __first, iterator __last) { _M_t._Rb_erase_range(__first, __last); }
  iterator lower_bound(const key_type& __x) { return (_M_t.lower_bound(__x)); }
  const_iterator lower_bound(const key_type& __x) const {
    return (_M_t.lower_bound(__x));
  }
  iterator upper_bound(const key_type& __x) { return (_M_t.upper_bound(__x)); }
  const_iterator upper_bound(const key_type& __x) const {
    return (_M_t.upper_bound(__x));
  }
  pair<iterator, iterator> equal_range(const key_type& __x) {
    return (_M_t.equal_range(__x));
  }
  pair<const_iterator, const_iterator> equal_range(const key_type& __x) const {
    return (_M_t.equal_range(__x));
  }
  allocator_type get_allocator() const { return (_M_t.get_allocator()); }

  template <typename T, typename U, typename C, typename A>
  friend bool operator==(map<T, U, C, A> const&,
                         map<T, U, C, A> const&);

  template <typename T, typename U, typename C, typename A>
  friend bool operator<(map<T, U, C, A> const&,
                        map<T, U, C, A> const&);
};

template <typename T, typename U, typename C, typename A>
bool operator==(map<T, U, C, A> const& left, map<T, U, C, A> const& right) {
  return (left._M_t == right._M_t);
}

template <typename T, typename U, typename C, typename A>
bool operator!=(map<T, U, C, A> const& left, map<T, U, C, A> const& right) {
  return (!(left == right));
}

template <typename T, typename U, typename C, typename A>
bool operator>(map<T, U, C, A> const& left, map<T, U, C, A> const& right) {
  return (right < left);
}

template <typename T, typename U, typename C, typename A>
bool operator<(map<T, U, C, A> const& left, map<T, U, C, A> const& right) {
  return (left._M_t < right._M_t);
}

template <typename T, typename U, typename C, typename A>
bool operator>=(map<T, U, C, A> const& left, map<T, U, C, A> const& right) {
  return (!(left < right));
}

template <typename T, typename U, typename C, typename A>
bool operator<=(map<T, U, C, A> const& left, map<T, U, C, A> const& right) {
  return (!(right < left));
}

template <class Key, class T, class Compare, class Allocator>
void swap(map<Key, T, Compare, Allocator>& __x,
          map<Key, T, Compare, Allocator>& __y) {
  __x.swap(__y);
}
}  // namespace ft

#endif
