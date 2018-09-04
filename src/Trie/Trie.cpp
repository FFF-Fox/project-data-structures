#include "Trie.h"
// #include <bits/stdc++.h>

namespace trie
{
/**
 * Node constructor.
*/
Node::Node() : eow(false), total_children(0)
{
    for (int i = 0; i < AB_size; i++)
    {
        children[i] = nullptr;
    }
}

/**
 * Trie constructor.
 */
Trie::Trie() : root(new Node){};

/**
 * Trie::insert
 * Inserts a string to the trie.
 */
void Trie::insert(std::string s)
{
    Node *n = root;

    /* Traverse down the tree, creating nodes if they don't
        already exist. */
    for (int i = 0; i < s.length(); i++)
    {
        int index = s[i] - 'a';
        if (!n->children[index])
        {
            n->children[index] = new Node;
        }
        n = n->children[index];
    }

    /* Mark the final node as end of word if it isn't already. */
    if (!n->eow)
    {
        n->eow = true;
        n->total_children++;
    }
}

/**
 * Trie::find
 * Checks whether the given string is contained in the trie.
 */
bool Trie::find(std::string s)
{
    Node *n = root;

    /* Traverse down the trie until the end of the word.
        If a node to be traversed doesn't exist, then the word
        is not contained in the trie. */
    for (int i = 0; i < s.length(); i++)
    {
        int index = s[i] - 'a';
        if (!n->children[index])
        {
            return false;
        }
        else
        {
            n = n->children[index];
        }
    }

    return n->eow;
}
} // namespace trie