#pragma once
#include <string>

#define AB_size 26

namespace trie
{
class Node
{
  public:
    Node *children[AB_size];
    bool eow;
    int total_children;

    Node();
};
class Trie
{
  private:
    Node *root;

  public:
    Trie();

    bool find(std::string s);
    void insert(std::string s);
    void remove(std::string s);
};
} // namespace trie