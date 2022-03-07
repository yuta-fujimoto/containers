#ifndef ENABLE_IF_H_
# define ENABLE_IF_H_

#include "common.hpp"

namespace ft {

// enable_if
template <bool, typename T = void>
struct enable_if {};

// partial specialization for true.
template <typename T>
struct enable_if<true, T> {
  typedef T type;
};
}

#endif
