#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "common.hpp"
#include "iterator_traits.hpp"

namespace ft {

template <typename _Iterator>
class _reverse_iterator {
 protected:
  _Iterator v;
  typedef iterator_traits<_Iterator> traits_type;

 public:
  typedef _Iterator iterator_type;
  typedef typename traits_type::iterator_category iterator_category;
  typedef typename traits_type::value_type value_type;
  typedef typename traits_type::difference_type difference_type;
  typedef typename traits_type::reference reference;
  typedef typename traits_type::pointer pointer;
  typedef std::size_t size_type;

  _reverse_iterator(_Iterator v = _Iterator()) : v(v) {}
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
  reference operator*() {
    _Iterator _tmp = v;

    return (*--_tmp);
  }
  const reference operator*() const {
    _Iterator _tmp = v;

    return (*--_tmp);
  }
  reference operator[](size_type p) { return (*(*this + p)); }
  const reference operator[](size_type p) const { return (*(*this + p)); }
  pointer operator->() const {
    _Iterator _tmp = v;

    --_tmp;
    return (_S_to_pointer(_tmp));
  }
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
  bool operator!=(_reverse_iterator const& right) const {
    return (v != right.v);
  }
  bool operator==(_reverse_iterator const& right) const {
    return (v == right.v);
  }
  bool operator>(_reverse_iterator const& right) const { return (v > right.v); }
  bool operator<(_reverse_iterator const& right) const { return (v < right.v); }
  bool operator>=(_reverse_iterator const& right) const {
    return (v >= right.v);
  }
  bool operator<=(_reverse_iterator const& right) const {
    return (v <= right.v);
  }
  _reverse_iterator operator+(size_type ri) const {
    return (_reverse_iterator(v - ri));
  }
  _reverse_iterator operator-(size_type ri) const {
    return (_reverse_iterator(v + ri));
  }
  size_type operator-(_reverse_iterator const& right) const { return (right.v - v); }
  _Iterator base(void) const { return (v); };

 private:
  template <typename _Tp>
  static _Tp* _S_to_pointer(_Tp* __p) {
    return (__p);
  }
  template <typename _Tp>
  static pointer _S_to_pointer(_Tp __t) {
    return (__t.operator->());
  }
};
}  // namespace ft

#endif
