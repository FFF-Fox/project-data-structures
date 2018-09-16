#include "RBTree.h"

#include <iostream>

namespace rbt
{
/**
 * Node constructor
 * Creates a single red node with the data specified.
 */
Node::Node(int n) : data(n), color(RED),
                    parent(nullptr), left(nullptr), right(nullptr) {}

/**
 * Rbt constructor
 * Initialize the root ptr of the tree.
 */
Rbt::Rbt() : root(nullptr) {}

/**
 * access
 * Helper function. Given an int x, traverse down the tree until
 * a node with data = x is found, or a leaf is reached and return that
 * node.
 */
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

/**
 * rotate_left, rotate_right
 * Implement the rotations.
 */
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

/**
 * restore
 * Used by insert(...) to balance the tree.
 */
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

/**
 *  insert
 *  Given an int x, check whether the x doesn't exist and insert it. 
 */
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

/**
 *  search
 *  Try to find the int value x in the tree. 
 */
bool Rbt::search(int x)
{
    if (!root)
    {
        return false;
    }

    Node *z = access(x);
    return (x == z->data);
}

/**
 *  Debugging
 */
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

int Rbt::count_blk(Node *z)
{
    int LB = 0;
    int RB = 0;

    if (z->left)
        LB = count_blk(z->left);
    if (z->right)
        RB = count_blk(z->right);

    if (LB < 0 || RB < 0)
        return -1;

    if (LB != RB)
        return -1;

    if (z->color == BLACK)
        LB++;

    return LB;
}

bool Rbt::check_red(Node *z, int p_color)
{
    bool L = true, R = true;
    if (z->left)
        L = check_red(z->left, z->color);
    if (z->right)
        R = check_red(z->right, z->color);

    if (!(L && R))
        return false;
    if (p_color == RED && z->color == RED)
        return false;

    return true;
}

bool Rbt::check_rules()
{
    if (!root)
    {
        return true;
    }
    if (root->color != BLACK)
    {
        return false;
    }

    int LB, RB;
    bool LR, RR;
    if (root->left)
    {
        LB = count_blk(root->left);
        LR = check_red(root->left, root->color);
        if (LB < 0 || !LR)
            return false;
    }
    if (root->right)
    {
        RB = count_blk(root->right);
        RR = check_red(root->right, root->color);
        if (RB < 0 || !RR)
            return false;
    }
    if (RB != LB)
        return false;

    return true;
}
} // namespace rbt