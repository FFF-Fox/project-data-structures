#include "RBTree.h"

#include <iostream>

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

void Rbt::restore(Node *z)
{
    while (z->parent && z->parent->color == RED)
    {
        if (z->parent->parent)
        {
            if (z->parent == z->parent->parent->left)
            {
                Node *y = z->parent->parent->right;
                if (y && y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        rotate_left(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotate_right(z->parent->parent);
                }
            }
            else if (z->parent == z->parent->parent->right)
            {
                Node *y = z->parent->parent->left;
                if (y && y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rotate_right(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rotate_left(z->parent->parent);
                }
            }
        }
    }
    root->color = BLACK;
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
    Node *n = new Node(x);
    if (x == z->data)
    {
        return;
    }
    else if (x < z->data)
    {
        n->parent = z;
        z->left = n;
    }
    else if (x > z->data)
    {
        n->parent = z;
        z->right = n;
    }

    // Balance tree
    restore(n);
}

void Rbt::print_node(int level, Node *z)
{
    level++;
    if (z->left)
        print_node(level, z->left);
    std::cout << "level: " << level << ", data: " << z->data << ", color: " << z->color << std::endl;
    if (z->right)
        print_node(level, z->right);
}

void Rbt::print_tree()
{
    print_node(0, root);
}
} // namespace rbt