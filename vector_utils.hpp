#ifndef VECTOR_UTILS_H_
#define VECTOR_UTILS_H_

#include <memory>

#include "type_traits.hpp"

namespace ft {

// Trivial types can have deleted copy constructor, but the std::copy
// optimization that uses memmove would happily "copy" them anyway.

template <typename _InputIterator, typename _ForwardIterator>
inline _ForwardIterator vector_uninitialized_copy(
    _InputIterator __first, _InputIterator __last, _ForwardIterator __result,
    typename enable_if<
        _is_trivial<typename _ForwardIterator::value_type>::value>::type* = 0) {
  // _InputIterator may be reverse iterator
  for (; __first != __last; ++__first, ++__result) {
    std::memmove(&*__result, &*__first,
                 sizeof(typename _ForwardIterator::value_type));
  }
  return (__result);
}

template <typename _InputIterator, typename _ForwardIterator>
inline _ForwardIterator vector_uninitialized_copy(
    _InputIterator __first, _InputIterator __last, _ForwardIterator __result,
    typename enable_if<
        !_is_trivial<typename _ForwardIterator::value_type>::value>::type* =
        0) {
  return (std::uninitialized_copy(__first, __last, __result));
}

template <typename _InputIterator, typename _ForwardIterator>
inline void vector_uninitialized_copy_backward(
    _InputIterator __first, _InputIterator __last, _ForwardIterator __result,
    typename enable_if<
        _is_trivial<typename _ForwardIterator::value_type>::value>::type* = 0) {
  // definetely vector::iterator(not reverse iterator)
  ptrdiff_t dist = std::distance(__first, __last);
  std::memmove(&*__result - dist, &*__first,
               sizeof(typename _ForwardIterator::value_type) * dist);
}

template <typename _InputIterator, typename _ForwardIterator>
inline void vector_uninitialized_copy_backward(
    _InputIterator __first, _InputIterator __last, _ForwardIterator __result,
    typename enable_if<
        !_is_trivial<typename _ForwardIterator::value_type>::value>::type* =
        0) {
  std::allocator<typename _InputIterator::value_type> alloc;

  while (__first != __last) alloc.construct((--__result).base(), *--__last);
}

template <typename _ForwardIterator, typename _T>
inline void vector_uninitialized_fill(
    _ForwardIterator __first, _ForwardIterator __last, const _T& __x,
    typename enable_if<
        _is_trivial<typename _ForwardIterator::value_type>::value>::type* = 0) {
  for (; __first != __last; ++__first) {
    std::memmove(&*__first, &__x, sizeof(_T));
  }
}

template <typename _ForwardIterator, typename _T>
inline void vector_uninitialized_fill(
    _ForwardIterator __first, _ForwardIterator __last, const _T& __x,
    typename enable_if<
        !_is_trivial<typename _ForwardIterator::value_type>::value>::type* =
        0) {
  std::uninitialized_fill(__first, __last, __x);
}

}  // namespace ft

#endif
