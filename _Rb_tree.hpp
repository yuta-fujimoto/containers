#ifndef RBTREE_H_
#define RBTREE_H_

/** @file RBtree.hpp
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{map,set}
 */

#include <iostream>
#include <limits>

#include "enable_if.hpp"
#include "iterator_traits.hpp"
#include "lexicographical_compare.hpp"
#include "pair.hpp"
#include "reverse_iterator.hpp"

namespace ft {
enum _RB_tree_color { BLACK = 0, RED = 1, HEAD = 2 };
enum _Dir { LEFT = false, RIGHT = true };

// RBnode :
template <typename _Val>
class _RB_tree_node {
 public:
  typedef _RB_tree_node<_Val> *_Link_type;
  typedef const _RB_tree_node<_Val> *_Const_Link_type;

  _Val *val;
  _Link_type parent;
  _Link_type child[2];
  _RB_tree_color color;

  _RB_tree_node() { this->color = RED; }
  void print(int level) {
    for (int i = 0; i < level; ++i) std::cout << '\t';
    if (color == RED)
      std::cout << "\033[31m"
                << "[" << val->first << ", " << val->second << "]"
                << "\033[0m" << std::endl;
    else
      std::cout << "[" << val->first << ", " << val->second << "]" << std::endl;
  }
};

template <typename _Val>
_RB_tree_node<_Val> *_Tree_minimum(_RB_tree_node<_Val> *N) {
  if (N == NULL) return (NULL);
  while (N->child[LEFT] != NULL) N = N->child[LEFT];
  return (N);
}
template <typename _Val>
_RB_tree_node<_Val> *_Tree_maximum(_RB_tree_node<_Val> *N) {
  if (N == NULL) return (NULL);
  while (N->child[RIGHT] != NULL) N = N->child[RIGHT];
  return (N);
}
// the node with the smallest key greater than n's key
template <typename _Val>
_RB_tree_node<_Val> *_Tree_successor(_RB_tree_node<_Val> *_X) {
  if (_X->child[RIGHT] != NULL) return (_Tree_minimum(_X->child[RIGHT]));
  _RB_tree_node<_Val> *_Y = _X->parent;
  while (_Y != NULL && _X == _Y->child[RIGHT]) {
    _X = _Y;
    _Y = _Y->parent;
  }
  // size(tree) != 1
  if (_X->child[RIGHT] != _Y) {
    _X = _Y;
  }
  return (_X);
}
// the node with the largest key smaller than n's key
template <typename _Val>
_RB_tree_node<_Val> *_Tree_predecessor(_RB_tree_node<_Val> *_X) {
  // _X is _M_header (not root)
  if (_X->color == HEAD) return (_X->child[RIGHT]);
  if (_X->child[LEFT] != NULL) return (_Tree_maximum(_X->child[LEFT]));
  _RB_tree_node<_Val> *_Y = _X->parent;
  while (_Y != NULL && _X == _Y->child[LEFT]) {
    _X = _Y;
    _Y = _Y->parent;
  }
  return (_Y);
}

template <typename _Val>
_RB_tree_node<_Val> *_Rb_tree_increment(_RB_tree_node<_Val> *N) {
  return (_Tree_successor(N));
}

template <typename _Val>
const _RB_tree_node<_Val> *_Rb_tree_increment(_RB_tree_node<_Val> const *N) {
  return (_Tree_successor(const_cast<_RB_tree_node<_Val> *>(N)));
}

template <typename _Val>
_RB_tree_node<_Val> *_Rb_tree_decrement(_RB_tree_node<_Val> *N) {
  return (_Tree_predecessor(N));
}

template <typename _Val>
const _RB_tree_node<_Val> *_Rb_tree_decrement(_RB_tree_node<_Val> const *N) {
  return (_Tree_predecessor(const_cast<_RB_tree_node<_Val> *>(N)));
}

template <typename T>
struct _Rb_tree_iterator {
  typedef T value_type;
  typedef T &reference;
  typedef T *pointer;

  typedef bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;

  typedef _Rb_tree_iterator<T> _Self;
  typedef typename _RB_tree_node<T>::_Link_type _Link_type;

  _Link_type _M_node;

