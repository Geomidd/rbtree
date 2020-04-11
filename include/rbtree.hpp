#ifndef RBTREE_H
#define RBTREE_H

namespace rbt
{
  int add(const int &a, const int &b);

  enum NodeColor
  {
    BLACK,
    RED
  };

  struct Node
  {
    int value;  // TODO: implement template/generics
    Node *parent;
    Node *left;
    Node *right;
    NodeColor color;

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