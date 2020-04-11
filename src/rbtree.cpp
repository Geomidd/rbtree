#include <cassert>
#include "rbtree.hpp"

void rbt::RBTree::RotateLeft(rbt::Node *n)
{
  Node *nNew = n->right;
  Node *p = n->parent;
  assert(nNew != nullptr);

  n->right = nNew->left;
  nNew->left = n;
  n->parent = nNew;

  if (n->right != nullptr)
  {
    n->right->parent = n;
  }

  if (p != nullptr)
  {
    if (n == p->left)
    {
      p->left = nNew;
    } else if (n == p->right)
    {
      p->right = nNew;
    }
  }

  nNew->parent = p;
}

void rbt::RBTree::RotateRight(rbt::Node *n)
{
  Node *nNew = n->left;
  Node *p = n->parent;
  assert(nNew != nullptr);

  n->left = nNew->right;
  nNew->right = n;
  n->parent = nNew;

  if (n->left != nullptr)
  {
    n->left->parent = n;
  }

  if (p != nullptr)
  {
    if (n == p->left)
    {
      p->left = nNew;
    } else if (n == p->right)
    {
      p->right = nNew;
    }
  }

  nNew->parent = p;
}
