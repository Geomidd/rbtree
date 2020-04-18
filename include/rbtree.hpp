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
    Node *root;
    Node *nil;

    Node *Predecessor(Node *p);
    Node *Successor(Node *p);

    void RotateLeft(Node *p);
    void RotateRight(Node *p);

    void InsertFixup(Node *p);

    void Delete(Node *p);
    void DeleteFixup(Node *p);

    void Dump(Node *n, int tabs);

  public:
    RBTree();

    Node *GetRoot();
    Node *Minimum(Node *p);
    Node *Maximum(Node *p);
    Node *Find(int val);

    void Insert(int val);

    void Remove(int val);

    void Dump();
    void InOrderTraversal(Node *p);
    void PreOrderTraversal(Node *p);
    void PostOrderTraversal(Node *p);
  };
}
#endif