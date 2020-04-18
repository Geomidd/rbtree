#ifndef RBTREE_H
#define RBTREE_H

namespace rbt
{
  enum NodeColor
  {
    BLACK,
    RED
  };

  template<class T, class U>
  struct Node
  {
    T key;
    U value;
    NodeColor color;
    Node<T, U> *left;
    Node<T, U> *right;
    Node<T, U> *parent;
  };

  template<class T, class U>
  class RBTree
  {
  private:
    Node<T, U> *root;
    Node<T, U> *nil;

    Node<T, U> *Predecessor(Node<T, U> *p)
    {
      if (p->left != nil)
      {
        return Maximum(p->left);
      }

      Node<T, U> *y = p;
      while (y != nil && y == y->parent->left)
      {
        y = y->parent;
      }
      return (y == nil ? nil : y->parent);
    }
    Node<T, U> *Successor(Node<T, U> *p)
    {
      if (p->right != nil)
      {
        return Minimum(p->right);
      }

      Node<T, U> *y = p;
      while (y != nil && y == y->parent->right)
      {
        y = y->parent;
      }
      return (y == nil ? nil : y->parent);
    }

    void RotateLeft(Node<T, U> *p)
    {
      Node<T, U> *y = p->right;
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
    void RotateRight(Node<T, U> *p)
    {
      Node<T, U> *y = p->left;
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

    void InsertFixup(Node<T, U> *p)
    {
      Node<T, U> *z = p;
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

    void Delete(Node<T, U> *p)
    {
      Node<T, U> *x = nil;
      Node<T, U> *y = nil;
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
    void DeleteFixup(Node<T, U> *p)
    {
      Node<T, U> *w = nil;
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

    void Dump(Node<T, U> *n, int tabs)
    {
      if (n == nullptr || n == nil)
      {
        return;
      }

      Dump(n->left, tabs + 1);

      for (int i = 0; i < tabs; ++i)
      {
        std::cout << "\t\t";
      }
      char color = n->color == 0 ? 'B' : 'R';
      std::cout << n->key << color << "(" << n->parent->key << ")" << std::endl;

      Dump(n->right, tabs + 1);
    }

  public:
    RBTree()
    {
      nil = new Node<T, U>;
      nil->key = T();
      nil->value = U();
      nil->left = nullptr;
      nil->right = nullptr;
      nil->parent = nullptr;
      root = nil;
    }

    Node<T, U> *GetRoot() { return root; }
    Node<T, U> *Minimum(Node<T, U> *p)
    {
      while (p->left != nil)
      {
        p = p->left;
      }
      return p;
    }
    Node<T, U> *Maximum(Node<T, U> *p)
    {
      while (p->right != nil)
      {
        p = p->right;
      }
      return p;
    }
    Node<T, U> *Find(T key)
    {
      Node<T, U> *containingNode = root;
      while (containingNode != nullptr)
      {
        if (key < containingNode->key)
        {
          containingNode = containingNode->left;
        } else if (key > containingNode->key)
        {
          containingNode = containingNode->right;
        } else
        {
          break;
        }
      }

      if (containingNode == nullptr || key != containingNode->key)
      {
        std::cout << key << " not found in tree" << std::endl;
        return nullptr;
      }
      return containingNode;
    }
    U GetValueFromKey(T key)
    {
      Node<T, U> *n = Find(key);
      if (n == nil || n == nullptr) return NULL;

      return n->value;
    }
    bool UpdateValue(T key, U val)
    {
      auto n = Find(key);
      if (n == nullptr || n == nil) return false;

      n->value = val;
      return n->value == val;
    }

    void Insert(T key, U value = U())
    {
      Node<T, U> *x = root;
      Node<T, U> *y = nil;
      while (x != nil)
      {
        y = x;
        if (x->key > key)
        {
          x = x->left;
        } else
        {
          x = x->right;
        }
      }
      Node<T, U> *temp = new Node<T, U>;
      temp->key = key;
      temp->value = value;
      temp->left = nil;
      temp->right = nil;
      temp->parent = y;
      temp->color = RED;
      if (temp->parent == nil)
      {
        root = temp;
      } else
      {
        if (key < y->key)
        {
          y->left = temp;
        } else
        {
          y->right = temp;
        }
      }
      InsertFixup(temp);
    }

    void Remove(T key)
    {
      Node<T, U> *n = Find(key);
      if (n == nullptr || n->key != key)
      {
        return;
      }
      Delete(n);
    }

    void Dump() { Dump(root, 0); }
    void InOrderTraversal(Node<T, U> *p)
    {
      if (p == nullptr || p == nil)
      {
        return;
      }
      InOrderTraversal(p->left);
      std::cout << p->key << (p->color == 0 ? 'B' : 'R') << " ";
      InOrderTraversal(p->right);
    }
    void PreOrderTraversal(Node<T, U> *p)
    {
      if (p == nullptr || p == nil)
      {
        return;
      }
      std::cout << p->key << (p->color == 0 ? 'B' : 'R') << " ";
      InOrderTraversal(p->left);
      InOrderTraversal(p->right);
    }
    void PostOrderTraversal(Node<T, U> *p)
    {
      if (p == nullptr || p == nil)
      {
        return;
      }
      InOrderTraversal(p->left);
      InOrderTraversal(p->right);
      std::cout << p->key << (p->color == 0 ? 'B' : 'R') << " ";
    }
  };
}
#endif