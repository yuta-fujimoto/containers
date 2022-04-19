#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include "common.hpp"

namespace ft {

// empty class
struct input_iterator_tag {
};
struct output_iterator_tag {
};
struct forward_iterator_tag : public input_iterator_tag {
};
struct bidirectional_iterator_tag : public forward_iterator_tag {
};
struct random_access_iterator_tag : public bidirectional_iterator_tag {
};

template <class _Iterator>
struct iterator_traits {
    typedef typename _Iterator::difference_type difference_type;
    typedef typename _Iterator::value_type value_type;
    typedef typename _Iterator::pointer pointer;
    typedef typename _Iterator::reference reference;
    typedef typename _Iterator::iterator_category iterator_category;
};

// specialization for pointer
template <class _Tp>
struct iterator_traits<_Tp*> {
    typedef ptrdiff_t difference_type;
    typedef _Tp value_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
    typedef std::random_access_iterator_tag iterator_category;
};

// specialization for const pointer
template <class _Tp>
struct iterator_traits<const _Tp*> {
    typedef ptrdiff_t difference_type;
    typedef _Tp value_type;
    typedef const _Tp* pointer;
    typedef const _Tp& reference;
    typedef std::random_access_iterator_tag iterator_category;
};
}

#endif
