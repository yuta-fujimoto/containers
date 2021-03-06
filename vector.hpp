#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <exception>
// #include <iostream>
#include <cstring>
#include <limits>

#include "common.hpp"
#include "lexicographical_compare.hpp"
#include "normal_iterator.hpp"
#include "reverse_iterator.hpp"
#include "vector_utils.hpp"

namespace ft {
template <typename _Tp, typename Allocator = std::allocator<_Tp> >
class vector {
 public:
  typedef _Tp value_type;
  typedef _Tp& reference;
  typedef const _Tp& const_reference;
  typedef _Tp* pointer;
  typedef const _Tp* const_pointer;
  typedef _normal_iterator<pointer, vector> iterator;
  typedef _normal_iterator<const_pointer, vector> const_iterator;
  // reverse_iterator can accept iterator
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef Allocator allocator_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

 private:
  allocator_type alloc;
  iterator first_;
  // end iterator of stored data
  iterator last_;
  // end iterator of allocated memory
  iterator reserved_last_;

  pointer allocate(const size_type& __n) { return (alloc.allocate(__n)); }
  void deallocate() { alloc.deallocate(&*first_, capacity()); }
  void construct(const iterator& __iter) { alloc.construct(__iter.base()); }
  void construct(const iterator& __iter, const_reference __value) {
    alloc.construct(__iter.base(), __value);
  }
  void destroy(pointer __ptr) { alloc.destroy(__ptr); }
  // destroy_until backs last
  void destroy_until(const reverse_iterator& __rbegin,
                     const reverse_iterator& __rend) {
    for (reverse_iterator ri = __rbegin; ri != __rend; ++ri) {
      destroy(ri.base().base());
    }
    last_ = last_ - (__rend - __rbegin);
  }
  void _M_erase_at_end(iterator __pos) { last_ = __pos; }
  size_type _M_check_len(size_type __n, const char* __s) const {
    if (__n > max_size() - size()) throw std::length_error(__s);

    if (size() + __n > capacity() * 2) return (size() + __n);
    return (capacity() * 2 + (__n == 0));
  }

