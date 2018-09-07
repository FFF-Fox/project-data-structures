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
 * index
 * Given a latin character in lower/upper case,
 * return the appropriate index of the Node.children array.
 */
int Trie::index(char c)
{
    int i = c;
    if (i >= 97)
    {
        i -= 6;
    }
    i -= 'A';

    return i;
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
        int ch_i = index(s[i]);
        if (!n->children[ch_i])
        {
            n->children[ch_i] = new Node;
            n->total_children++;
        }
        n = n->children[ch_i];
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
        int ch_i = index(s[i]);
        if (!n->children[ch_i])
        {
            return false;
        }
        else
        {
            n = n->children[ch_i];
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
        int ch_i = index(s[i]);
        if (!n->children[ch_i])
        {
            return;
        }
        else
        {
            S.push(n->children[ch_i]);
            I.push(ch_i);
            n = n->children[ch_i];
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