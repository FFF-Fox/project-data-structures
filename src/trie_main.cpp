#include <iostream>
#include "Cli.h"
#include "Trie.h"

void make_trie_cli(cli::Cli& trie_cli, trie::Trie &t);

int main()
{
    trie::Trie t;

    cli::Cli trie_cli;
    make_trie_cli(trie_cli, t);
    trie_cli.start();

    return 0;
}

void make_trie_cli(cli::Cli& trie_cli, trie::Trie &t)
{
    std::string menu =
        R"(1 - αναζήτηση
2 - πρόσθεση
3 - διαγραφή
q - έξοδος)";

    trie_cli.set_menu_message(menu);

    trie_cli.add_command("0", [&]() { greet(menu); });
    trie_cli.add_command("1", [&]() {
        std::string context = "[Αναζήτηση] ";
        std::string str;

        std::cout << context << "Πληκτρολογήστε την λέξη για αναζήτηση." << std::endl;
        trie_cli.show_prompt();
        std::cin >> str;

        bool found = t.find(str);
        if (found)
        {
            std::cout << context << "Η λέξη βρέθηκε στο trie." << std::endl;
        }
        else
        {
            std::cout << context << "Η λέξη δεν βρέθηκε στο trie." << std::endl;
        }
    });
    trie_cli.add_command("2", [&]() {
        std::string context = "[Εισαγωγή] ";

        std::string str;
        std::cout << context << "Πληκτρολογήστε την λέξη για εισαγωγή." << std::endl;
        trie_cli.show_prompt();
        std::cin >> str;
        t.insert(str);

        std::cout << context << "Έγινε εισαγωγή." << std::endl;
    });
    trie_cli.add_command("3", [&]() {
        std::string context = "[Διαγραφή] ";

        std::string str;
        std::cout << "Πληκτρολογήστε την λέξη για διαγραφή." << std::endl;
        trie_cli.show_prompt();
        std::cin >> str;
        t.remove(str);
        std::cout << context << "Έγινε διαγραφή." << std::endl;
    });
}