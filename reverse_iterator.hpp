#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "common.hpp"
#include "iterator_traits.hpp"
#include "type_traits.hpp"

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

  _reverse_iterator(_Iterator __v = _Iterator()) : v(__v) {}
  _reverse_iterator(_reverse_iterator const& rhs) : v(rhs.v) {}
  // Allow iterator to const_iterator conversion
  template <typename Iter>
  _reverse_iterator(const _reverse_iterator<Iter>& rhs) : v(rhs.base()) {}
  ~_reverse_iterator() {}
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

    ++*this;
    return (copy);
  }
  _reverse_iterator& operator--() {
    v++;

    return (*this);
  }
  _reverse_iterator operator--(int) {
    _reverse_iterator copy = *this;

    --*this;
    return (copy);
  }
  _reverse_iterator operator+(difference_type __n) const {
    return (_reverse_iterator(v - __n));
  }
  _reverse_iterator& operator+=(difference_type __n) {
    v -= __n;
    return (*this);
  }
  _reverse_iterator operator-(difference_type __n) const {
    return (_reverse_iterator(v + __n));
  }
  _reverse_iterator& operator-=(difference_type __n) {
    v += __n;
    return (*this);
  }
  _Iterator base(void) const { return (v); }

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

// Comparison of reverse_iterator to const reverse_iterator.
template <typename _IteratorL, typename _IteratorR>
inline bool operator==(const _reverse_iterator<_IteratorL>& __x,
                       const _reverse_iterator<_IteratorR>& __y) {
  return __x.base() == __y.base();
}

template <typename _IteratorL, typename _IteratorR>
inline bool operator<(const _reverse_iterator<_IteratorL>& __x,
                      const _reverse_iterator<_IteratorR>& __y) {
  return __y.base() < __x.base();
}

template <typename _IteratorL, typename _IteratorR>
inline bool operator!=(const _reverse_iterator<_IteratorL>& __x,
                       const _reverse_iterator<_IteratorR>& __y) {
  return !(__x == __y);
}

template <typename _IteratorL, typename _IteratorR>
inline bool operator>(const _reverse_iterator<_IteratorL>& __x,
                      const _reverse_iterator<_IteratorR>& __y) {
  return __y < __x;
}

template <typename _IteratorL, typename _IteratorR>
inline bool operator<=(const _reverse_iterator<_IteratorL>& __x,
                       const _reverse_iterator<_IteratorR>& __y) {
  return !(__y < __x);
}

template <typename _IteratorL, typename _IteratorR>
inline bool operator>=(const _reverse_iterator<_IteratorL>& __x,
                       const _reverse_iterator<_IteratorR>& __y) {
  return !(__x < __y);
}

template <typename _Iterator>
inline typename _reverse_iterator<_Iterator>::difference_type operator-(
    const _reverse_iterator<_Iterator>& __x,
    const _reverse_iterator<_Iterator>& __y) {
  return __y.base() - __x.base();
}

// operator- must accept mixed iterator/const_iterator
// parameters.
template <typename _IteratorL, typename _IteratorR>
inline typename _reverse_iterator<_IteratorL>::difference_type operator-(
    const _reverse_iterator<_IteratorL>& __x,
    const _reverse_iterator<_IteratorR>& __y) {
  return __y.base() - __x.base();
}

template <typename _Iterator>
inline _reverse_iterator<_Iterator> operator+(
    typename _reverse_iterator<_Iterator>::difference_type __n,
    const _reverse_iterator<_Iterator>& __x) {
  return _reverse_iterator<_Iterator>(__x.base() - __n);
}

}  // namespace ft

#endif
