#ifndef IS_INTEGRAL_H_
#define IS_INTEGRAL_H_

#include "type_traits.hpp"

namespace ft {
// is_integral_helper
template <typename>
struct is_integral_helper : false_type {};

// partial specializations
template <>
struct is_integral_helper<bool> : true_type {};

template <>
struct is_integral_helper<char> : true_type {};

template <>
struct is_integral_helper<wchar_t> : true_type {};

template <>
struct is_integral_helper<short> : true_type {};

template <>
struct is_integral_helper<int> : true_type {};

template <>
struct is_integral_helper<long> : true_type {};

// is_integral
template <class T>
struct is_integral : is_integral_helper<typename remove_cv<T>::type> {};
}  // namespace ft

#endif
