#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <exception>
#include <iostream>
#include <limits>

#include "common.hpp"
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"
#include "normal_iterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {
template <typename T, typename Allocator = std::allocator<T> >
class vector {
 public:
  typedef T value_type;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef _normal_iterator<pointer> iterator;
  typedef _normal_iterator<const_pointer> const_iterator;
  typedef _reverse_iterator<const_pointer> const_reverse_iterator;
  typedef _reverse_iterator<pointer> reverse_iterator;
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

  pointer allocate(const size_type& n) { return (alloc.allocate(n)); }
  void deallocate() { alloc.deallocate(&*first_, capacity()); }
  void construct(const iterator& iter) { alloc.construct(&*iter); }
  void construct(const iterator& iter, const_reference& value) {
    alloc.construct(&*iter, value);
  }
  void destroy(pointer ptr) { alloc.destroy(ptr); }
  // destroy_until backs last
  void destroy_until(const reverse_iterator& rbegin,
                     const reverse_iterator& rend) {
    for (reverse_iterator ri = rbegin; ri != rend; ++ri) {
      destroy(&*rbegin);
    }
    last_ = last_ - (rend - rbegin);
  }
  void _M_erase_at_end(iterator pos) { last_ = pos; }

 public:
  vector(const allocator_type& a = Allocator())
      : alloc(a), last_(first_), reserved_last_(first_) {}
  vector(std::size_t size, const value_type& v = value_type(),
         Allocator a = Allocator())
      : alloc(a) {
    resize(size, v);
  }
  template <typename InputIterator>
  vector(InputIterator first, InputIterator last,
         const Allocator& a = Allocator(),
         typename enable_if<!is_integral<InputIterator>::value>::type* = 0)
      : alloc(a) {
    reserve(last - first);
    for (InputIterator i = first; i != last; ++i) push_back(*i);
  }
  ~vector() {
    clear();
    deallocate();
  }
  vector(const vector& x, const Allocator& a = Allocator()) : alloc(a) {
    *this = x;
  }
  vector& operator=(const vector& x) {
    if (this == &x) return (*this);
    const size_type len = x.size();
    if (len > capacity()) {
      iterator ptr = allocate(len);
      iterator old_first = first_;
      iterator old_last = last_;
      size_type old_capacity = capacity();

      first_ = ptr;
      reserved_last_ = first_ + len;
      last_ = reserved_last_;

      // for (size_type i = 0; i < len; ++i, ++last_) {
      //   construct(&ptr[i], x[i]);
      // }

      std::copy(x.begin(), x.end(), first_);
      for (reverse_iterator riter = reverse_iterator(&*old_last),
                            rend = reverse_iterator(&*old_first);
           riter != rend; ++riter) {
        destroy(&*riter);
      }
      alloc.deallocate(old_first.base(), old_capacity);
    } else {
      destroy_until(&*(last_ - 1), &*(first_ - 1));
      for (size_type i = 0; i < len; ++i, ++last_)
        construct(&first_[i], *(x.begin() + i));
    }
    return (*this);
  }

