#include <iostream>
#include "Cli.h"
#include "Trie.h"

void greet(std::string msg);

int main()
{
    std::string menu =
        R"(1 - αναζήτηση
2 - πρόσθεση
3 - διαγραφή
q - έξοδος)";

    trie::Trie t;

    cli::Cli trie_cli;

    trie_cli.set_menu_message(menu);

    trie_cli.add_command("0", [&]() { greet(menu); });
    trie_cli.add_command("1", [&]() {

    });

    trie_cli.start();

    return 0;
}

void greet(std::string msg)
{
    std::cout << msg << std::endl;
}