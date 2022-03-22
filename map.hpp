#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include "pair.hpp"
#include "common.hpp"
#include "reverse_iterator.hpp"
#include "normal_iterator.hpp"
#include "RBtree.hpp"

namespace ft {
template <class Key, class T, class Compare = std::less<Key>,
          class Allocator = std::allocator<ft::pair<const Key, T> > >
class map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef std::pair<key_type, mapped_type> value_type;
  typedef Compare key_compare;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef _normal_iterator<pointer> iterator;
  typedef _normal_iterator<const_pointer> const_iterator;
  typedef _reverse_iterator<const_pointer> const_reverse_iterator;
  typedef _reverse_iterator<pointer> reverse_iterator;
  typedef Allocator allocator_type;
  typedef ptrdiff_t difference_type;
// value_compare ??
// node_type node_handle ??
// insert_return_type
  map();
  ~map();
  map(map const &rhs);
  map &operator=(map const &rhs);
  // iterator first
  // ft::pair<iterator, bool> insert(const value_type &x)
  // {
  //   ft::pair<iterator, bool> res;

  //   if (Mt.RBfind(x.first))
  // }
 private:

  typedef RBtree<key_type, value_type> Rep_type;

  Rep_type Mt;
};

}  // namespace std

#endif
