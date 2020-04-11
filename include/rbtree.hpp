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
  public:
    RBTree();
    Node *GetRoot();
    Node *Insert(int val);
    void TraverseInOrder(Node *current);

  private:
    Node *root;

    Node *Insert(Node *n);
    void InsertRecursive(Node *current, Node *n);

    void RotateLeft(Node *n);
    void RotateRight(Node *n);
  };
}

#endif