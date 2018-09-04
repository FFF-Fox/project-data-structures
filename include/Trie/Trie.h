#pragma once
#include <vector>

namespace trie
{
// typedef std::vector<node_element> node;

struct node
{
    struct node_element
    {
        std::vector<node_element> elements;
        char letter;
        bool wordContained;

        node *child;
    };

    std::vector<node_element> elements;
};

class Trie
{
  private:
    node *root;

  public:
    Trie() : root(new node){};

    bool find(const char *x);
    void insert(const char *x);
};
} // namespace trie