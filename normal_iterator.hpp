#ifndef NORMAL_ITERATOR_HPP
#define NORMAL_ITERATOR_HPP

#include <iostream>

#include "common.hpp"
#include "iterator_traits.hpp"

namespace ft {

template <typename Iterator>
class _normal_iterator {
 protected:
  Iterator v;
  typedef iterator_traits<Iterator> traits_type;

 public:
  typedef Iterator iterator_type;
  typedef typename traits_type::iterator_category iterator_category;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::difference_type difference_type;
  typedef typename traits_type::reference reference;
  typedef typename traits_type::pointer pointer;

 public:
  _normal_iterator(Iterator v = Iterator()) : v(v) {}
  _normal_iterator(_normal_iterator<Iterator> const& rhs) : v(rhs.v) {}
  // Allow iterator to const_iterator conversion
  template <typename Iter>
  _normal_iterator(const _normal_iterator<Iter>& rhs) : v(rhs.base()) {}
  _normal_iterator& operator=(_normal_iterator const& rhs) {
    if (this != &rhs) {
      v = rhs.v;
    }
    return (*this);
  }
  reference operator*() { return (*v); }
  const reference operator*() const { return (*v); }
  reference operator[](size_type p) { return (*(v + p)); }
  const reference operator[](size_type p) const { return (*(v + p)); }
  _normal_iterator& operator++() {
    v++;

    return (*this);
  }
  _normal_iterator operator++(int) {
    _normal_iterator copy = *this;

    ++*this;
    return (copy);
  }
  _normal_iterator& operator--() {
    v--;

    return (*this);
  }
  _normal_iterator operator--(int) {
    _normal_iterator copy = *this;

    --*this;
    return (copy);
  }
  bool operator!=(_normal_iterator const& right) const {
    return (v != right.v);
  }
  bool operator==(_normal_iterator const& right) const {
    return (v == right.v);
  }
  bool operator>(_normal_iterator const& right) const { return (v > right.v); }
  bool operator<(_normal_iterator const& right) const { return (v < right.v); }
  bool operator>=(_normal_iterator const& right) const {
    return (v >= right.v);
  }
  bool operator<=(_normal_iterator const& right) const {
    return (v <= right.v);
  }
  _normal_iterator operator+(size_type ri) {
    return (_normal_iterator(v + ri));
  }
  _normal_iterator operator-(size_type ri) {
    return (_normal_iterator(v - ri));
  }
  pointer operator->() const { return (&(*v)); }
  size_type operator-(_normal_iterator const& right) const {
    return (v - right.v);
  }
  const Iterator& base(void) const { return (v); }
};
}  // namespace ft

#endif
