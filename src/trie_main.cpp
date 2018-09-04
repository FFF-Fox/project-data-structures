#include <iostream>
#include <stack>
#include "Trie.h"

int main()
{
    trie::Trie t;

    t.insert("a");
    t.insert("aa");
    
    t.remove("a");
    t.remove("e");

    bool a1 = t.find("a");
    bool a2 = t.find("aa");

    std::cout << "Found 'a': " << a1 << std::endl;
    std::cout << "Found 'aa': " << a2 << std::endl;

    return 0;
}