  iterator begin() { return (first_); }
  const_iterator begin() const { return (const_iterator(&*first_)); }
  reverse_iterator rbegin() { return (reverse_iterator(&*last_)); }
  const_reverse_iterator rbegin() const { return (const_reverse_iterator(&*last_)); }
  iterator end() { return (last_); }
  const_iterator end() const { return (const_iterator(&*last_)); }
  reverse_iterator rend() { return (reverse_iterator(&*first_)); }
  const_reverse_iterator rend() const { return (const_reverse_iterator(&*first_)); }
  size_type size() const { return (last_ - first_); }
  bool empty() const { return begin() == end(); }
  size_type capacity() const { return (reserved_last_ - first_); }
  const_reference operator[](size_type i) const { return (first_[i]); }
  reference operator[](size_type i) { return (first_[i]); }
  reference at(size_type n) {
    if (n >= size()) throw std::out_of_range("vector");
    return (first_[n]);
  }
  const_reference at(size_type n) const {
    if (n >= size()) throw std::out_of_range("vector");
    return (first_[n]);
  }
  reference front() { return (*begin()); }
  const_reference front() const { return (*begin()); }
  reference back() { return (*(end() - 1)); }
  const_reference back() const { return (*(end() - 1)); }
  void clear() {
    _M_erase_at_end(first_);
    // destroy_until(rbegin(), rend());
  }
  // may need to reallocate memory, so change all member var
  void reserve(size_type sz) {
    if (max_size() < sz) throw std::length_error("vector::reserve");
    if (sz <= capacity()) return;
    iterator ptr = allocate(sz);

    iterator old_first = first_;
    iterator old_last = last_;
    size_type old_capacity = capacity();

    first_ = ptr;
    reserved_last_ = first_ + sz;
    last_ = first_ + (old_last - old_first);

    std::copy(old_first, old_last, first_);
    for (reverse_iterator riter = reverse_iterator(&*old_last),
                          rend = reverse_iterator(&*old_first);
         riter != rend; ++riter) {
      destroy(&*riter);
    }
    alloc.deallocate(&*old_first, old_capacity);
  }
  void resize(size_type sz, value_type c = value_type()) {
    if (sz > size())
      insert(end(), sz - size(), c);
    else if (sz < size())
      erase(begin() + sz, end());
  }
  void push_back(const_reference value) {
    if (size() + 1 > capacity()) {
      size_type c = size();
      if (c == 0)
        c = 1;
      else
        c *= 2;
      reserve(c);
    }
    construct(last_, value);
    ++last_;
  }
  // std's pop back requires empty() = false and if this is not achieved, segv
  // occurs when reserve(example).
  void pop_back(void) {
    if (empty()) return;
    destroy(last_.base());
    last_--;
  }
  // reassign container
  template <class InputIterator>
  void assign(
      InputIterator __first, InputIterator __last,
      typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {
    iterator __cur(first_);

    for (; __first != __last && __cur != last_; ++__cur, ++__first)
      *__cur = *__first;
    if (__first == __last)
      _M_erase_at_end(__cur);
    else
      insert(end(), __first, __last);
  }
  void assign(size_type __n, const value_type& __val) {
    if (__n > capacity()) {
      vector __tmp(__n, __val, get_allocator());
      swap(__tmp);
    } else if (__n > size()) {
      std::fill(begin(), begin() + __n, __val);
      last_ = begin() + __n;
      // ???
      // const size_type  __add = __n - size();
      // std::uninitialized_fill_n();
    } else {
      _M_erase_at_end(std::fill_n(first_, __n, __val));
    }
    // *this = vector(n, u);
  }
  // return max_size vector can store
  size_type max_size() const {
    const size_t alloc_max = alloc.max_size();
    const size_t diffmax =
        std::numeric_limits<ptrdiff_t>::max() * 2 / sizeof(value_type);
    return (std::min(alloc_max, diffmax));
  }
  iterator insert(iterator position, const value_type& x) {
    const size_type diff = position - first_;

    insert(position, 1, x);
    return (first_ + diff);
  }
  void insert(iterator position, size_type n, const value_type& x) {
    if (size() + n > capacity()) {
      const size_type diff = position - first_;
      // reserve updates first member variable
      if (size() + n > capacity() * 2)
        reserve(size() + n);
      else
        reserve(capacity() * 2);
      position = first_ + diff;
    }
    if (position != last_) {
      std::copy_backward(position, position + size(), position + n + size());
    }
    std::fill(position, position + difference_type(n), x);
    last_ = last_ + n;
  }
  template <typename InputIterator>
  void insert(
      iterator position, InputIterator first, InputIterator last,
      typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {
    const size_type n = last - first;
    const size_type diff = position - first_;
    if (size() + n > capacity()) {
      if (size() + n > capacity() * 2)
        reserve(size() + n);
      else
        reserve(capacity() * 2);
      position = first_ + diff;
    }
    if (position != last_) {
      std::copy_backward(position, position + size(), position + n + size());
    }
    // std::fill(position, position + difference_type(n), x);
    for (size_type i = 0; i != n; ++i, ++last_) {
      // need to construct
      construct(position + i, *(first + i));
    }
  }
  iterator erase(iterator position) { return (erase(position, position + 1)); }
  iterator erase(iterator __first, iterator __last) {
    iterator old_last = last_;

    if (__first != __last) {
      if (__last != end()) std::copy(__last, end(), __first);
      last_ = __first.base() + (end() - __last);
      // destroy_until(end().base(), );
    }
    return (__first);
  }
  void swap(vector& x) {
    std::swap(alloc, x.alloc);
    std::swap(first_, x.first_);
    std::swap(last_, x.last_);
    std::swap(reserved_last_, x.reserved_last_);
  }
  allocator_type get_allocator() const { return (alloc); }
};

template <typename T, typename U>
bool operator!=(vector<T, U> const& left, vector<T, U> const& right) {
  return (!(left == right));
  // return (ft::lexicographical_compare(begin(), end(), right.begin(),
  // right.end(),
  //                                 std::not_equal_to<value_type>()));
}

template <typename _T, typename _Alloc>
bool operator==(vector<_T, _Alloc> const& left,
                vector<_T, _Alloc> const& right) {
  return (left.size() == right.size() &&
          std::equal(left.begin(), left.end(), right.begin()));
}

template <typename _T, typename _Alloc>
bool operator>(vector<_T, _Alloc> const& left,
               vector<_T, _Alloc> const& right) {
  return (right < left);
}

template <typename _T, typename _Alloc>
// equal to lexicographical_compare
bool operator<(vector<_T, _Alloc> const& left,
               vector<_T, _Alloc> const& right) {
  return (ft::lexicographical_compare(left.begin(), left.end(), right.begin(),
                                      right.end()));
}

template <typename _T, typename _Alloc>
// not equal to lexicographical_compare
bool operator>=(vector<_T, _Alloc> const& left,
                vector<_T, _Alloc> const& right) {
  return (!(left < right));
}

template <typename _T, typename _Alloc>
bool operator<=(vector<_T, _Alloc> const& left,
                vector<_T, _Alloc> const& right) {
  return (!(right < left));
}

template <typename _T, typename _Alloc>
void swap(vector<_T, _Alloc>& x, vector<_T, _Alloc>& y) {
  x.swap(y);
}
}  // namespace ft

#endif