 public:
  explicit vector(const allocator_type& __a = Allocator())
      : alloc(__a), last_(first_), reserved_last_(first_) {}
  explicit vector(std::size_t __size, const value_type& __v = value_type(),
                  Allocator __a = Allocator())
      : alloc(__a), last_(first_), reserved_last_(first_) {
    if (__size > max_size()) throw std::length_error("vector");
    resize(__size, __v);
  }
  template <typename InputIterator>
  vector(InputIterator __first, InputIterator __last,
         const Allocator& __a = Allocator(),
         typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
      : alloc(__a) {
    reserve(std::distance(first_, last_));
    for (InputIterator i = __first; i != __last; ++i) push_back(*i);
  }
  ~vector() {
    clear();
    deallocate();
  }
  vector(const vector& __x, const Allocator& __a = Allocator()) : alloc(__a) {
    *this = __x;
  }
  vector& operator=(const vector& __x) {
    if (this == &__x) return (*this);
    const size_type len = __x.size();
    if (len > capacity()) {
      iterator ptr = allocate(len);

      vector_uninitialized_copy(__x.begin(), __x.end(), ptr);
      destroy_until((last_ - 1), (first_ - 1));
      alloc.deallocate(first_.base(), capacity());

      first_ = ptr;
      reserved_last_ = first_ + len;
      last_ = reserved_last_;
    } else {
      destroy_until((last_ - 1), (first_ - 1));
      vector_uninitialized_copy(__x.begin(), __x.end(), first_);
      last_ = first_ + __x.size();
    }
    return (*this);
  }

  iterator begin() { return (first_); }
  const_iterator begin() const { return (const_iterator(first_.base())); }
  reverse_iterator rbegin() { return (reverse_iterator(last_.base())); }
  const_reverse_iterator rbegin() const {
    return (const_reverse_iterator(last_.base()));
  }
  iterator end() { return (last_); }
  const_iterator end() const { return (const_iterator(last_.base())); }
  reverse_iterator rend() { return (reverse_iterator(first_.base())); }
  const_reverse_iterator rend() const {
    return (const_reverse_iterator(first_.base()));
  }
  size_type size() const { return (last_ - first_); }
  bool empty() const { return (first_ == last_); }
  size_type capacity() const { return (reserved_last_ - first_); }
  const_reference operator[](size_type __i) const { return (first_[__i]); }
  reference operator[](size_type __i) { return (first_[__i]); }
  reference at(size_type __n) {
    if (__n >= size()) throw std::out_of_range("vector");
    return (first_[__n]);
  }
  const_reference at(size_type __n) const {
    if (__n >= size()) throw std::out_of_range("vector");
    return (first_[__n]);
  }
  reference front() { return (*begin()); }
  const_reference front() const { return (*begin()); }
  reference back() { return (*(end() - 1)); }
  const_reference back() const { return (*(end() - 1)); }
  void clear() { _M_erase_at_end(first_); }
  // may need to reallocate memory, so change all member variables
  void reserve(size_type __sz) {
    if (max_size() < __sz) throw std::length_error("vector::reserve");
    if (__sz <= capacity()) return;
    iterator ptr = allocate(__sz);
    size_type old_size = size();

    vector_uninitialized_copy(first_, last_, ptr);
    destroy_until(last_ - 1, first_ - 1);
    alloc.deallocate(first_.base(), capacity());

    first_ = ptr;
    reserved_last_ = first_ + __sz;
    last_ = first_ + old_size;
  }
  void resize(size_type __sz, value_type __c = value_type()) {
    if (__sz > size()) {
      insert(end(), __sz - size(), __c);
    } else if (__sz < size()) {
      erase(begin() + __sz, end());
    }
  }
  void push_back(const_reference __value) {
    if (size() + 1 > capacity()) {
      reserve(_M_check_len(1, "vector"));
    }
    vector_uninitialized_fill(last_, last_ + 1, __value);
    ++last_;
  }
  // std's pop back requires empty() = false and if this is not achieved, segv
  // occurs when reserve(example).
  void pop_back() {
    if (empty()) return;
    destroy(last_.base());
    --last_;
  }
  // reassign container
  template <class InputIterator>
  void assign(
      InputIterator __first, InputIterator __last,
      typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {
    iterator __cur(first_);

    for (; __first != __last && __cur != last_; ++__cur, ++__first) {
      *__cur = *__first;
    }
    if (__first == __last) {
      _M_erase_at_end(__cur);
    } else {
      insert(end(), __first, __last);
    }
  }
  void assign(size_type __n, const value_type& __val) {
    if (__n > capacity()) {
      vector __tmp(__n, __val, get_allocator());
      swap(__tmp);
    } else if (__n > size()) {
      vector_uninitialized_fill(begin(), begin() + __n, __val);
      last_ = begin() + __n;
    } else {
      _M_erase_at_end(std::fill_n(first_, __n, __val));
    }
  }
  // return max_size vector can store
  size_type max_size() const {
    const size_t alloc_max = alloc.max_size();
    size_t div = sizeof(value_type) / 2;
    if (div == 0)
      div = 1;
    const size_t diffmax =
        std::numeric_limits<ptrdiff_t>::max() / div;
    return (std::min(alloc_max, diffmax));
  }
  iterator insert(iterator __position, const value_type& __x) {
    const size_type diff = __position - first_;

    insert(__position, 1, __x);
    return (first_ + diff);
  }
  void insert(iterator __position, size_type __n, const value_type& __x) {
    if (__n == 0) return;
    if (size() + __n > capacity()) {
      const size_type len = _M_check_len(__n, "vector");
      const size_type elems_before = __position - first_;

      iterator new_first = allocate(len);
      iterator new_last;

      vector_uninitialized_fill(new_first + elems_before,
                                new_first + elems_before + __n, __x);
      new_last = vector_uninitialized_copy(first_, __position, new_first);
      new_last = vector_uninitialized_copy(__position, last_, new_last + __n);

      destroy_until(last_ - 1, first_ - 1);
      alloc.deallocate(first_.base(), capacity());

      first_ = new_first;
      last_ = new_last;
      reserved_last_ = first_ + len;
    } else {
      if (__position != last_) {
        vector_uninitialized_copy_backward(__position, last_, last_ + __n);
      }
      vector_uninitialized_fill(__position, __position + __n, __x);
      last_ = last_ + __n;
    }
  }
  template <typename InputIterator>
  void insert(
      iterator __position, InputIterator __first, InputIterator __last,
      typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {
    const size_type n = std::distance(__first, __last);
    if (size() + n > capacity()) {
      const size_type len = _M_check_len(n, "vector");
      const size_type elems_before = std::distance(first_, __position);

      iterator new_first = allocate(len);
      iterator new_last;

      vector_uninitialized_copy(__first, __last, new_first + elems_before);
      new_last = vector_uninitialized_copy(first_, __position, new_first);
      new_last = vector_uninitialized_copy(__position, last_, new_last + n);

      if (last_ != first_) {
        destroy_until(last_ - 1, first_ - 1);
        alloc.deallocate(first_.base(), capacity());
      }

      first_ = new_first;
      last_ = new_last;
      reserved_last_ = first_ + len;
    } else {
      if (__position != last_) {
        vector_uninitialized_copy_backward(__position, last_, last_ + n);
      }
      vector_uninitialized_copy(__first, __last, __position);
      last_ = last_ + n;
    }
  }
  iterator erase(iterator __position) {
    return (erase(__position, __position + 1));
  }
  iterator erase(iterator __first, iterator __last) {
    if (__first != __last) {
      if (__last != end()) std::copy(__last, end(), __first);
      last_ = __first.base() + (end() - __last);
      // std has no destroy
    }
    return (__first);
  }
  void swap(vector& __x) {
    std::swap(alloc, __x.alloc);
    std::swap(first_, __x.first_);
    std::swap(last_, __x.last_);
    std::swap(reserved_last_, __x.reserved_last_);
  }
  allocator_type get_allocator() const { return (alloc); }
};

template <typename _Tp, typename U>
bool operator!=(vector<_Tp, U> const& __left, vector<_Tp, U> const& __right) {
  return (!(__left == __right));
}

template <typename _Tp, typename _Alloc>
bool operator==(vector<_Tp, _Alloc> const& __left,
                vector<_Tp, _Alloc> const& __right) {
  return (__left.size() == __right.size() &&
          std::equal(__left.begin(), __left.end(), __right.begin()));
}

template <typename _Tp, typename _Alloc>
bool operator>(vector<_Tp, _Alloc> const& __left,
               vector<_Tp, _Alloc> const& __right) {
  return (__right < __left);
}

template <typename _Tp, typename _Alloc>
// equal to lexicographical_compare
bool operator<(vector<_Tp, _Alloc> const& __left,
               vector<_Tp, _Alloc> const& __right) {
  return (ft::lexicographical_compare(__left.begin(), __left.end(),
                                      __right.begin(), __right.end()));
}

template <typename _Tp, typename _Alloc>
// not equal to lexicographical_compare
bool operator>=(vector<_Tp, _Alloc> const& __left,
                vector<_Tp, _Alloc> const& __right) {
  return (!(__left < __right));
}

template <typename _Tp, typename _Alloc>
bool operator<=(vector<_Tp, _Alloc> const& left,
                vector<_Tp, _Alloc> const& __right) {
  return (!(__right < left));
}

template <typename _Tp, typename _Alloc>
void swap(vector<_Tp, _Alloc>& __x, vector<_Tp, _Alloc>& __y) {
  __x.swap(__y);
}
}  // namespace ft

#endif
