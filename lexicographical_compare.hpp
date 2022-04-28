#ifndef LEXICOGRAPHICAL_COMPARE_H_
# define LEXICOGRAPHICAL_COMPARE_H_


#include "common.hpp"

namespace ft {
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 __first1, InputIterator1 __last1,
                             InputIterator2 __first2, InputIterator2 __last2) {
  for (; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2) {
    if (*__first1 < *__first2) return (true);
    if (*__first2 < *__first1) return (false);
  }
  return (__first1 == __last1 && __first2 != __last2);
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 __first1, InputIterator1 __last1,
                             InputIterator2 __first2, InputIterator2 __last2,
                             Compare comp) {
  for (; __first1 != __last1 && __first2 != __last2; ++__first1, ++__first2) {
    if (comp(*__first1, *__first2)) return (true);
    if (comp(*__first2, *__first1)) return (false);
  }
  return (__first1 == __last1 && __first2 != __last2);
}
}  // namespace ft

#endif