  _Rb_tree_iterator(_Link_type N = NULL) : _M_node(N) {}
  reference operator*() const { return (*(_M_node->val)); }
  pointer operator->() const { return (_M_node->val); }
  _Self &operator++() {
    _M_node = _Rb_tree_increment(_M_node);
    return (*this);
  }
  _Self operator++(int) {
    _Self __tmp = *this;
    _M_node = _Rb_tree_increment(_M_node);
    return (__tmp);
  }
  _Self &operator--() {
    _M_node = _Rb_tree_decrement(_M_node);
    return (*this);
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    _M_node = _Rb_tree_decrement(_M_node);
    return (__tmp);
  }

  friend bool operator==(const _Self &__x, const _Self &__y) {
    return __x._M_node == __y._M_node;
  }

  friend bool operator!=(const _Self &__x, const _Self &__y) {
    return __x._M_node != __y._M_node;
  }
};

template <typename T>
struct _Rb_tree_const_iterator {
  typedef T value_type;
  typedef const T &reference;
  typedef const T *pointer;

  typedef _Rb_tree_iterator<T> iterator;

  typedef bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;

  typedef _Rb_tree_const_iterator<T> _Self;
  typedef const _RB_tree_node<T> *_Link_type;

  _Link_type _M_node;

  _Rb_tree_const_iterator(_Link_type N = NULL) : _M_node(N) {}
  _Rb_tree_const_iterator(const iterator &__it) : _M_node(__it._M_node) {}
  iterator _M_const_cast() const {
    return iterator(const_cast<typename iterator::_Link_type>(_M_node));
  }
  reference operator*() const { return (*(_M_node->val)); }
  pointer operator->() const { return (_M_node->val); }
  _Self &operator++() {
    _M_node = _Rb_tree_increment(_M_node);
    return (*this);
  }
  _Self operator++(int) {
    _Self __tmp = *this;
    _M_node = _Rb_tree_increment(_M_node);
    return (__tmp);
  }
  _Self &operator--() {
    _M_node = _Rb_tree_decrement(_M_node);
    return (*this);
  }
  _Self operator--(int) {
    _Self __tmp = *this;
    _M_node = _Rb_tree_decrement(_M_node);
    return (__tmp);
  }
  friend bool operator==(const _Self &__x, const _Self &__y) {
    return (__x._M_node == __y._M_node);
  }
  friend bool operator!=(const _Self &__x, const _Self &__y) {
    return (__x._M_node != __y._M_node);
  }
};

template <typename _Key_compare>
struct _Rb_tree_key_compare {
  _Key_compare _M_key_compare;

  _Rb_tree_key_compare() : _M_key_compare() {}
  _Rb_tree_key_compare(const _Key_compare &__comp) : _M_key_compare(__comp) {}
};

template <typename _Val>
struct _Rb_tree_header : public _RB_tree_node<_Val> {
  // PARENT: ROOT
  // LEFT: BEGIN
  // RIGHT: END - 1
  size_t _M_node_count;

  _Rb_tree_header() {
    this->color = HEAD;
    _M_reset();
  }
  void _M_move_data(_Rb_tree_header &_from) {
    this->color = _from.color;
    this->parent = _from.parent;
    this->child[LEFT] = _from.child[LEFT];
    this->child[RIGHT] = _from.child[RIGHT];
    // TODO
    // this->parent->parent = &_from;
    _M_node_count = _from._M_node_count;

    _from._M_reset();
  }
  void _M_reset() {
    this->parent = NULL;
    this->child[LEFT] = this;
    this->child[RIGHT] = this;
    _M_node_count = 0;
  }
};

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare,
          typename _Alloc = std::allocator<_Val> >
class _Rb_tree {
 private:
  typedef typename _Alloc::template rebind<_RB_tree_node<_Val> >::other
      _Node_allocator;
  typedef _RB_tree_node<_Val> *_Link_type;
  typedef const _RB_tree_node<_Val> *_Const_Link_type;

