#pragma once

#define BLACK 0
#define RED 1

namespace rbt
{
struct Node
{
    int data;
    int color;
    Node *parent;
    Node *left;
    Node *right;

    Node(int n);
};

class Rbt
{
  private:
    Node *root;

    Node *access(int x);

    void rotate_left(Node *x);
    void rotate_right(Node *x);
    void restore(Node *z);

    void print_node(int level, Node *z); /* Debug */

  public:
    Rbt();

    void insert(int x);
    bool search(int x);

    void print_tree(); /* Debug */
};
} // namespace rbt