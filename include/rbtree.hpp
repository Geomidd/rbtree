#ifndef RBTREE_H
#define RBTREE_H

namespace rbt
{
  enum NodeColor
  {
    BLACK,
    RED
  };

  struct Node
  {
    int key;  // TODO: implement template/generics
    NodeColor color;
    Node *left;
    Node *right;
    Node *parent;
  };

  class RBTree
  {
  private:
    Node *root, *nil;

  public:
    RBTree();

    Node *GetRoot();
    Node *Minimum(Node *p);
    Node *Maximum(Node *p);
    Node *Predecessor(Node *p);
    Node *Successor(Node *p);
    Node *Find(int val);

    void RotateLeft(Node *p);
    void RotateRight(Node *p);

    void Insert(int val);
    void InsertFixup(Node *p);

    void Remove(int val);
    void Delete(Node *p);
    void DeleteFixup(Node *p);

    void Dump();
    void Dump(Node *n, int tabs);
  };
}
#endif