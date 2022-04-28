#ifndef EQUAL_H_
#define EQUAL_H_

#include "common.hpp"

namespace ft {
template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 __first1, InputIterator1 __last1,
           InputIterator2 __first2) {
  for (; __first1 != __last1; ++__first1, ++__first2)
    if (!bool(*__first1 == *__first2)) return (false);
  return (true);
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 __first1, InputIterator1 __last1,
           InputIterator2 first2, BinaryPredicate __pred) {
  for (; __first1 != __last1; ++__first1, ++first2)
    if (!bool(__pred(*__first1, *first2))) return (false);
  return (true);
}

}  // namespace ft

#endif
