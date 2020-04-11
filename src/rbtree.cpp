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

rbt::Node *rbt::RBTree::GetRoot()
{
  if (root != nullptr)
    std::cout << "Root value " << root->value << std::endl;
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
  //InsertRepairTree(n);
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
  std::cout << current->value << " ";
  if (current->right != NULL)
  {
    TraverseInOrder(current->right);
  }
}
