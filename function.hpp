#ifndef FUNCTION_H_
#define FUNCTION_H_

namespace ft {
template <typename _Arg, typename _Result>
struct unary_function {
  typedef _Arg argument_type;
  typedef _Result result_type;
};

template <typename _Pair>
struct _Select1st
    : public std::unary_function<_Pair, typename _Pair::first_type> {
  typename _Pair::first_type& operator()(_Pair& __x) const { return __x.first; }

  const typename _Pair::first_type& operator()(const _Pair& __x) const {
    return __x.first;
  }
};

template <typename _Tp>
struct _Identity : public unary_function<_Tp, _Tp> {
  _Tp& operator()(_Tp& __x) const { return __x; }

  const _Tp& operator()(const _Tp& __x) const { return __x; }
};

template <typename _Tp>
struct _Identity<const _Tp> : _Identity<_Tp> {};

}  // namespace ft



#endif
