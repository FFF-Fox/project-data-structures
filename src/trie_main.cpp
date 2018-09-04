#include <iostream>
#include "Trie.h"

int main() {

    std::cout << "Hello!" << std::endl;
    
    trie::Trie t;

    t.insert("what");
    t.insert("abc");

    bool a1 = t.find("what");
    bool a2 = t.find("abc");
    bool a3 = t.find("ab");
    bool a4 = t.find("");

    std::cout << "'what' found: " << a1 << std::endl;
    std::cout << "'abc' found: " << a2 << std::endl;
    std::cout << "'ab' found: " << a3 << std::endl;
    std::cout << "'' found: " << a4 << std::endl;

    t.insert("");
    a4 = t.find("");
    std::cout << "'' found after inserted: " << a4 << std::endl;

    return 0;
}