  struct _Rb_tree_impl : public _Rb_tree_key_compare<_Compare>,
                         public _Rb_tree_header<_Val> {
    typedef _Rb_tree_key_compare<_Compare> _Base_key_compare;

    _Rb_tree_impl() {}

    _Rb_tree_impl(const _Rb_tree_impl &__x)
        : _Base_key_compare(__x._M_key_compare) {}

    _Rb_tree_impl(const _Compare &__comp) : _Base_key_compare(__comp) {}

    _Rb_tree_impl(const _Compare &__comp, const _Node_allocator &__a)
        : _Base_key_compare(__comp), _alloc(__a) {}

    _Node_allocator _node_alloc;
    _Alloc _alloc;
  };
  _Rb_tree_impl _M_header;

  _Link_type _M_get_node(void) { return (_M_header._node_alloc.allocate(1)); }
  void _M_construct_node(_Link_type _node, const _Val &x) {
    _node->color = RED;
    _node->child[LEFT] = NULL;
    _node->child[RIGHT] = NULL;
    _node->parent = NULL;
    _node->val = _M_header._alloc.allocate(1);
    _M_header._alloc.construct(_node->val, x);
    // in c++ , try catch is used
  }
  _Link_type _M_create_node(const _Val &x) {
    _Link_type _tmp = _M_get_node();
    _M_construct_node(_tmp, x);
    return _tmp;
  }
  void _M_drop_node(_Link_type _p) {
    _M_header._alloc.destroy(_p->val);
    _M_header._alloc.deallocate(_p->val, 1);
    _M_header._node_alloc.deallocate(_p, 1);
  }
  bool childDir(_Link_type N) {
    return (N == (N->parent)->child[RIGHT] ? RIGHT : LEFT);
  }
  _Link_type _Rotate_dir_root(_Link_type P, bool dir) {
    _Link_type G = P->parent;       // GrandParent
    _Link_type S = P->child[!dir];  // Son
    if (S == NULL) return (NULL);
    _Link_type C = S->child[dir];

    P->child[!dir] = C;
    if (C != NULL) C->parent = P;

    S->child[dir] = P;
    P->parent = S;
    S->parent = G;

    if (G != &_M_header)
      G->child[P == G->child[RIGHT] ? RIGHT : LEFT] = S;
    else {
      _M_header.parent = S;
      // S->parent = &_M_header;     S->parent = G;
    }
    return (S);  // new root of subtree
  }
  // insert and rebalance
  _Link_type _Rb_insert2(_Link_type N, _Link_type P, bool dir) {
    _Link_type G;  // GrandParent
    _Link_type U;  // Uncle
    _Link_type Inserted = N;

    N->parent = P;
    if (P == &_M_header) {
      _M_header.parent = N;
      N->parent = &_M_header;
      return (Inserted);
    }
    P->child[dir] = N;
    do {
      if (P->color == BLACK)  // Case_I1 (P: BLACK)
        return (Inserted);
      G = P->parent;
      if (G == &_M_header) goto Case_I4;  // Case_I4 (P: RED and ROOT)
      dir = childDir(P);
      U = G->child[!dir];
      if (U == NULL || U->color == BLACK)  // Case_I56 (U: BLACK)
        goto Case_I56;
      // Case_I2 (P+U: RED)
      P->color = BLACK;
      U->color = BLACK;
      G->color = RED;
      N = G;
      P = N->parent;
    } while (P != &_M_header);
    // Case_I3 (N: ROOT)
    return (Inserted);
  Case_I4:
    P->color = BLACK;
    return (Inserted);
  Case_I56:
    if (N == P->child[!dir]) {
      // Case_I5 (P: RED, U: BLACK, N: inner grandchild of G)
      _Rotate_dir_root(P, dir);
      N = P;
      P = G->child[dir];
    }
    // Case_I6 (P: RED, U: BLACK, N: outer grandchild of G)
    _Rotate_dir_root(G, !dir);
    P->color = BLACK;
    G->color = RED;
    return (Inserted);
  }
  // search where to insert
  _Link_type _Rb_insert1(_Link_type N) {
    _Link_type P;

    if (_M_header.parent == NULL) return (_Rb_insert2(N, &_M_header, LEFT));
    P = _M_header.parent;
    while (true) {
      if (_M_header._M_key_compare(_KeyOfValue()(*P->val),
                                   _KeyOfValue()(*N->val))) {
        if (P->child[RIGHT] == NULL) return (_Rb_insert2(N, P, RIGHT));
        P = P->child[RIGHT];
      } else if (_M_header._M_key_compare(_KeyOfValue()(*N->val),
                                          _KeyOfValue()(*P->val))) {
        if (P->child[LEFT] == NULL) return (_Rb_insert2(N, P, LEFT));
        P = P->child[LEFT];
      } else {
        return (P);
      }
    }
  }

