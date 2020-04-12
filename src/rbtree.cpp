#include <cassert>
#include <iostream>
#include "rbtree.hpp"

rbt::RBTree::RBTree()
  : root(nullptr)
{
  std::cout << "Creating rbt" << std::endl;
}

void rbt::RBTree::RotateLeft(rbt::Node *n)
{
  Node *nNew = n->right;
  Node *p = n->GetParent();
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

rbt::Node *rbt::RBTree::GetRoot()
{
  return root;
}

rbt::Node *rbt::RBTree::Insert(int val)
{
  Node *newNode = new Node{ val };
  return Insert(newNode);
}

rbt::Node *rbt::RBTree::Insert(rbt::Node *n)
{
  InsertRecursive(root, n);
  RepairTree(n);

  root = n;
  while (root->GetParent())
  {
    root = root->GetParent();
  }
  return n;
}

void rbt::RBTree::InsertRecursive(rbt::Node *current, rbt::Node *n)
{
  if (current != nullptr)
  {
    if (n->value < current->value)
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
    dir = (current == current->GetParent()->left) ? "L" : "R";
    parentVal = current->GetParent()->value;
  }
  std::cout << dir << current->value << "(" << current->color << ")" << parentVal;
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
  if (n->GetParent() == nullptr)
  {
    RepairCase1(n);
  } else if (n->GetParent()->color == BLACK)
  {
    RepairCase2(n);
  } else if (n->GetUncle() != nullptr && n->GetUncle()->color == RED)
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
  n->GetParent()->color = BLACK;
  n->GetUncle()->color = BLACK;
  n->GetGrandparent()->color = RED;
  RepairTree(n->GetGrandparent());
}

void rbt::RBTree::RepairCase4(rbt::Node *n)
{
  Node *p = n->GetParent();
  Node *g = n->GetGrandparent();

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
  Node *p = n->GetParent();
  Node *g = n->GetGrandparent();

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
  if (!n)
  {
    return;
  }

  Dump(n->left, tabs + 1);

  for (int i = 0; i < tabs; ++i)
  {
    std::cout << "\t\t";
  }
  std::cout << n->value << (n->color == 0 ? "B" : "R") << std::endl;

  Dump(n->right, tabs + 1);
}
