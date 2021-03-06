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

    int count_blk(Node *z); /* Debug */
    bool check_red(Node *z, int p_color); /* Debug */

  public:
    Rbt();

    void insert(int x);
    bool search(int x);

    bool check_rules(); /* Debug */
    void print_tree(); /* Debug */
};
} // namespace rbt