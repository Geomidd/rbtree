#include "rbtree.hpp"

rbt::Node *rbt::Node::GetParent()
{
  return parent == nullptr ? nullptr : parent;
}

rbt::Node *rbt::Node::GetGrandparent()
{
  return parent == nullptr ? nullptr : parent->GetParent();
}

rbt::Node *rbt::Node::GetSibling()
{
  if (parent == nullptr)
    return nullptr;

  if (this == parent->left)
    return parent->right;
  else
    return parent->left;
}

rbt::Node *rbt::Node::GetUncle()
{
  return GetParent()->GetSibling();
}