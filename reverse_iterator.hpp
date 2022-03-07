#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "common.hpp"
#include "iterator_traits.hpp"

namespace ft {

template <typename Iterator>
class _reverse_iterator {
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

  _reverse_iterator(Iterator v = Iterator()) : v(v) {}
  ~_reverse_iterator() {}
  _reverse_iterator(_reverse_iterator const& rhs) : v(rhs.v) {}
  // Allow iterator to const_iterator conversion
  template <typename Iter>
  _reverse_iterator(const _reverse_iterator<Iter>& rhs) : v(rhs.base()) {}
  _reverse_iterator& operator=(_reverse_iterator const& rhs) {
    if (this != &rhs) {
      v = rhs.v;
    }
    return (*this);
  }
  reference operator*() { return (*(v - 1)); }
  const reference operator*() const { return (*(v - 1)); }
  reference operator[](size_type p) { return (*(v - p - 1)); }
  const reference operator[](size_type p) const { return (*(v - p - 1)); }
  pointer operator->() const { return (&(*(v - 1))); }
  _reverse_iterator& operator++() {
    v--;

    return (*this);
  }
  _reverse_iterator operator++(int) {
    _reverse_iterator copy = *this;

    --*this;
    return (copy);
  }
  _reverse_iterator& operator--() {
    v++;

    return (*this);
  }
  _reverse_iterator operator--(int) {
    _reverse_iterator copy = *this;

    ++*this;
    return (copy);
  }
  bool operator!=(_reverse_iterator const& right) const { return (v != right.v); }
  bool operator==(_reverse_iterator const& right) const { return (v == right.v); }
  bool operator>(_reverse_iterator const& right) const { return (v > right.v); }
  bool operator<(_reverse_iterator const& right) const { return (v < right.v); }
  bool operator>=(_reverse_iterator const& right) const { return (v >= right.v); }
  bool operator<=(_reverse_iterator const& right) const { return (v <= right.v); }
  _reverse_iterator operator+(size_type ri) {
    return (_reverse_iterator(v - ri));
  }
  _reverse_iterator operator-(size_type ri) {
    return (_reverse_iterator(v + ri));
  }
  size_type operator-(_reverse_iterator const& right) { return (right.v - v); }
  Iterator base(void) const { return (v); };
};
}  // namespace ft

#endif
