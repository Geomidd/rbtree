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
    Node *parent;
    NodeColor color;
    Node *left;
    Node *right;
  };

  class RBTree
  {
  public:
    RBTree();
    ~RBTree();
    const Node *GetRoot();
    void Insert(int val);
    void Remove(int val);
    void TraverseInOrder(Node *current);
    void Dump();

  private:
    Node *root;

    // Insertion
    void Insert(Node *n);
    void InsertFixup(Node *n);
    void InsertRecursive(Node *current, Node *n);
    void RepairTree(Node *n);
    //// Repair cases
    void RepairCase1(Node *n);  // If node is root, set black
    void RepairCase2(Node *n);  // If node's parent is black, do nothing
    void RepairCase3(Node *n);  // If node's parent & uncle are black, switch to black; switch grandparent to red & repair again
    void RepairCase4(Node *n);  // If the parent is red but uncle is black, 1) rotate to the outside and 2) then rotate grandparent the opposite direction and update colors
    void RepairCase4Step2(Node *n);

    // Deletion/removal
    void DeleteNode(Node *n);
    void Remove(Node *n);

    Node *Find(int val);

    void RotateLeft(Node *x);
    void RotateRight(Node *n);

    Node *GetParent(Node *n);
    Node *GetSibling(Node *n);
    Node *GetUncle(Node *n);
    Node *GetGrandparent(Node *n);
    void Transplant(Node *dest, Node *src);
    Node *Minimum(Node *n);
    void RemoveFixup(Node *n, NodeColor originalColor);
    void Dump(Node *node, int tabs);
  };
}

#endif