  // REPLACE NODE N WITH R
  void _Subtree_shift(_Link_type N, _Link_type R) {
    if (N == _M_header.parent) {
      _M_header.parent = R;
      R->parent = &_M_header;
    } else
      N->parent->child[childDir(N)] = R;
    if (R != NULL) R->parent = N->parent;
  }
  // N != ROOT && N->color == BLACK && N has no child
  void _Rb_erase2(_Link_type N) {
    _Link_type P = N->parent;
    bool dir;
    _Link_type S;
    _Link_type C;
    _Link_type D;

    // P != NULL
    dir = childDir(N);
    P->child[dir] = NULL;
    goto Start_D;
    do {
      dir = childDir(N);
    Start_D:
      S = P->child[!dir];
      D = S->child[!dir];
      C = S->child[dir];
      if (S->color == RED)  // Case_D3 (S: RED)
        goto Case_D3;
      if (D != NULL && D->color == RED)  // Case_D6 (D: RED, S: BLACK)
        goto Case_D6;
      if (C != NULL && C->color == RED)  // Case_D6 (C: RED, S+D: BLACK)
        goto Case_D5;
      if (P->color == RED)  // Case_D4 (P: RED, C+S+D: BLACK)
        goto Case_D4;
      // Case_D1 (P+C+S+D: BLACK)
      S->color = RED;
      N = P;
      P = N->parent;
    } while (P != &_M_header);
    // Case_D2 (P==NULL)
    return;
  Case_D3:                     // Case_D3 (S: RED, P+C+D: BLACK)
    _Rotate_dir_root(P, dir);  // P may be root

    P->color = RED;
    S->color = BLACK;
    S = C;

    D = S->child[!dir];
    if (D != NULL && D->color == RED) goto Case_D6;
    C = S->child[dir];
    if (C != NULL && C->color == RED) goto Case_D5;
  Case_D4:
    S->color = RED;
    P->color = BLACK;
    return;
  Case_D5:
    _Rotate_dir_root(S, !dir);
    S->color = RED;
    C->color = BLACK;
    D = S;
    S = C;
    // now: D red && S black
    // fall through to Case_d&
  Case_D6:
    _Rotate_dir_root(P, dir);
    S->color = P->color;
    P->color = BLACK;
    D->color = BLACK;
    return;
  }
  void _Rb_erase1(_Link_type N) {
    if (N == _M_header.parent && N->child[LEFT] == NULL &&
        N->child[RIGHT] == NULL) {
      _M_header.parent = NULL;
    } else if (N->child[LEFT] && N->child[RIGHT]) {
      _Link_type R = _Tree_successor(N);

      if (R->color == BLACK) _Rb_erase2(R);
      R->color = N->color;
      if (R->parent != N) {
        _Subtree_shift(R, R->child[RIGHT]);
        R->child[RIGHT] = N->child[RIGHT];
        R->child[RIGHT]->parent = R;
      }
      _Subtree_shift(N, R);
      R->child[LEFT] = N->child[LEFT];
      if (R->child[LEFT] != NULL) R->child[LEFT]->parent = R;
    } else if (N->color == RED) {
      _Subtree_shift(N, NULL);
    } else {
      if (N->child[LEFT] != NULL || N->child[RIGHT] != NULL) {
        _Link_type R =
            N->child[LEFT] != NULL ? N->child[LEFT] : N->child[RIGHT];

        R->color = BLACK;
        _Subtree_shift(N, R);
      } else {
        _Rb_erase2(N);
      }
    }
  }
  _Link_type _Rb_find1(_Link_type N, const _Key k) const {
    if (N == NULL) return (NULL);
    if (_M_header._M_key_compare(k, _KeyOfValue()(*N->val)))
      return (_Rb_find1(N->child[LEFT], k));
    if (_M_header._M_key_compare(_KeyOfValue()(*N->val), k))
      return (_Rb_find1(N->child[RIGHT], k));
    return (N);
  }
  void _Rb_clear1(_Link_type N) {
    if (N == NULL) return;
    _Rb_clear1(N->child[LEFT]);
    _Rb_clear1(N->child[RIGHT]);
    _M_drop_node(N);
  }

