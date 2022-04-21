#ifndef TYPE_TRAITS_H_
#define TYPE_TRAITS_H_

namespace ft {

template <typename _Tp, _Tp _v>
struct integral_constant {
  static const _Tp value = _v;
  typedef _Tp value_type;
  typedef integral_constant<_Tp, _v> type;
  operator value_type() const { return (value); }
};

template <typename _Tp, _Tp __v>
const _Tp integral_constant<_Tp, __v>::value;

// remove_cv
template <class _Tp>
struct remove_cv {
  typedef _Tp type;
};

// remove_cv partial specializations
template <class _Tp>
struct remove_cv<const _Tp> {
  typedef _Tp type;
};
template <class _Tp>
struct remove_cv<volatile _Tp> {
  typedef _Tp type;
};
template <class _Tp>
struct remove_cv<const volatile _Tp> {
  typedef _Tp type;
};

/// The type used as a compile-time boolean with true value.
typedef ft::integral_constant<bool, true> true_type;

/// The type used as a compile-time boolean with false value.
typedef ft::integral_constant<bool, false> false_type;

/*
 is_same
*/
template <typename, typename>
struct is_same : public false_type {};

template <typename _Tp>
struct is_same<_Tp, _Tp> : public true_type {};

// is_integral_helper
template <typename>
struct is_integral_helper : false_type {};

// partial specializations
template <>
struct is_integral_helper<bool> : public true_type {};

template <>
struct is_integral_helper<char> : public true_type {};

template <>
struct is_integral_helper<signed char> : public true_type {};

template <>
struct is_integral_helper<unsigned char> : public true_type {};

template <>
struct is_integral_helper<wchar_t> : public true_type {};

template <>
struct is_integral_helper<short> : public true_type {};

template <>
struct is_integral_helper<unsigned short> : public true_type {};

template <>
struct is_integral_helper<int> : public true_type {};

template <>
struct is_integral_helper<unsigned int> : public true_type {};

template <>
struct is_integral_helper<long> : public true_type {};

template <>
struct is_integral_helper<unsigned long> : public true_type {};

/*
 is_integral
*/
template <class _Tp>
struct is_integral : is_integral_helper<typename remove_cv<_Tp>::type> {};

/*
 enable_if
*/
template <bool, typename _Tp = void>
struct enable_if {};

// partial specialization for true.
template <typename _Tp>
struct enable_if<true, _Tp> {
  typedef _Tp type;
};

}  // namespace ft

#endif
