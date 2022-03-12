#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <exception>
#include <iostream>
#include <limits>

#include "common.hpp"
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
  iterator first;
  // end iterator of stored data
  iterator last;
  // end iterator of allocated memory
  iterator reserved_last;

  pointer allocate(size_type n) { return (alloc.allocate(n)); }
  void deallocate() { alloc.deallocate(&*first, capacity()); }
  void construct(iterator iter) { alloc.construct(&*iter); }
  void construct(iterator iter, const_reference value) {
    alloc.construct(&*iter, value);
  }
  void destroy(pointer ptr) { alloc.destroy(ptr); }
  // destroy_until backs last
  void destroy_until(reverse_iterator rbegin, reverse_iterator rend) {
    for (; rbegin != rend; ++rbegin, --last) {
      destroy(&*rbegin);
    }
  }

 public:
  vector(const allocator_type& a = Allocator())
      : alloc(a), last(first), reserved_last(first) {}
  vector(std::size_t size, const value_type& v = value_type(),
         Allocator a = Allocator())
      : alloc(a) {
    resize(size, v);
  }
  vector(const_iterator first, const_iterator last,
         const Allocator& a = Allocator())
      : vector(a) {
    reserve(last - first);
    for (const_iterator i = first; i != last; ++i) push_back(*i);
  }
  vector(const_reverse_iterator first, const_reverse_iterator last,
         const Allocator& a = Allocator())
      : alloc(a) {
    reserve(last - first);
    for (const_reverse_iterator i = first; i != last; ++i) push_back(*i);
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
      iterator old_first = first;
      iterator old_last = last;
      size_type old_capacity = capacity();

      first = ptr;
      reserved_last = first + len;
      last = first;

      for (size_type i = 0; i < len; ++i, ++last) {
        construct(&ptr[i], x[i]);
      }
      for (reverse_iterator riter = reverse_iterator(&*old_last),
                            rend = reverse_iterator(&*old_first);
           riter != rend; ++riter) {
        destroy(&*riter);
      }
      alloc.deallocate(&*old_first, old_capacity);
    } else {
      destroy_until(&*(last), &*(first));
      for (size_type i = 0; i < len; ++i, ++last)
        construct(&first[i], *(x.begin() + i));
    }
    return (*this);
  }

  iterator begin() { return (first); }
  const_iterator begin() const { return (const_iterator(&*first)); }
  reverse_iterator rbegin() { return (reverse_iterator(&*last)); }
  iterator end() { return (last); }
  const_iterator end() const { return (const_iterator(&*last)); }
  reverse_iterator rend() { return (reverse_iterator(&*first)); }
  size_type size() const { return (last - first); }
  bool empty() { return begin() == end(); }
  size_type capacity() const { return (reserved_last - first); }
  const_reference operator[](size_type i) const { return (first[i]); }
  reference operator[](size_type i) { return (first[i]); }
  reference at(size_type n) {
    std::ostringstream os;

    os << "ft_vector::range_check: n (which is " << n
       << ") >= this->size() (which is " << size() << ")";
    if (n >= size()) throw std::out_of_range(os.str());
    return (first[n]);
  }
  const_reference at(size_type n) const {
    std::ostringstream os;

    os << "ft_vector::range_check: n (which is " << n
       << ") >= this->size() (which is " << size() << ")";
    if (n >= size()) throw std::out_of_range(os.str());
    return (first[n]);
  }
  reference front() { return (*begin()); }
  const_reference front() const { return (*begin()); }
  reference back() { return (*(end() - 1)); }
  const_reference back() const { return (*(end() - 1)); }
  void clear() { destroy_until(rbegin(), rend()); }
  void reserve(size_type sz) {
    if (sz <= capacity()) return;
    iterator ptr = allocate(sz);

    iterator old_first = first;
    iterator old_last = last;
    size_type old_capacity = capacity();

    first = ptr;
    last = first;
    reserved_last = first + sz;

    for (iterator old_iter = old_first; old_iter != old_last;
         ++old_iter, ++last) {
      construct(last, *old_iter);
    }
    for (reverse_iterator riter = reverse_iterator(&*old_last),
                          rend = reverse_iterator(&*old_first);
         riter != rend; ++riter) {
      destroy(&*riter);
    }
    alloc.deallocate(&*old_first, old_capacity);
  }
  void resize(size_type sz, value_type c = value_type()) {
    // please look at ezoe
    if (sz < size()) {
      size_type diff = size() - sz;
      destroy_until(rbegin(), rbegin() + diff);
      last = first + sz;
    } else if (sz > size()) {
      reserve(sz);
      for (; last != reserved_last; ++last) {
        construct(last, c);
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
    construct(last, value);
    ++last;
  }
  // reassign containers
  template <class InputIterator>
  void assign(InputIterator f, InputIterator l) {
    // it may be awfully slow....
    // if (capacity() < l - f)
    *this = vector(f, l);
  }
  void assign(size_type n, const value_type& u) { *this = vector(n, u); }
  // return max_size vector can store
  size_type max_size() const {
    const size_t alloc_max = alloc.max_size();
    const size_t diffmax =
        std::numeric_limits<ptrdiff_t>::max() / sizeof(value_type);
    return (std::min(alloc_max, diffmax));
  }
};
}  // namespace ft

#endif
