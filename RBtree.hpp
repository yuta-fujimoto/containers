#ifndef RBTREE_H_
#define RBTREE_H_

#include <iostream>

enum color_t { BLACK, RED };

#define NIL NULL
#define LEFT 0
#define RIGHT 1
#define left child[LEFT]
#define right child[RIGHT]

struct RBnode {
  RBnode *parent;
  RBnode *child[2];
  color_t color;
  int key;

  RBnode(int k = 0) : key(k), parent(NIL), color(BLACK) {
    child[LEFT] = NIL;
    child[RIGHT] = NIL;
  }
  ~RBnode() {}
  RBnode(RBnode const &rhs) { *this = rhs; }
  RBnode &operator=(RBnode const &rhs) {
    if (this == &rhs) return (*this);
    key = rhs.key;
    child[LEFT] = rhs.child[LEFT];
    child[RIGHT] = rhs.child[RIGHT];
    return (*this);
  }
};

struct RBtree {
  RBnode *root;

  RBtree() : root(NIL) {}
};

#define childDir(N) (N == (N->parent)->right ? RIGHT : LEFT)

// T(TREE: RBtree)
// P(pivot: root of subtree)
// dir(left rotation or right rotation)
RBnode *RotateDirRoot(RBtree *T, RBnode *P, char dir) {
  RBnode *G = P->parent;          // GrandParent
  RBnode *S = P->child[1 - dir];  // Son
  if (S == NIL) return (NIL);
  RBnode *C = S->child[dir];

  P->child[1 - dir] = C;
  if (C != NIL) C->parent = P;

  S->child[dir] = P;
  P->parent = S;
  S->parent = G;

  if (G != NIL)
    G->child[P == G->right ? RIGHT : LEFT] = S;
  else
    T->root = S;
  return (S);  // new root of subtree
}

#define RotateDir(N, dir) RotateDirRoot(T, N, dir)
#define RotateLeft(N) RotateDirRoot(T, N, LEFT)
#define RotateRight(N) RotateDirRoot(T, N, RIGHT)

void RBinsert1(RBtree *T, RBnode *N, RBnode *P, char dir) {
  RBnode *G;  // GrandParent
  RBnode *U;  // Uncle

  N->color = RED;
  N->left = NIL;
  N->right = NIL;
  N->parent = P;
  if (P == NIL) {
    T->root = N;
    return;
  }
  P->child[dir] = N;
  do {
    if (P->color == BLACK)  // Case_I1 (P: BLACK)
      return;
    G = P->parent;
    if (G == NIL)  // Case_I4 (P: RED and ROOT)
      goto Case_I4;
    dir = childDir(P);
    U = G->child[1 - dir];
    if (U == NIL || U->color == BLACK)  // Case_I56 (U: BLACK)
      goto Case_I56;
    // Case_I2 (P+U: RED)
    P->color = BLACK;
    U->color = BLACK;
    G->color = RED;
    N = G;
    P = N->parent;
  } while (P != NIL);
  // Case_I3 (N: ROOT)
  return;
Case_I4:
  P->color = BLACK;
  return;
Case_I56:
  if (N == P->child[1 - dir]) {
    // Case_I5 (P: RED, U: BLACK, N: inner grandchild of G)
    RotateDir(P, dir);
    N = P;
    P = G->child[dir];
  }
  // Case_I6 (P: RED, U: BLACK, N: outer grandchild of G)
  RotateDirRoot(T, G, 1 - dir);
  P->color = BLACK;
  G->color = RED;
  return;
}

RBnode *TreeMinimum(RBnode *N) {
  while (N->left != NIL) N = N->left;
  return (N);
}

RBnode *TreeSuccessor(RBnode *N) { return (TreeMinimum(N->right)); }

// REPLACE NODE N WITH R
void SubtreeShift(RBtree *T, RBnode *N, RBnode *R) {
  if (N->parent == NIL)
    T->root = R;
  else
    N->parent->child[childDir(N)] = R;
  if (R != NIL) R->parent = N->parent;
}

void RBdelete2(RBtree *T, RBnode *N) {
  RBnode *P = N->parent;
  char dir;
  RBnode *S;
  RBnode *C;
  RBnode *D;

  // P != NULL
  dir = childDir(N);
  P->child[dir] = NIL;
  goto Start_D;
  do {
    dir = childDir(N);
  Start_D:
    S = P->child[1 - dir];
    D = S->child[1 - dir];
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
  } while (P != NIL);
  // Case_D2 (P==NULL)
  return;
Case_D3:                     // Case_D3 (S: RED, P+C+D: BLACK)
  RotateDirRoot(T, P, dir);  // P may be root
  P->color = RED;
  S->color = BLACK;
  S = C;

  D = S->child[1 - dir];
  if (D != NIL && D->color == RED) goto Case_D6;
  C = S->child[dir];
  if (C != NIL && C->color == RED) goto Case_D5;
Case_D4:
  S->color = RED;
  P->color = BLACK;
  return;
Case_D5:
  RotateDir(S, 1 - dir);
  S->color = RED;
  C->color = BLACK;
  D = S;
  S = C;
  // now: D red && S black
  // fall through to Case_d&
Case_D6:
  RotateDirRoot(T, P, dir);
  S->color = P->color;
  P->color = BLACK;
  D->color = BLACK;
  return;
}

void RBdelete1(RBtree *T, RBnode *N) {
  if (N->parent == NIL && N->left == NIL && N->right == NIL) {
    T->root = NIL;
    return;
  }
  if (N->left && N->right) {
    RBnode *R = TreeSuccessor(N);

    R->color = N->color;
    if (R->parent != N) {
      SubtreeShift(T, R, R->right);
      R->right = N->right;
      R->right->parent = R;
    }
    SubtreeShift(T, N, R);
    R->left = N->left;
    R->left->parent = R;
  } else if (N->color == RED)
    SubtreeShift(T, N, NIL);
  else {
    if (N->left || N->right) {
      RBnode *R = N->left != NIL ? N->left : N->right;

      R->color = BLACK;
      SubtreeShift(T, N, R);
    } else
      RBdelete2(T, N);
  }
}

RBnode *newRBnode(int k) {
  RBnode *N;

  N = new RBnode(k);
  return (N);
}

void RBinsert(RBtree *T, RBnode *N) {
  RBnode *P;

  if (T->root == NIL) RBinsert1(T, N, NIL, LEFT);
  P = T->root;
  while (true) {
    if (N->key > P->key) {
      if (P->left == NIL) {
        RBinsert1(T, N, P, LEFT);
        return;
      }
      P = P->left;
    } else if (N->key < P->key) {
      if (P->right == NIL) {
        RBinsert1(T, N, P, RIGHT);
        return;
      }
      P = P->right;
    } else
      return;
  }
}

void RBclear(RBnode *N) {
  if (N == NIL) return;
  RBclear(N->left);
  RBclear(N->right);
  delete N;
}

RBnode *RBfind(RBnode *N, int k) {
  if (N == NIL) return (NIL);
  if (k > N->key) return (RBfind(N->left, k));
  if (k < N->key) return (RBfind(N->right, k));
  return (N);
}

void RBdelete(RBtree *T, int k) {
  RBnode *N = RBfind(T->root, k);

  if (N != NIL) RBdelete1(T, N);
}

#endif
