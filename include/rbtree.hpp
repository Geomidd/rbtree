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

    void RepairTree(Node *n);
    // Repair cases
    void RepairCase1(Node *n);  // If node is root, set black
    void RepairCase2(Node *n);  // If node's parent is black, do nothing
    void RepairCase3(Node *n);  // If node's parent & uncle are black, switch to black; switch grandparent to red & repair again
    void RepairCase4(Node *n);  // If the parent is red but uncle is black, 1) rotate to the outside and 2) then rotate grandparent the opposite direction and update colors
    void RepairCase4Step2(Node *n);

    void RotateLeft(Node *n);
    void RotateRight(Node *n);
  };
}

#endif