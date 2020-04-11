#ifndef RBTREE_H
#define RBTREE_H

namespace rbt
{
  int add(const int &a, const int &b);

  struct Node
  {
    int value;
    Node *parent;
    Node *left;
    Node *right;
    bool color;  // true = black, red = false

    Node *GetParent();
    Node *GetGrandparent();
    Node *GetSibling();
    Node *GetUncle();
  };

  class RBTree
  {
  private:
    void RotateLeft(Node *n);
    void RotateRight(Node *n);
  };
}

#endif