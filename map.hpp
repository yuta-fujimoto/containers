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

template <class Key, class T, class Compare = std::less<Key>,
          typename _Alloc = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef _Alloc allocator_type;

  // value_compare ??
  // node_type node_handle ??
  // insert_return_type

 private:
  typedef _Rb_tree<key_type, value_type, _Select1st<value_type>, Compare>
      _Rep_type;

  _Rep_type Mt;

 public:
  class value_compare
      : public std::binary_function<value_type, value_type, bool> {
    // get first/second value type with baluebinary funtion
    // FRIEND !!!
    friend class map<Key, T, Compare, _Alloc>;

   protected:
    Compare comp;

    value_compare(Compare __c) : comp(__c) {}

   public:
    bool operator()(const value_type& __x, const value_type& __y) const {
      return (comp(__x.first, __y.first));
    }
  };
  explicit map(const Compare& comp = Compare(),
               const allocator_type& alloc = allocator_type())
      : Mt(comp, alloc) {}
  template <class InputIterator>
  map(InputIterator first, InputIterator last, const Compare& comp = Compare(),
      const allocator_type& alloc = allocator_type())
      : Mt(comp, alloc) {
    Mt._Rb_insert_range(first, last);
  }
  ~map(){};
  map(map const& rhs) : Mt(rhs.Mt) {}
  map& operator=(map const& rhs) {
    if (this != &rhs) Mt = rhs.Mt;
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

  mapped_type& operator[](const key_type& _k) {
    // i->first >= _k
    iterator _i = lower_bound(_k);

    if (_i == end() || key_comp()(_k, _i->first)) {
      _i = insert(_i, value_type(_k, mapped_type()));
    }
    return (_i->second);
  }
  mapped_type& operator[](key_type& _k) {
    // i->first >= _k
    std::cout << _k << std::endl;
    iterator _i = lower_bound(_k);

    std::cout << "LOWER BOUND DONE" << std::endl;
    if (_i == end() || key_comp()(_k, _i->first)) {
      _i = insert(_i, value_type(_k, mapped_type()));
    }
    return (_i->second);
  }
  iterator begin() { return (Mt.begin()); }
  const_iterator begin() const { return (Mt.begin()); }
  reverse_iterator rbegin() { return (reverse_iterator(Mt.end())); }
  iterator end() { return (Mt.end()); }
  const_iterator end() const { return (Mt.end()); }
  reverse_iterator rend() { return (reverse_iterator(Mt.begin())); }
  iterator find(const key_type& x) { return (iterator(Mt._Rb_find(x))); }
  const_iterator find(const key_type& x) const {
    return (const_iterator(Mt._Rb_find(x)));
  }
  pair<iterator, bool> insert(const value_type& x) {
    return (Mt._Rb_insert(x));
  }
  iterator insert(iterator pos, const value_type& x) {
    return (Mt._Rb_insert_hint(pos, x));
  }
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    Mt._Rb_insert_range(first, last);
  }
  size_type count(const key_type& x) const {
    if (find(x) == end()) return (0);
    return (1);
  }
  void swap(map& _x) { Mt.swap(_x.Mt); }
  void clear() { Mt._Rb_clear(); }
  key_compare key_comp() const { return (Mt.key_comp()); }
  value_compare value_comp() const { return (value_compare(Mt.key_comp())); }
  size_type max_size() const { return (Mt.max_size()); }
  size_type size(void) const { return (Mt.size()); }
  bool empty(void) const { return (Mt.size() == 0); }
  size_type erase(const key_type& x) {
    return (Mt._Rb_erase(x));
  }
  // auxiliary
  void erase(iterator pos) { Mt._Rb_erase_aux(pos._M_node); }
  void erase(iterator first, iterator last) { Mt._Rb_erase_range(first, last); }
  iterator lower_bound(const key_type& x) { return (Mt.lower_bound(x)); }
  const_iterator lower_bound(const key_type& x) const {
    return (Mt.lower_bound(x));
  }
  iterator upper_bound(const key_type& x) { return (Mt.upper_bound(x)); }
  const_iterator upper_bound(const key_type& x) const {
    return (Mt.upper_bound(x));
  }
  pair<iterator, iterator> equal_range(const key_type& x) {
    return (Mt.equal_range(x));
  }
  pair<const_iterator, const_iterator> equal_range(const key_type& x) const {
    return (Mt.equal_range(x));
  }
  allocator_type get_allocator() const { return (Mt.get_allocator()); }

  template <typename _K1, typename _T1, typename _C1, typename _A1>
  friend bool operator==(map<_K1, _T1, _C1, _A1> const&,
                         map<_K1, _T1, _C1, _A1> const&);

  template <typename _K1, typename _T1, typename _C1, typename _A1>
  friend bool operator<(map<_K1, _T1, _C1, _A1> const&,
                        map<_K1, _T1, _C1, _A1> const&);
};

template <typename T, typename U, typename C, typename A>
bool operator==(map<T, U, C, A> const& left, map<T, U, C, A> const& right) {
  return (left.Mt == right.Mt);
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
  return (left.Mt < right.Mt);
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
void swap(map<Key, T, Compare, Allocator>& x,
          map<Key, T, Compare, Allocator>& y) {
  x.swap(y);
}
}  // namespace ft

#endif