  struct _Alloc_node {
    _Alloc_node(_Rb_tree &__t) : _M_t(__t) {}

    template <typename _Arg>
    _Link_type operator()(const _Arg &__arg) const {
      return _M_t._M_create_node(__arg);
    }

   private:
    _Rb_tree &_M_t;
  };

 public:
  typedef _Rb_tree_iterator<_Val> iterator;
  typedef _Rb_tree_const_iterator<_Val> const_iterator;
  typedef _reverse_iterator<iterator> reverse_iterator;
  typedef _reverse_iterator<const_iterator> const_reverse_iterator;

  typedef _Key key_type;
  typedef _Val value_type;
  typedef value_type *pointer;
  typedef const value_type *const_pointer;
  typedef value_type &reference;
  typedef const value_type &const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef _Alloc allocator_type;

  // _Rb_tree() {}
  _Rb_tree(const _Compare &__comp = _Compare(),
           const allocator_type &__a = allocator_type())
      : _M_header(__comp, _Node_allocator(__a)) {}
  _Rb_tree(const _Rb_tree &__x) : _M_header(__x._M_header) {
    if (__x._M_root() != 0) _M_root() = _M_copy(__x);
  }
  ~_Rb_tree() { _M_erase(_M_begin()); }
  _Rb_tree(_Link_type const &rhs) { *this = rhs; }
  _Rb_tree &operator=(_Rb_tree const &rhs) {
    if (this != &rhs) {
      _Rb_clear1(_M_header.parent);
      _M_root() = _M_copy(rhs);
    }
    return (*this);
  }
  _Link_type &_M_root() { return (_M_header.parent); }
  _Const_Link_type _M_root() const { return (_M_header.parent); }
  _Link_type &_M_leftmost() { return (_M_header.child[LEFT]); }
  _Const_Link_type _M_leftmost() const { return (_M_header.child[LEFT]); }
  _Link_type &_M_rightmost() { return (_M_header.child[RIGHT]); }
  _Const_Link_type _M_rightmost() const { return (_M_header.child[RIGHT]); }
  size_type size() const { return (_M_header._M_node_count); }
  size_type max_size() const {
    size_t div = sizeof(_Link_type) * 4 + (sizeof(value_type) / 8) * 8;

    return (std::numeric_limits<size_type>::max() / div);
  }
  _Link_type _M_begin() { return (_M_header.parent); }
  _Const_Link_type _M_begin() const { return (_M_header.parent); }
  _Link_type _M_end() { return (&_M_header); }
  _Const_Link_type _M_end() const { return (&_M_header); }
  _Link_type _S_left(_Link_type __x) {
    return (static_cast<_Link_type>(__x->child[0]));
  }
  _Const_Link_type _S_left(_Const_Link_type __x) {
    return static_cast<_Const_Link_type>(__x->child[0]);
  }
  _Link_type _S_right(_Link_type __x) {
    return static_cast<_Link_type>(__x->child[1]);
  }
  _Const_Link_type _S_right(_Const_Link_type __x) {
    return static_cast<_Const_Link_type>(__x->child[1]);
  }
  template <typename _NodeGen>
  _Link_type _M_clone_node(_Const_Link_type __x, _NodeGen &__node_gen) {
    _Link_type __tmp = __node_gen(*__x->val);
    __tmp->color = __x->color;
    __tmp->child[LEFT] = 0;
    __tmp->child[RIGHT] = 0;
    return (__tmp);
  }
  template <typename _NodeGen>
  _Link_type _M_copy(_Const_Link_type _x, _Link_type _p, _NodeGen &_node_gen) {
    // Structural copy. _x and _p must be non-null.
    _Link_type _top = _M_clone_node(_x, _node_gen);
    _top->parent = _p;

    try {
      if (_x->child[RIGHT])
        _top->child[RIGHT] = _M_copy(_x->child[RIGHT], _top, _node_gen);
      _p = _top;
      _x = _x->child[LEFT];

      while (_x != 0) {
        _Link_type _y = _M_clone_node(_x, _node_gen);
        _p->child[LEFT] = _y;
        _y->parent = _p;
        if (_x->child[RIGHT])
          _y->child[RIGHT] = _M_copy(_x->child[RIGHT], _y, _node_gen);
        _p = _y;
        _x = _x->child[LEFT];
      }
    } catch (...) {
      _M_erase(_top);
      // __throw_exception_again
      throw;
    }
    return (_top);
  }
  template <typename _NodeGen>
  _Link_type _M_copy(const _Rb_tree &__x, _NodeGen &__gen) {
    _Link_type __root = _M_copy(__x._M_begin(), _M_end(), __gen);
    _M_leftmost() = _Tree_minimum(__root);
    _M_rightmost() = _Tree_maximum(__root);
    _M_header._M_node_count = __x._M_header._M_node_count;
    return (__root);
  }
  _Link_type _M_copy(const _Rb_tree &__x) {
    _Alloc_node _an(*this);
    return _M_copy(__x, _an);
  }
  void _M_erase(_Link_type __x) {
    // Erase without rebalancing.
    while (__x != 0) {
      _M_erase(_S_right(__x));
      _Link_type __y = _S_left(__x);
      _M_drop_node(__x);
      __x = __y;
    }
  }
  // _y >= k
  iterator _M_lower_bound(_Link_type _x, _Link_type _y, const _Key &k) {
    while (_x != NULL) {
      // _x >= k
      if (!_M_header._M_key_compare(_KeyOfValue()(*_x->val), k))
        _y = _x, _x = _x->child[LEFT];
      else
        _x = _x->child[RIGHT];
    }
    return (iterator(_y));
  }
  const_iterator _M_lower_bound(_Link_type _x, _Link_type _y,
                                const _Key &k) const {
    while (_x != NULL) {
      if (!_M_header._M_key_compare(_KeyOfValue()(*_x->val), k))
        _y = _x, _x = _x->child[LEFT];
      else
        _x = _x->child[RIGHT];
    }
    return (const_iterator(_y));
  }
  // _y > k
  iterator _M_upper_bound(_Link_type _x, _Link_type _y, const _Key &k) {
    while (_x != NULL) {
      // k < _x
      if (_M_header._M_key_compare(k, _KeyOfValue()(*_x->val)))
        _y = _x, _x = _x->child[LEFT];
      else
        _x = _x->child[RIGHT];
    }
    return (iterator(_y));
  }
  const_iterator _M_upper_bound(_Link_type _x, _Link_type _y,
                                const _Key &k) const {
    while (_x != NULL) {
      if (_M_header._M_key_compare(k, _KeyOfValue()(*_x->val)))
        _y = _x, _x = _x->child[LEFT];
      else
        _x = _x->child[RIGHT];
    }
    return (iterator(_y));
  }
  // set's iterator == const_iterator,
  iterator _Rb_insert_hint(const_iterator _p, const value_type &v) {
    iterator _pos = _p._M_const_cast();
    _Link_type inserted;

    if (_pos == begin()) {
      if (size() > 0 &&
          _M_header._M_key_compare(_KeyOfValue()(v), _KeyOfValue()(*_pos))) {
        inserted = _Rb_insert2(_M_create_node(v), _M_header.child[LEFT], LEFT);
        _M_header.child[LEFT] = inserted;
      } else {
        return (_Rb_insert(v).first);
      }
    } else if (_pos == end()) {
      if (_M_header._M_key_compare(_KeyOfValue()(*_M_rightmost()->val),
                                   _KeyOfValue()(v))) {
        inserted =
            _Rb_insert2(_M_create_node(v), _M_header.child[RIGHT], RIGHT);
        _M_header.child[RIGHT] = inserted;
      } else {
        return (_Rb_insert(v).first);
      }
    } else {
      iterator before = _pos;
      // if after is upper, than before is mostright of after's left tree
      // else after is mostleft of before's right tree
      if (_M_header._M_key_compare(_KeyOfValue()(v), _KeyOfValue()(*_pos)) &&
          _M_header._M_key_compare(_KeyOfValue()(*(--before)),
                                   _KeyOfValue()(v))) {
        if (before._M_node->child[RIGHT] == NULL)
          inserted = _Rb_insert2(_M_create_node(v), before._M_node, RIGHT);
        else
          inserted = _Rb_insert2(_M_create_node(v), _pos._M_node, LEFT);
      } else {
        return (_Rb_insert(v).first);
      }
    }
    ++_M_header._M_node_count;
    return (iterator(inserted));
  }
  template <typename _InputIterator>
  void _Rb_insert_range(_InputIterator _first, _InputIterator _last) {
    for (; _first != _last; ++_first) _Rb_insert(*_first);
  }
  pair<iterator, bool> _Rb_insert(const value_type &v) {
    _Link_type N = _M_create_node(v);

    _Link_type treeNode = _Rb_insert1(N);
    if (treeNode != N) {
      _M_drop_node(N);
      return (pair<iterator, bool>(treeNode, false));
    }
    ++_M_header._M_node_count;
    _M_header.child[RIGHT] = _Tree_maximum(_M_header.parent);
    _M_header.child[LEFT] = _Tree_minimum(_M_header.parent);
    return (pair<iterator, bool>(iterator(treeNode), true));
  }
  void _Rb_clear(void) {
    if (_M_header.parent == NULL) return;
    _Rb_clear1(_M_header.parent);
    _M_header._M_reset();
  }
  // if k was not found, return end()
  _Link_type _Rb_find(const _Key k) {
    _Link_type found = _Rb_find1(_M_header.parent, k);

    if (found == NULL) return (_M_end());
    return (found);
  }
  _Const_Link_type _Rb_find(const _Key k) const {
    _Const_Link_type found = _Rb_find1(_M_header.parent, k);

    if (found == NULL) return (_M_end());
    return (found);
  }
  // delete surely
  void _Rb_erase_aux(_Link_type N) {
    _Rb_erase1(N);
    _M_drop_node(N);
    --_M_header._M_node_count;
  }
  // [TODO]: const ??
  void _Rb_erase_aux(const_iterator pos) {
    _Rb_erase_aux(const_cast<_Link_type>(pos._M_node));
  }
  void _Rb_erase_range(const_iterator _first, const_iterator _last) {
    if (_first == begin() && _last == end())
      _Rb_clear();
    else {
      const_iterator iter = _first;
      while (iter != _last) {
        ++iter;
        _Rb_erase_aux(_first);
        _first = iter;
      }
      // HACK...
      if (_M_header.parent == NULL) {
        _M_header.child[RIGHT] = &_M_header;
        _M_header.child[LEFT] = &_M_header;
        return;
        _M_header.child[RIGHT] = _Tree_maximum(_M_header.parent);
        _M_header.child[LEFT] = _Tree_minimum(_M_header.parent);
      }
    }
  }
  size_type _Rb_erase(_Key k) {
    _Link_type N = _Rb_find(k);

    if (N == _M_end()) return (0);
    size_type old_size = size();
    _Rb_erase_aux(N);
    if (_M_header.parent == NULL) {
      _M_header.child[RIGHT] = &_M_header;
      _M_header.child[LEFT] = &_M_header;
    } else {
      _M_header.child[RIGHT] = _Tree_maximum(_M_header.parent);
      _M_header.child[LEFT] = _Tree_minimum(_M_header.parent);
    }
    return (old_size - size());
  }
  _Compare key_comp() const { return (_M_header._M_key_compare); }
  const_iterator begin() const { return (_M_header.child[LEFT]); }
  iterator begin() { return (_M_header.child[LEFT]); }
  // const_iterator begin() const { return
  // (const_iterator(_M_header.child[LEFT])); }
  const_iterator end() const { return (&_M_header); }
  iterator end() { return (&_M_header); }
  // const_iterator end() const { return (const_iterator(&_M_header)); }
  reverse_iterator rbegin() { return (reverse_iterator(end())); }
  const_reverse_iterator rbegin() const {
    return (const_reverse_iterator(end()));
  }
  reverse_iterator rend() { return (reverse_iterator(begin())); }
  const_reverse_iterator rend() const {
    return (const_reverse_iterator(begin()));
  }
  iterator lower_bound(const key_type &_k) {
    return (_M_lower_bound(_M_begin(), _M_end(), _k));
  }
  const_iterator lower_bound(const key_type &_k) const {
    return (_M_lower_bound(_M_begin(), _M_end(), _k));
  }
  iterator upper_bound(const key_type &_k) {
    return (_M_upper_bound(_M_begin(), _M_end(), _k));
  }
  const_iterator upper_bound(const key_type &_k) const {
    return (_M_upper_bound(_M_begin(), _M_end(), _k));
  }
  pair<iterator, iterator> equal_range(const key_type &_k) {
    _Link_type _x = _M_begin();
    _Link_type _y = _M_end();

    while (_x != NULL) {
      if (_M_header._M_key_compare(_KeyOfValue()(*_x->val), _k))
        _x = _x->child[RIGHT];
      else if (_M_header._M_key_compare(_k, _KeyOfValue()(*_x->val)))
        _y = _x, _x = _x->child[LEFT];
      else {
        _Link_type _xu(_x);
        _Link_type _yu(_y);

        _y = _x, _x = _x->child[LEFT];
        _xu = _xu->child[RIGHT];
        // ((_y >= k), (_yu > _k))
        return pair<iterator, iterator>(_M_lower_bound(_x, _y, _k),
                                        _M_upper_bound(_xu, _yu, _k));
      }
    }
    // _y > _k
    return (pair<iterator, iterator>(iterator(_y), iterator(_y)));
  }
  pair<const_iterator, const_iterator> equal_range(const key_type &_k) const {
    _Const_Link_type _x = _M_begin();
    _Const_Link_type _y = _M_end();

    while (_x != NULL) {
      if (_M_header._M_key_compare(_KeyOfValue()(*_x->val), _k))
        _x = _x->child[RIGHT];
      else if (_M_header._M_key_compare(_k, _KeyOfValue()(*_x->val)))
        _y = _x, _x = _x->child[LEFT];
      else {
        _Const_Link_type _xu(_x);
        _Const_Link_type _yu(_y);

        _y = _x, _x = _x->child[LEFT];
        _xu = _xu->child[RIGHT];
        // ((_y >= k), (_yu > _k))
        return pair<const_iterator, const_iterator>(
            _M_lower_bound(_x, _y, _k), _M_upper_bound(_xu, _yu, _k));
      }
    }
    // _y > _k
    return (pair<const_iterator, const_iterator>(iterator(_y), iterator(_y)));
  }
  void swap(_Rb_tree &_t) {
    if (_M_root() == NULL) {
      if (_t._M_root() != NULL) _M_header._M_move_data(_t._M_header);
    } else if (_t._M_root() == NULL) {
      _t._M_header._M_move_data(_M_header);
    } else {
      std::swap(_M_root(), _t._M_root());
      std::swap(_M_leftmost(), _t._M_leftmost());
      std::swap(_M_rightmost(), _t._M_rightmost());

      _M_root()->parent = _M_end();
      _t._M_root()->parent = _t._M_end();
      std::swap(_M_header._M_node_count, _t._M_header._M_node_count);
    }
    std::swap(_M_header._alloc, _t._M_header._alloc);
  }
  allocator_type get_allocator() const { return (_M_header._alloc); }
};  // namespace ft

template <typename T, typename U, typename C, typename A>
bool operator==(const _Rb_tree<T, U, C, A> &left,
                const _Rb_tree<T, U, C, A> &right) {
  return (left.size() == right.size() &&
          std::equal(left.begin(), left.end(), right.begin()));
}

template <typename T, typename U, typename C, typename A>
bool operator>(const _Rb_tree<T, U, C, A> &left,
               const _Rb_tree<T, U, C, A> &right) {
  return (right < left);
}

// equal to lexicographical_compare
template <typename T, typename U, typename C, typename A>
bool operator<(const _Rb_tree<T, U, C, A> &left,
               const _Rb_tree<T, U, C, A> &right) {
  return (ft::lexicographical_compare(left.begin(), left.end(), right.begin(),
                                      right.end()));
}

template <typename T, typename U, typename C, typename A>
// not equal to lexicographical_compare
bool operator>=(const _Rb_tree<T, U, C, A> &left,
                const _Rb_tree<T, U, C, A> &right) {
  return (!(left < right));
}

template <typename T, typename U, typename C, typename A>
bool operator<=(const _Rb_tree<T, U, C, A> &left,
                const _Rb_tree<T, U, C, A> &right) {
  return (!(right < left));
}
}  // namespace ft

#endif
