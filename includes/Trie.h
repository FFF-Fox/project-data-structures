#pragma once
#include <vector>

namespace trie
{
struct node_element
{
    char letter;
    bool wordContained;

    node* child;
};

struct node
{
    std::vector<node_element> elements;
};

class Trie
{
  private:
    node *root;

  public:
    Trie() : root(new node){};

    node_element *find(const char *x);
    void instert(const char *x);
};
} // namespace trie