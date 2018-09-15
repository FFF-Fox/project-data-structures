#include "RBTree.h"

namespace rbt
{
Node::Node(int n) : data(n), color(RED),
                    parent(nullptr), left(nullptr), right(nullptr) {}

Rbt::Rbt() : root(nullptr) {}

Node *Rbt::access(int x)
{
    Node *z = root;

    if (!root)
    {
        return nullptr;
    }

    while (z)
    {
        if (z->data == x)
        {
            return z;
        }

        if (x < z->data)
        {
            if (z->left)
            {
                z = z->left;
            }
            else
            {
                return z;
            }
        }
        else if (x > z->data)
        {
            if (z->right)
            {
                z = z->right;
            }
            else
            {
                return z;
            }
        }
    }
}

void Rbt::rotate_left(Node *x)
{
    Node *y = x->right;
    x->right = y->left;

    if (y->left)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void Rbt::rotate_right(Node *x)
{
    Node *y = x->left;
    x->left = y->right;

    if (y->right)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent)
    {
        root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void Rbt::insert(int x)
{
    if (!root)
    {
        root = new Node(x);
        root->color = BLACK;
        return;
    }

    Node *z = access(x);
    if (x == z->data)
    {
        return;
    }
    else if (x < z->data)
    {
        Node *n = new Node(x);
        n->parent = z;
        z->left = n;
    }
    else if (x > z->data)
    {
        Node *n = new Node(x);
        n->parent = z;
        z->right = n;
    }

    // Balance tree
}
} // namespace rbt