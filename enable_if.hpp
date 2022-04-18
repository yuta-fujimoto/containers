#ifndef ENABLE_IF_H_
# define ENABLE_IF_H_

#include "common.hpp"

namespace ft {

// enable_if
template <bool, typename _Tp = void>
struct enable_if {};

// partial specialization for true.
template <typename _Tp>
struct enable_if<true, _Tp> {
  typedef _Tp type;
};
}

#endif
