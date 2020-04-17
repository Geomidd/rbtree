#include <cassert>
#include <iostream>
#include "rbtree.hpp"

rbt::RBTree::RBTree()
  : root(nullptr)
{
  std::cout << "Creating rbt" << std::endl;
}

rbt::RBTree::~RBTree()
{
  DeleteNode(root);
}

void rbt::RBTree::RotateLeft(rbt::Node *x)
{
  Node *y = x->right;
  x->right = y->left;
  if (y->left != nullptr)
  {
    y->left->parent = x;
  }

  y->parent = x->parent;

  if (x->parent == nullptr)
  {
    root = y;
  } else if (x == x->parent->left)
  {
    x->parent->left = y;
  } else
  {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

void rbt::RBTree::RotateRight(rbt::Node *y)
{
  Node *x = y->left;
  y->left = x->right;
  if (x->right != nullptr)
  {
    x->right->parent = y;
  }

  x->parent = y->parent;

  if (y->parent == nullptr)
  {
    root = x;
  } else if (y == y->parent->left)
  {
    y->parent->left = x;
  } else
  {
    y->parent->right = x;
  }
  x->right = y;
  y->parent = x;
}

const rbt::Node *rbt::RBTree::GetRoot()
{
  return root;
}

void rbt::RBTree::Insert(int val)
{
  Node *newNode = new Node{ val };
  Insert(newNode);
}

void rbt::RBTree::Insert(rbt::Node *n)
{
  Node *parent = nullptr;
  Node *node = root;
  while (node)
  {
    parent = node;
    if (n->key < node->key)
    {
      node = node->left;
    } else
    {
      node = node->right;
    }
  }

  if (parent == nullptr)
  {
    root = n;
    n->color = BLACK;
    n->parent = nullptr;
    n->left = nullptr;
    n->right = nullptr;
  } else
  {
    n->color = RED;
    n->parent = parent;
    n->left = nullptr;
    n->right = nullptr;

    if (n->key < parent->key)
    {
      parent->left = n;
    } else
    {
      parent->right = n;
    }
  }
  InsertFixup(n);
}

void rbt::RBTree::InsertRecursive(rbt::Node *current, rbt::Node *n)
{
  if (current != nullptr)
  {
    if (n->key < current->key)
    {
      if (current->left != nullptr)
      {
        InsertRecursive(current->left, n);
        return;
      } else
      {
        current->left = n;
      }
    } else
    {
      if (current->right != nullptr)
      {
        InsertRecursive(current->right, n);
        return;
      } else
      {
        current->right = n;
      }
    }
  }

  n->parent = current;
  n->left = nullptr;
  n->right = nullptr;
  n->color = RED;
}

void rbt::RBTree::TraverseInOrder(Node *current)
{
  if (current->left != nullptr)
  {
    TraverseInOrder(current->left);
  }

  std::string dir = "";
  int parentVal = 0;
  if (current == root)
    std::cout << "[";
  else
  {
    dir = (current == current->parent->left) ? "L" : "R";
    parentVal = current->parent->key;
  }
  std::cout << dir << current->key << "(" << current->color << ")" << parentVal;
  if (current == root)
    std::cout << "] ";
  else
    std::cout << " ";
  if (current->right != NULL)
  {
    TraverseInOrder(current->right);
  }
}

void rbt::RBTree::RepairTree(rbt::Node *n)
{
  if (n->parent == nullptr)
  {
    RepairCase1(n);
  } else if (n->parent->color == BLACK)
  {
    RepairCase2(n);
  } else if (GetUncle(n) != nullptr && GetUncle(n)->color == RED)
  {
    RepairCase3(n);
  } else
  {
    RepairCase4(n);
  }
}

void rbt::RBTree::RepairCase1(rbt::Node *n)
{
  n->color = BLACK;
}

void rbt::RBTree::RepairCase2(rbt::Node *n)
{
  // Do nothing
}

void rbt::RBTree::RepairCase3(rbt::Node *n)
{
  GetParent(n)->color = BLACK;
  GetUncle(n)->color = BLACK;
  GetGrandparent(n)->color = RED;
  RepairTree(GetGrandparent(n));
}

void rbt::RBTree::RepairCase4(rbt::Node *n)
{
  Node *p = GetParent(n);
  Node *g = GetGrandparent(n);

  if (n == p->right && p == g->left)
  {
    RotateLeft(p);
    n = n->left;
  } else if (n == p->left && p == g->right)
  {
    RotateRight(p);
    n = n->right;
  }

  RepairCase4Step2(n);
}
void rbt::RBTree::RepairCase4Step2(rbt::Node *n)
{
  Node *p = GetParent(n);
  Node *g = GetGrandparent(n);

  if (n == p->left)
  {
    RotateRight(g);
  } else
  {
    RotateLeft(g);
  }
  p->color = BLACK;
  g->color = RED;
}

void rbt::RBTree::Dump(Node *n, int tabs)
{
  if (n == nullptr) return;

  Dump(n->left, tabs + 1);

  for (int i = 0; i < tabs; ++i)
  {
    std::cout << "\t\t";
  }
  std::cout << n->key << (n->color == 0 ? "B" : "R") << std::endl;

  Dump(n->right, tabs + 1);
}

rbt::Node *rbt::RBTree::GetParent(Node *n)
{
  return n->parent == nullptr ? nullptr : n->parent;
}

rbt::Node *rbt::RBTree::GetUncle(rbt::Node *n)
{
  return GetSibling(GetParent(n));
}

rbt::Node *rbt::RBTree::GetSibling(Node *n)
{
  if (n->parent == nullptr)
    return nullptr;

  if (n == GetParent(n)->left)
    return GetParent(n)->right;
  else
    return GetParent(n)->left;
}

rbt::Node *rbt::RBTree::GetGrandparent(Node *n)
{
  return GetParent(n) == nullptr ? nullptr : GetParent(GetParent(n));
}

rbt::Node *rbt::RBTree::Find(int val)
{
  Node *containingNode = root;
  while (containingNode != nullptr)
  {
    if (val < containingNode->key)
    {
      containingNode = containingNode->left;
    } else if (val > containingNode->key)
    {
      containingNode = containingNode->right;
    } else
    {
      break;
    }
  }

  if (containingNode == nullptr || val != containingNode->key)
  {
    std::cout << val << " not found in tree" << std::endl;
    return nullptr;
  }
  return containingNode;
}

void rbt::RBTree::Remove(int val)
{
  // TODO: Redo this based on Intro to Algorithms
  Node *n = Find(val);
  if (n == nullptr) return;

  NodeColor original = n->color;
  Node *sub;
  Node *old;
  if (n->left == nullptr)
  {
    sub = n->right;
    Transplant(n, sub);
  } else if (n->right == nullptr)
  {
    sub = n->left;
    Transplant(n, sub);
  } else
  {
    old = Minimum(n->right);
    original = old->color;
    sub = old->right;

    if (old->parent == n)
    {
      sub->parent = n;
    } else
    {
      Transplant(old, old->right);
      old->right = n->right;
      old->right->parent = old;
    }

    Transplant(n, old);
    old->left = n->left;
    old->left->parent = old;
    old->color = n->color;
  }
  delete n;

  if (original == BLACK)
  {
    bool side;
    Node *sibling;
    while (old != root && old->color == BLACK)
    {
      side = old == old->parent->left;
      if (side)
      {
        sibling = old->parent->right;
      } else
      {
        sibling = old->parent->left;
      }

      if (sibling->color == RED)
      {
        sibling->color = BLACK;
        old->parent->color = RED;
        side ? RotateLeft(old->parent) : RotateRight(old->parent);
        sibling = side ? old->parent->right : old->parent->left;
      }

      if (sibling->left->color == BLACK && sibling->right->color == RED)
      {
        sibling->color = RED;
        old = old->parent;
      } else
      {
        if (BLACK == side ? sibling->right->color : sibling->left->color)
        {
          sibling->color = RED;
          if (side)
          {
            sibling->left->color = BLACK;
            RotateRight(sibling);
            sibling = old->parent->right;
          } else
          {
            sibling->right->color = BLACK;
            RotateLeft(sibling);
            sibling = old->parent->left;
          }
        }

        sibling->color = old->parent->color;
        old->parent->color = BLACK;
        if (side)
        {
          sibling->left->color = BLACK;
          RotateLeft(old->parent);
        } else
        {
          sibling->right->color = BLACK;
          RotateRight(old->parent);
        }

        old = root;
      }
    }
  }
}
void rbt::RBTree::Remove(rbt::Node *n)
{
}
void rbt::RBTree::DeleteNode(rbt::Node *n)
{
  if (n == nullptr) return;

  if (n->left) DeleteNode(n->left);
  if (n->right) DeleteNode(n->right);
  delete n;
}
void rbt::RBTree::InsertFixup(rbt::Node *n)
{
  bool side;
  Node *uncle;
  while (n->parent && n->parent->color == RED)
  {
    bool side = n->parent == n->parent->parent->left;
    if (side)
    {
      uncle = n->parent->parent->right;
    } else
    {
      uncle = n->parent->parent->left;
    }

    if (uncle && uncle->color == RED)
    {
      n->parent->color = BLACK;
      uncle->color = BLACK;
      n->parent->parent->color = RED;
      n = n->parent->parent;
    } else
    {
      if (n == (side ? n->parent->right : n->parent->left))
      {
        n = n->parent;
        side ? RotateLeft(n) : RotateRight(n);
      }

      n->parent->color = BLACK;
      n->parent->parent->color = RED;
      side ? RotateRight(n->parent->parent) : RotateLeft(n->parent->parent);
    }
  }

  root->color = BLACK;
}
void rbt::RBTree::Transplant(rbt::Node *dest, rbt::Node *src)
{
  if (dest->parent == NULL)
  {
    root = src;
  } else if (dest == dest->parent->left)
  {
    dest->parent->left = src;
  } else
  {
    dest->parent->right = src;
  }

  if (src)
  {
    src->parent = dest->parent;
  }
}
rbt::Node *rbt::RBTree::Minimum(rbt::Node *n)
{
  while (n->left)
  {
    n = n->left;
  }
  return n;
}
void rbt::RBTree::Dump()
{
  Dump(root, 0);
}
