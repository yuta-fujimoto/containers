#ifndef TYPE_TRAITS_H_
#define TYPE_TRAITS_H_

namespace ft {

template <typename _T, _T _v>
struct integral_constant {
  static const _T value = _v;
  typedef _T value_type;
};

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

/// is_same
template <typename, typename>
struct is_same : public false_type {};

template <typename _Tp>
struct is_same<_Tp, _Tp> : public true_type {};

}  // namespace ft

#endif
