#include "Trie.h"
#include <stack>

namespace trie
{
/**
 * Node constructor.
 * Fills the children array with null pointers.
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
            n->total_children++;
        }
        n = n->children[index];
    }

    /* Mark the final node as end of word if it isn't already. */
    if (!n->eow)
    {
        n->eow = true;
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

/**
 * Trie::remove
 * Removes the given string from the trie, if it exists.
 */
void Trie::remove(std::string s)
{
    Node *n = root;

    /* A stack is used to keep the nodes traversed.
        It is used to remove unnecessary nodes after
        a removal. */
    std::stack<Node *> S;
    std::stack<int> I;
    S.push(n);

    /* Traverse the trie to find whether the word exists. */
    for (int i = 0; i < s.length(); i++)
    {
        int index = s[i] - 'a';
        if (!n->children[index])
        {
            return;
        }
        else
        {
            S.push(n->children[index]);
            I.push(index);
            n = n->children[index];
        }
    }

    /* If the word exists, delete all the nodes from the eow to the root
        that don't have children. */
    if (S.top()->eow)
    {
        S.top()->eow = false;

        while (!S.empty() && S.top()->total_children == 0 && !S.top()->eow)
        {
            if (S.top() != root)
            {
                delete S.top();
            }
            S.pop();

            if (!S.empty())
            {
                S.top()->total_children--;
                S.top()->children[I.top()] = nullptr;
                I.pop();
            }
        }
    }
}
} // namespace trie