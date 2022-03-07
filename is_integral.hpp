#ifndef IS_INTEGRAL_H_
#define IS_INTEGRAL_H_

namespace ft {

template <typename _T, _T _v>
struct integral_constant {
  static const _T value = _v;
  typedef _T value_type;
};

// remove_cv
template <class T>
struct remove_cv {
  typedef T type;
};

// remove_cv partial specializations
template <class T>
struct remove_cv<const T> {
  typedef T type;
};
template <class T>
struct remove_cv<volatile T> {
  typedef T type;
};
template <class T>
struct remove_cv<const volatile T> {
  typedef T type;
};

/// The type used as a compile-time boolean with true value.
typedef ft::integral_constant<bool, true> true_type;

/// The type used as a compile-time boolean with false value.
typedef ft::integral_constant<bool, false> false_type;

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
