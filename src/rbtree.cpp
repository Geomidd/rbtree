#include <iostream>
#include "rbtree.hpp"

rbt::RBTree::RBTree()
{
  nil = new Node;
  nil->key = 0;
  nil->left = nullptr;
  nil->right = nullptr;
  nil->parent = nullptr;
  root = nil;
}
rbt::Node *rbt::RBTree::GetRoot()
{
  return root;
}
rbt::Node *rbt::RBTree::Minimum(Node *p)
{
  while (p->left != nil)
  {
    p = p->left;
  }
  return p;
}
rbt::Node *rbt::RBTree::Maximum(Node *p)
{
  while (p->right != nil)
  {
    p = p->right;
  }
  return p;
}
rbt::Node *rbt::RBTree::Successor(Node *p)
{
  // TODO: Switch to while loop
  if (p->right != nil)
  {
    return Minimum(p->right);
  }
  Node *y = p;
  while (y != nil && y == (y->parent)->right)
  {
    y = y->parent;
  }
  return (y == nil ? nil : y->parent);
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
void rbt::RBTree::RotateLeft(Node *p)
{
  Node *y = p->right;
  y->parent = p->parent;

  if (p->parent != nil)
  {
    if (p == (p->parent->left))
    {
      y->parent->left = y;
    } else
    {
      y->parent->right = y;
    }
  } else
  {
    root = y;
  }
  p->right = y->left;
  if (p->right != nil)
  {
    p->right->parent = p;
  }
  y->left = p;
  p->parent = y;
}
void rbt::RBTree::RotateRight(Node *p)
{
  Node *y = p->left;
  y->parent = p->parent;

  if (p->parent != nil)
  {
    if (p == (p->parent->left))
    {
      y->parent->left = y;
    } else
    {
      y->parent->right = y;
    }
  } else
  {
    root = y;
  }
  p->left = y->right;
  if (p->left != nil)
  {
    p->left->parent = p;
  }
  y->right = p;
  p->parent = y;
}

void rbt::RBTree::Insert(int val)
{
  Node *x = root;
  Node *y = nil;
  while (x != nil)
  {
    y = x;
    if (x->key > val)
    {
      x = x->left;
    } else
    {
      x = x->right;
    }
  }
  Node *temp = new Node;
  temp->key = val;
  temp->left = nil;
  temp->right = nil;
  temp->parent = y;
  temp->color = RED;
  if (temp->parent == nil)
  {
    root = temp;
  } else
  {
    if (val < y->key)
    {
      y->left = temp;
    } else
    {
      y->right = temp;
    }
  }
  InsertFixup(temp);
}
void rbt::RBTree::InsertFixup(Node *p)
{
  Node *z = p;
  while (z != nil && z->parent != nil && z->parent->parent != nil && z->parent->color == RED)
  {

    if (z->parent->parent->left == z->parent)
    {
      if (z->parent->parent->right != nil && z->parent->parent->right->color == RED)
      {
        //case 1
        z->parent->color = BLACK;
        z->parent->parent->right->color = BLACK;
        z = z->parent->parent;
        z->color = RED;
      } else
      {
        //case 2
        if (z == z->parent->right)
        {
          RotateLeft((z = z->parent));
        }
        //case 3
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        RotateRight(z->parent->parent);
      }
    }

    else
    {

      if (z->parent->parent->left != nil && z->parent->parent->left->color == RED)
      {
        //case 1
        z->parent->color = BLACK;
        z->parent->parent->left->color = BLACK;
        z = z->parent->parent;
        z->color = RED;
      } else
      {
        //case 2
        if (z == z->parent->left) { RotateRight((z = z->parent)); }
        //case 3
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        RotateLeft(z->parent->parent);
      }
    }
  }
  root->color = BLACK;
}

void rbt::RBTree::Remove(int val)
{
  Node *n = Find(val);
  if (n == nullptr || n->key != val)
  {
    return;
  }
  Delete(n);
}
void rbt::RBTree::Delete(Node *p)
{
  Node *x = nil;
  Node *y = nil;
  if (p->left == nil || p->right == nil)
  {
    y = p;
  } else
  {
    y = Successor(p);
  }
  if (y->left != nil)
  {
    x = y->left;
  } else
  {
    x = y->right;
  }
  x->parent = y->parent;

  if (y->parent == nil)
  {
    root = x;
  } else
  {
    if (y == y->parent->left)
    {
      x->parent->left = x;
    } else
    {
      x->parent->right = x;
    }
  }
  if (y != p)
  {
    p->key = y->key;
  }
  if (y->color == BLACK)
  {
    DeleteFixup(x);
  }
}
void rbt::RBTree::DeleteFixup(Node *p)
{
  Node *w = nil;
  while (p != root && p->color == BLACK)
  {
    if (p->parent->left == p)
    {
      w = p->parent->right;
      //case 1
      if (w->color == RED)
      {
        w->color = BLACK;
        w->parent->color = RED;
        RotateLeft(w->parent);
        w = p->parent->right;
      } else
      {
        //case 2
        if (w->left->color == BLACK && w->right->color == BLACK)
        {

          w->color = RED;
          p = p->parent;
        }

        else
        {  //case 3
          if (w->left->color == RED && w->right->color == BLACK)
          {
            w->color = RED;
            w->left->color = BLACK;
            RotateRight(w);
            w = p->parent->right;
          }
          //case 4
          w->color = p->parent->color;
          p->parent->color = BLACK;
          w->right->color = BLACK;
          RotateLeft(w->parent);
          p = root;
        }
      }
    } else
    {
      w = p->parent->left;
      //case 1
      if (w->color == RED)
      {
        w->parent->color = RED;
        w->color = BLACK;
        RotateRight(p->parent);
        w = p->parent->left;
      } else
      {  //case 2
        if (w->left->color == BLACK && w->right->color == BLACK)
        {
          w->color = RED;
          p = p->parent;
        } else
        {
          //case 3
          if (w->right->color == RED && w->left->color == BLACK)
          {
            w->color = RED;
            w->right->color = BLACK;
            RotateLeft(w);
            w = p->parent->left;
          }
          //case 4
          w->color = w->parent->color;
          w->parent->color = BLACK;
          w->left->color = BLACK;
          RotateRight(w->parent);
          p = root;
        }
      }
    }
  }
  p->color = BLACK;
}
void rbt::RBTree::Dump()
{
  Dump(root, 0);
}
void rbt::RBTree::Dump(Node *n, int tabs)
{
  if (n == nullptr)
  {
    return;
  }

  Dump(n->left, tabs + 1);

  for (int i = 0; i < tabs; ++i)
  {
    std::cout << "\t\t";
  }
  char color = n->color == 0 ? 'B' : 'R';
  std::cout << n->key << color << std::endl;

  Dump(n->right, tabs + 1);
}
