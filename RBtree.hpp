#ifndef RBTREE_H_
#define RBTREE_H_

/** @file RBtree.hpp
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{map,set}
 */

#include <iostream>

#include "iterator_traits.hpp"
#include "pair.hpp"

namespace ft {
enum _RB_tree_color { BLACK = false, RED = true };
// LEFT/RIGHT ratation
#define LEFT false
#define RIGHT true

#define NIL NULL
#define left child[LEFT]
#define right child[RIGHT]
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

  _RB_tree_node() {
    this->color = RED;
    _M_reset();
  }
  void _M_move_data(_RB_tree_node &_from) {
    this->color = _from.color;
    this->parent = _from.parent;
    this->left = _from.left;
    this->right = _from.right;
    this->parent->parent = &_from;

    _from._M_reset();
  }
  void _M_reset() {
    this->parent = 0;
    this->left = this;
    this->right = this;
  }
  typename _Val::first_type getKey() const { return (val->first); }
  typename _Val::second_type getValue() const { return (val->second); }
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
_RB_tree_node<_Val> *TreeMinimum(_RB_tree_node<_Val> *N) {
  if (N == NIL) return (NIL);
  while (N->left != NIL) N = N->left;
  return (N);
}
template <typename _Val>
_RB_tree_node<_Val> *TreeMaximum(_RB_tree_node<_Val> *N) {
  if (N == NIL) return (NIL);
  while (N->right != NIL) N = N->right;
  return (N);
}
// the node with the smallest key greater than n's key
template <typename _Val>
_RB_tree_node<_Val> *TreeSuccessor(_RB_tree_node<_Val> *_X) {
  if (_X->right != NIL) return (TreeMinimum(_X->right));
  _RB_tree_node<_Val> *_Y = _X->parent;
  while (_Y != NIL && _X == _Y->right) {
    _X = _Y;
    _Y = _Y->parent;
  }
  if (_X->right != _Y)
    _X = _Y;
  return (_X);
}
// the node with the largest key smaller than n's key
template <typename _Val>
_RB_tree_node<_Val> *TreePredecessor(_RB_tree_node<_Val> *_X) {
  if (_X->left != NIL) return (TreeMaximum(_X->left));
  _RB_tree_node<_Val> *_Y = _X->parent;
  while (_Y != NIL && _X == _Y->left) {
    _X = _Y;
    _Y = _Y->parent;
  }
  return (_Y);
}

template <typename _Val>
_RB_tree_node<_Val> *_Rb_tree_increment(_RB_tree_node<_Val> *N) {
  return (TreeSuccessor(N));
}

template <typename _Val>
_RB_tree_node<_Val> *_Rb_tree_increment(_RB_tree_node<_Val> const *N) {
  return (TreeSuccessor(N));
}
template <typename _Val>
_RB_tree_node<_Val> *_Rb_tree_decrement(_RB_tree_node<_Val> *N) {
  return (TreePredecessor(N));
}
template <typename _Val>
_RB_tree_node<_Val> *_Rb_tree_decrement(_RB_tree_node<_Val> const *N) {
  return (TreePredecessor(N));
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
  // typedef _Rb_tree_node<T> *_Link_type;

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

// template <typename _Val>
// struct _Rb_tree_header : public _RB_tree_node<_Val> {
//   // PARENT: ROOT
//   // LEFT: BEGIN
//   // RIGHT: END - 1
//   size_t _M_node_count;

//   _Rb_tree_header() {
//     this->color = RED;
//     _M_reset();
//   }
//   // WHAT'S ???
//   void _M_move_data(_Rb_tree_header &_from) {
//     this->color = _from.color;
//     this->parent = _from.parent;
//     this->left = _from.left;
//     this->right = _from.right;
//     this->parent->parent = &_from;
//     _M_node_count = _from._M_node_count;

//     _from._M_reset();
//   }
//   void _M_reset() {
//     this->parent = 0;
//     this->left = this;
//     this->right = this;
//     _M_node_count = 0;
//   }
// };

// template<typename _Key, typename _Val, typename _KeyOfValue,
// 	typename _Compare, typename _Alloc = std::allocator<_Val> >
template <typename _Key, typename _Val, typename _Alloc = std::allocator<_Val> >
class RBtree {
 private:
  typedef typename _Alloc::template rebind<_RB_tree_node<_Val> >::other
      _Node_allocator;
  typedef _RB_tree_node<_Val> *_Link_type;

  _RB_tree_node<_Val> _M_header;
  _Node_allocator _node_alloc;
  _Alloc _alloc;

  _Link_type _M_get_node(void) { return (_node_alloc.allocate(1)); }
  void _M_construct_node(_Link_type _node, const _Val &x) {
    _node->color = RED;
    _node->left = NIL;
    _node->right = NIL;
    _node->parent = NIL;
    _node->val = _alloc.allocate(1);
    _alloc.construct(_node->val, x);
    // in c++ , try catch is used
  }
  _Link_type _M_create_node(const _Val &x) {
    _Link_type _tmp = _M_get_node();
    _M_construct_node(_tmp, x);
    return _tmp;
  }
  void _M_drop_node(_Link_type _p) {
    _alloc.destroy(_p->val);
    _alloc.deallocate(_p->val, 1);
    _node_alloc.deallocate(_p, 1);
  }
#define childDir(N) (N == (N->parent)->right ? RIGHT : LEFT)
  _Link_type RotateDirRoot(_Link_type P, bool dir) {
    _Link_type G = P->parent;       // GrandParent
    _Link_type S = P->child[!dir];  // Son
    if (S == NIL) return (NIL);
    _Link_type C = S->child[dir];

    P->child[!dir] = C;
    if (C != NIL) C->parent = P;

    S->child[dir] = P;
    P->parent = S;
    S->parent = G;

    if (G != &_M_header)
      G->child[P == G->right ? RIGHT : LEFT] = S;
    else
    {
      _M_header.parent = S;
      // S->parent = &_M_header;     S->parent = G;
    }
    return (S);  // new root of subtree
  }

#define RotateDir(N, dir) RotateDirRoot(N, dir)
#define RotateLeft(N) RotateDirRoot(N, LEFT)
#define RotateRight(N) RotateDirRoot(N, RIGHT)

  void RBinsert2(_Link_type N, _Link_type P, bool dir) {
    _Link_type G;  // GrandParent
    _Link_type U;  // Uncle

    N->parent = P;
    if (P == &_M_header) {
      _M_header.parent = N;
      N->parent = &_M_header;
      return;
    }
    P->child[dir] = N;
    do {
      if (P->color == BLACK)  // Case_I1 (P: BLACK)
        return;
      G = P->parent;
      if (G == &_M_header)
        goto Case_I4;  // Case_I4 (P: RED and ROOT)
      dir = childDir(P);
      U = G->child[!dir];
      if (U == NIL || U->color == BLACK)  // Case_I56 (U: BLACK)
      {
        goto Case_I56;
      }
      // Case_I2 (P+U: RED)
      P->color = BLACK;
      U->color = BLACK;
      G->color = RED;
      N = G;
      P = N->parent;
    } while (P != &_M_header);
    // Case_I3 (N: ROOT)
    return;
  Case_I4:
    P->color = BLACK;
    return;
  Case_I56:
    if (N == P->child[!dir]) {
      // Case_I5 (P: RED, U: BLACK, N: inner grandchild of G)
      RotateDir(P, dir);
      N = P;
      P = G->child[dir];
    }
    // Case_I6 (P: RED, U: BLACK, N: outer grandchild of G)
    RotateDir(G, !dir);
    P->color = BLACK;
    G->color = RED;
    return;
  }
  _Link_type RBinsert1(_Link_type N) {
    _Link_type P;

    if (_M_header.parent == NIL) RBinsert2(N, &_M_header, LEFT);
    P = _M_header.parent;
    while (true) {
      if (N->getKey() > P->getKey()) {
        if (P->right == NIL) {
          RBinsert2(N, P, RIGHT);
          return (N);
        }
        P = P->right;
      } else if (N->getKey() < P->getKey()) {
        if (P->left == NIL) {
          RBinsert2(N, P, LEFT);
          return (N);
        }
        P = P->left;
      } else {
        return (P);
      }
    }
  }

  // REPLACE NODE N WITH R
  void SubtreeShift(_Link_type N, _Link_type R) {
    if (N == _M_header.parent) {
      _M_header.parent = R;
      R->parent = &_M_header;
    }
    else
      N->parent->child[childDir(N)] = R;
    if (R != NIL) R->parent = N->parent;
  }
  // N != ROOT && N->color == BLACK && N has no child
  void RBdelete2(_Link_type N) {
    _Link_type P = N->parent;
    bool dir;
    _Link_type S;
    _Link_type C;
    _Link_type D;

    // P != NULL
    dir = childDir(N);
    P->child[dir] = NIL;
    goto Start_D;
    do {
      dir = childDir(N);
    Start_D:
      S = P->child[!dir];
      D = S->child[!dir];
      C = S->child[dir];
      if (S->color == RED)  // Case_D3 (S: RED)
        goto Case_D3;
      if (D != NIL && D->color == RED)  // Case_D6 (D: RED, S: BLACK)
        goto Case_D6;
      if (C != NIL && C->color == RED)  // Case_D6 (C: RED, S+D: BLACK)
        goto Case_D5;
      if (P->color == RED)  // Case_D4 (P: RED, C+S+D: BLACK)
        goto Case_D4;
      // Case_D1 (P+C+S+D: BLACK)
      S->color = RED;
      N = P;
      P = N->parent;
    } while (P != &_M_header);
    // Case_D2 (P==NULL)
    std::cout << "YES" << std::endl;
    return;
  Case_D3:                     // Case_D3 (S: RED, P+C+D: BLACK)
    RotateDirRoot(P, dir);  // P may be root
  
    P->color = RED;
    S->color = BLACK;
    S = C;

    D = S->child[!dir];
    if (D != NIL && D->color == RED) goto Case_D6;
    C = S->child[dir];
    if (C != NIL && C->color == RED) goto Case_D5;
  Case_D4:
    S->color = RED;
    P->color = BLACK;
    return;
  Case_D5:
    RotateDirRoot(S, !dir);
    S->color = RED;
    C->color = BLACK;
    D = S;
    S = C;
    // now: D red && S black
    // fall through to Case_d&
  Case_D6:
    RotateDirRoot(P, dir);
    S->color = P->color;
    P->color = BLACK;
    D->color = BLACK;
    return;
  }
  void RBdelete1(_Link_type N) {
    if (N == _M_header.parent && N->left == NIL && N->right == NIL) {
      _M_header.parent = NIL;
    } else if (N->left && N->right) {
      _Link_type R = TreeSuccessor(N);

      if (R->color == BLACK)
        RBdelete2(R);
      R->color = N->color;
      if (R->parent != N) {
        SubtreeShift(R, R->right);
        R->right = N->right;
        R->right->parent = R;
      }
      SubtreeShift(N, R);
      R->left = N->left;
      if (R->left != NIL)
        R->left->parent = R;
    } else if (N->color == RED) {
      SubtreeShift(N, NIL);
    } else {
      if (N->left != NIL || N->right != NIL) {
        _Link_type R = N->left != NIL ? N->left : N->right;

        R->color = BLACK;
        SubtreeShift(N, R);
      } else {
        RBdelete2(N);
      }
    }
    _M_drop_node(N);
  }
  _Link_type RBfind1(_Link_type N, _Key k) {
    if (N == NIL) return (NIL);
    if (k < N->getKey()) return (RBfind1(N->left, k));
    if (k > N->getKey()) return (RBfind1(N->right, k));
    return (N);
  }
  void RBclear1(_Link_type N) {
    if (N == NIL) return;
    RBclear1(N->left);
    RBclear1(N->right);
    _M_drop_node(N);
  }
  void printTree1(_Link_type N, int level) {
    if (!N) return;
    printTree1(N->left, level + 1);
    N->print(level);
    printTree1(N->right, level + 1);
  }
  void InvalidTree(_Link_type N) {
    printTree1(N, 0);
  }
  int checkTree1(_Link_type N, int len) {
    int ldep;
    int rdep;

    if (!N)
      return (len + 1);
    if (N->color == RED)
    {
      if ((N->left == NIL || N->left->color == BLACK)
        && (N->right == NIL || N->right->color == BLACK))
      {
        ldep = checkTree1(N->left, len);
        rdep = checkTree1(N->right, len);
        if (ldep != -1 && rdep == ldep)
          return (ldep);
        std::cout << "CURRENT: " << N->getKey() << " LEFT: " << ldep << " RIGHT: " << rdep << std::endl;
      }
      printTree1(N, 0);
      return (-1);
    }
    ldep = checkTree1(N->left, len + 1);
    rdep = checkTree1(N->right, len + 1);
    if (ldep != -1 && rdep == ldep)
      return (ldep);
    std::cout << "CURRENT: " << N->getKey() << " LEFT: " << ldep << " RIGHT: " << rdep << std::endl;
    printTree1(N, 0);
    return (-1);
  }

 public:
  typedef _Rb_tree_iterator<_Val> iterator;
  // typedef _Rb_tree_const_iterator<value_type> const_iterator;
  RBtree() {}
  ~RBtree() {}
  RBtree(_Link_type const &rhs) { *this = rhs; }
  RBtree &operator=(RBtree const &rhs) {
    if (this == &rhs) return (*this);
    if (_M_header.parent != NIL) RBclear1(_M_header.parent);
    _M_header.parent = rhs._M_header.parent;  // should move
  }
  _Link_type _M_begin() { return (_M_header.left); }
  // _Const_Link_type _M_begin() const { return (_M_header.left); }
  _Link_type _M_end() { return (&_M_header); }
  // _Const_Link_type _M_end() const { return (_M_header); }
  pair<iterator, bool> RBinsert(const _Val &v) {
    _Link_type N = _M_create_node(v);

    _Link_type treeNode = RBinsert1(N);
    if (treeNode != N)
    {
      _M_drop_node(N);
      return (pair<iterator, bool>(treeNode, false));
    }
    _M_header.right = TreeMaximum(_M_header.parent);
    _M_header.left = TreeMinimum(_M_header.parent);
    return (pair<iterator, bool>(treeNode, true));
  }
  void RBclear(void) {
    if (_M_header.parent == NIL) return;
    RBclear1(_M_header.parent);
    _M_header._M_reset();
  }
  _Link_type RBfind(_Key k) { return (RBfind1(_M_header.parent, k)); }

  void RBdelete(_Key k) {
    _Link_type N = RBfind(k);

    if (N == NIL) return;
    RBdelete1(N);
    if (_M_header.parent == NIL) {
      _M_header.right = &_M_header;
      _M_header.left = &_M_header;
      return ;
    }
    _M_header.right = TreeMaximum(_M_header.parent);
    _M_header.left = TreeMinimum(_M_header.parent);
  }
  void printTree() {
    if (_M_header.parent == NIL) return;
    printTree1(_M_header.parent->left, 1);
    _M_header.parent->print(0);
    printTree1(_M_header.parent->right, 1);
  }
  bool checkTree() {
    int dep = checkTree1(_M_header.parent, 0);

    if (dep == -1)
      std::cout << "ERROR!" << std::endl;
    else
      std::cout << "SUCCESS: " << dep << std::endl;
    return (dep != -1);
  }
};

}  // namespace ft

#endif
