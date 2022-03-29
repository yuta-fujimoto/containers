#ifndef MAP_HPP
#define MAP_HPP

#include <functional>

#include "_Rb_tree.hpp"
#include "common.hpp"
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
  map() {}
  ~map() { clear(); }
  map(map const& rhs);
  map& operator=(map const& rhs);

 private:
  typedef _Rb_tree<key_type, value_type, Compare> _Rep_type;

  _Rep_type Mt;

 public:
  typedef typename _Rep_type::iterator iterator;
  typedef typename _Rep_type::const_iterator const_iterator;
  typedef typename _Rep_type::size_type size_type;
  typedef typename _Rep_type::difference_type difference_type;
  typedef typename _Rep_type::reverse_iterator reverse_iterator;
  typedef typename _Rep_type::const_reverse_iterator const_reverse_iterator;

  key_compare key_comp() const { return (Mt.key_comp()); }
  T& operator[](const key_type& x) {}
  T& operator[](key_type&& x);
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
  // [TODO]
  // pair<iterator, bool> insert(iterator pos, const value_type& x)
  // {
  //   return (Mt._Rb_insert(x));
  // }
  size_type count(const key_type& x) const {
    if (Mt._Rb_find(x) == NULL) return (0);
    return (1);
  }
  void clear() { Mt._Rb_clear(); }
  size_type size(void) const { return (Mt.size()); }
  bool empty(void) const { return (Mt.size() == 0); }
  size_type erase(const key_type& x) {
    size_type old_size = Mt.size();
    Mt._Rb_erase(x);
    return (size() - old_size);
  }
  // auxiliary
  void erase(iterator pos) { Mt._Rb_erase_aux(pos->_M_node); }
  void erase(iterator first, iterator last) {
    for (iterator it = first; it != last; ++it) {
      erase(it);
    }
  }
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
};
}  // namespace ft

#endif
