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

 private:
  allocator_type alloc;
  iterator first_;
  // end iterator of stored data
  iterator last_;
  // end iterator of allocated memory
  iterator reserved_last_;

  pointer allocate(size_type n) { return (alloc.allocate(n)); }
  void deallocate() { alloc.deallocate(&*first_, capacity()); }
  void construct(iterator iter) { alloc.construct(&*iter); }
  void construct(iterator iter, const_reference value) {
    alloc.construct(&*iter, value);
  }
  void destroy(pointer ptr) { alloc.destroy(ptr); }
  // destroy_until backs last
  void destroy_until(reverse_iterator rbegin, reverse_iterator rend) {
    for (; rbegin != rend; ++rbegin, --last_) {
      destroy(&*rbegin);
    }
  }

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
      : vector(a) {
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
      last_ = first_;

      for (size_type i = 0; i < len; ++i, ++last_) {
        construct(&ptr[i], x[i]);
      }
      for (reverse_iterator riter = reverse_iterator(&*old_last),
                            rend = reverse_iterator(&*old_first);
           riter != rend; ++riter) {
        destroy(&*riter);
      }
      alloc.deallocate(&*old_first, old_capacity);
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
  iterator end() { return (last_); }
  const_iterator end() const { return (const_iterator(&*last_)); }
  reverse_iterator rend() { return (reverse_iterator(&*first_)); }
  size_type size() const { return (last_ - first_); }
  bool empty() { return begin() == end(); }
  size_type capacity() const { return (reserved_last_ - first_); }
  bool operator!=(vector const& right) const {
    return (!(*this == right));
    // return (ft::lexicographical_compare(begin(), end(), right.begin(), right.end(),
    //                                 std::not_equal_to<value_type>()));
  }
  bool operator==(vector const& right) const {
    return (size() == right.size() && std::equal(begin(), end(), right.begin()));
  }
  bool operator>(vector const& right) const {
    return (right < *this);
  }
  // equal to lexicographical_compare
  bool operator<(vector const& right) const {
    return (ft::lexicographical_compare(begin(), end(), right.begin(), right.end()));
  }
  // not equal to lexicographical_compare
  bool operator>=(vector const& right) const {
    return (!(*this < right));
  }
  bool operator<=(vector const& right) const {
    return (!(right < *this));
  }
  const_reference operator[](size_type i) const { return (first_[i]); }
  reference operator[](size_type i) { return (first_[i]); }
  reference at(size_type n) {
    std::ostringstream os;

    os << "ft_vector::range_check: n (which is " << n
       << ") >= this->size() (which is " << size() << ")";
    if (n >= size()) throw std::out_of_range(os.str());
    return (first_[n]);
  }
  const_reference at(size_type n) const {
    std::ostringstream os;

    os << "ft_vector::range_check: n (which is " << n
       << ") >= this->size() (which is " << size() << ")";
    if (n >= size()) throw std::out_of_range(os.str());
    return (first_[n]);
  }
  reference front() { return (*begin()); }
  const_reference front() const { return (*begin()); }
  reference back() { return (*(end() - 1)); }
  const_reference back() const { return (*(end() - 1)); }
  void clear() { destroy_until(rbegin(), rend()); }
  // may need to reallocate memory, so change all member var
  void reserve(size_type sz) {
    if (sz <= capacity()) return;
    iterator ptr = allocate(sz);

    iterator old_first = first_;
    iterator old_last = last_;
    size_type old_capacity = capacity();

    first_ = ptr;
    last_ = first_;
    reserved_last_ = first_ + sz;

    for (iterator old_iter = old_first; old_iter != old_last;
         ++old_iter, ++last_) {
      construct(last_, *old_iter);
    }
    for (reverse_iterator riter = reverse_iterator(&*old_last),
                          rend = reverse_iterator(&*old_first);
         riter != rend; ++riter) {
      destroy(&*riter);
    }
    alloc.deallocate(&*old_first, old_capacity);
  }
  void resize(size_type sz, value_type c = value_type()) {
    if (sz < size()) {
      size_type diff = size() - sz;
      destroy_until(rbegin(), rbegin() + diff);
    } else if (sz > size()) {
      reserve(sz);
      for (; last_ != reserved_last_; ++last_) {
        construct(last_, c);
      }
    }
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
    destroy(&*last_);
    last_--;
  }
  // reassign containers
  // is it okay to template??
  template <class InputIterator>
  void assign(
      InputIterator first, InputIterator last,
      typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {
    // it may be awfully slow....
    // if (capacity() < l - f)
    *this = vector(first, last);
  }
  void assign(size_type n, const value_type& u) { *this = vector(n, u); }
  // return max_size vector can store
  size_type max_size() const {
    const size_t alloc_max = alloc.max_size();
    const size_t diffmax =
        std::numeric_limits<ptrdiff_t>::max() / sizeof(value_type);
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
      for (size_type i = size(); i > 0;) {
        --i;
        *(position + n + i) = *(position + i);
      }
    }
    for (size_type i = 0; i != n; ++i, ++last_) {
      construct(position + i, x);
    }
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
      for (size_type i = size(); i > diff;) {
        --i;
        // only copy
        *(position + n + i) = *(position + i);
      }
    }
    for (size_type i = 0; i != n; ++i, ++last_) {
      // need to construct
      construct(position + i, *(first + i));
    }
  }
  iterator erase(iterator position) { return (erase(position, position + 1)); }
  iterator erase(iterator first, iterator last) {
    const size_type diff = last - first;
    iterator old_last = last_;

    destroy_until(&*(last - 1), &*(first - 1));
    for (iterator it = first; it != (old_last - diff); ++it) {
      // only copy
      *it = *(it + diff);
    }
    return (first);
  }
  void swap(vector& x) {
    iterator temp;
    allocator_type allocTemp;

    // alloc
    allocTemp = x.alloc;
    x.alloc = alloc;
    alloc = allocTemp;

    // first
    temp = x.first_;
    x.first_ = first_;
    first_ = temp;

    // last
    temp = x.last_;
    x.last_ = last_;
    last_ = temp;

    // reserved_last
    temp = x.reserved_last_;
    x.reserved_last_ = reserved_last_;
    reserved_last_ = temp;
  }
  allocator_type get_allocator() const { return (alloc); }
};
}  // namespace ft

#endif
