#ifndef NORMAL_ITERATOR_HPP
#define NORMAL_ITERATOR_HPP

#include <iostream>

#include "common.hpp"
#include "enable_if.hpp"
#include "iterator_traits.hpp"
#include "type_traits.hpp"

namespace ft {

// The _Container parameter exists solely so that different containers
// using this template can instantiate different types, even if the
// _Iterator parameter is the same.
template <typename _Iterator, typename _Container>
class _normal_iterator {
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

 public:
  _normal_iterator(_Iterator v = _Iterator()) : v(v) {}
  _normal_iterator(_normal_iterator<_Iterator, _Container> const& rhs)
      : v(rhs.v) {}
  // Allow iterator to const_iterator conversion
  template <typename _Iter>
  _normal_iterator(
      const _normal_iterator<
          _Iter, typename enable_if<
                     (is_same<_Iter, typename _Container::pointer>::value),
                     _Container>::type>& rhs)
      : v(rhs.base()) {}
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
  _normal_iterator operator+(difference_type __n) const {
    return (_normal_iterator(v + __n));
  }
  _normal_iterator& operator+=(difference_type __n) {
    v += __n;
    return (*this);
  }
  _normal_iterator operator-(difference_type __n) const {
    return (_normal_iterator(v - __n));
  }
  _normal_iterator& operator-=(difference_type __n) {
    v -= __n;
    return (*this);
  }
  // ??
  pointer operator->() const { return (&(*v)); }
  const _Iterator& base(void) const { return (v); }
};

// Forward iterator requirements
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator==(const _normal_iterator<_IteratorL, _Container>& __lhs,
                       const _normal_iterator<_IteratorR, _Container>& __rhs) {
  return __lhs.base() == __rhs.base();
}

template <typename _Iterator, typename _Container>
inline bool operator==(const _normal_iterator<_Iterator, _Container>& __lhs,
                       const _normal_iterator<_Iterator, _Container>& __rhs) {
  return __lhs.base() == __rhs.base();
}

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator!=(const _normal_iterator<_IteratorL, _Container>& __lhs,
                       const _normal_iterator<_IteratorR, _Container>& __rhs) {
  return __lhs.base() != __rhs.base();
}

template <typename _Iterator, typename _Container>
inline bool operator!=(const _normal_iterator<_Iterator, _Container>& __lhs,
                       const _normal_iterator<_Iterator, _Container>& __rhs) {
  return __lhs.base() != __rhs.base();
}

// Random access iterator requirements
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator<(const _normal_iterator<_IteratorL, _Container>& __lhs,
                      const _normal_iterator<_IteratorR, _Container>& __rhs) {
  return __lhs.base() < __rhs.base();
}

template <typename _Iterator, typename _Container>
inline bool operator<(const _normal_iterator<_Iterator, _Container>& __lhs,
                      const _normal_iterator<_Iterator, _Container>& __rhs) {
  return __lhs.base() < __rhs.base();
}

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator>(const _normal_iterator<_IteratorL, _Container>& __lhs,
                      const _normal_iterator<_IteratorR, _Container>& __rhs) {
  return __lhs.base() > __rhs.base();
}

template <typename _Iterator, typename _Container>
inline bool operator>(const _normal_iterator<_Iterator, _Container>& __lhs,
                      const _normal_iterator<_Iterator, _Container>& __rhs) {
  return __lhs.base() > __rhs.base();
}

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator<=(const _normal_iterator<_IteratorL, _Container>& __lhs,
                       const _normal_iterator<_IteratorR, _Container>& __rhs) {
  return __lhs.base() <= __rhs.base();
}

template <typename _Iterator, typename _Container>
inline bool operator<=(const _normal_iterator<_Iterator, _Container>& __lhs,
                       const _normal_iterator<_Iterator, _Container>& __rhs) {
  return __lhs.base() <= __rhs.base();
}

template <typename _IteratorL, typename _IteratorR, typename _Container>
inline bool operator>=(const _normal_iterator<_IteratorL, _Container>& __lhs,
                       const _normal_iterator<_IteratorR, _Container>& __rhs) {
  return __lhs.base() >= __rhs.base();
}

template <typename _Iterator, typename _Container>
inline bool operator>=(const _normal_iterator<_Iterator, _Container>& __lhs,
                       const _normal_iterator<_Iterator, _Container>& __rhs) {
  return __lhs.base() >= __rhs.base();
}

// operator- must accept mixed iterator/const_iterator
// parameters.
template <typename _IteratorL, typename _IteratorR, typename _Container>
inline typename _normal_iterator<_IteratorL, _Container>::difference_type
operator-(const _normal_iterator<_IteratorL, _Container>& __lhs,
          const _normal_iterator<_IteratorR, _Container>& __rhs) {
  return __lhs.base() - __rhs.base();
}

template <typename _Iterator, typename _Container>
inline typename _normal_iterator<_Iterator, _Container>::difference_type
operator-(const _normal_iterator<_Iterator, _Container>& __lhs,
          const _normal_iterator<_Iterator, _Container>& __rhs) {
  return __lhs.base() - __rhs.base();
}

template <typename _Iterator, typename _Container>
inline _normal_iterator<_Iterator, _Container> operator+(
    typename _normal_iterator<_Iterator, _Container>::difference_type __n,
    const _normal_iterator<_Iterator, _Container>& __i) {
  return _normal_iterator<_Iterator, _Container>(__i.base() + __n);
}

}  // namespace ft

#endif
