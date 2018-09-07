#pragma once
#include <string>

#define AB_size 52

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

    int index(char c);

  public:
    Trie();

    bool find(std::string s);
    void insert(std::string s);
    void remove(std::string s);
};
} // namespace trie