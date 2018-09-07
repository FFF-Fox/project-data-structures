#include <iostream>
#include <fstream>
#include <string>
#include "Cli.h"
#include "Trie.h"

#include <vector> /* testing */

void read_words(std::string filename, trie::Trie &t);
void make_trie_cli(cli::Cli &trie_cli, trie::Trie &t);

void test_trie(std::string filename); /* testing */

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Παρακαλώ εισάγετε το path του αρχείου με τις λέξεις για εισαγωγή στο trie..." << std::endl;
        std::cerr << "Χρήση: " << argv[0] << " FILENAME" << std::endl;

        return 1;
    }

    std::string filename = argv[1];
    trie::Trie t;

    read_words(filename, t);

    cli::Cli trie_cli;
    make_trie_cli(trie_cli, t);
    trie_cli.start();

    return 0;
}

void read_words(std::string filename, trie::Trie &t)
{
    /* open file */
    std::ifstream infile(filename);

    /* for each line:
        1. parse string
        2. insert to trie */
    std::string line;
    while (std::getline(infile, line))
    {
        t.insert(line);
    }
}

void make_trie_cli(cli::Cli &trie_cli, trie::Trie &t)
{
    std::string menu =
        R"(1 - αναζήτηση
2 - πρόσθεση
3 - διαγραφή
q - έξοδος)";

    trie_cli.set_menu_message(menu);

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

void test_trie(std::string filename)
{
    trie::Trie t;

    /* open file */
    std::ifstream infile(filename);
    std::vector<std::string> words;

    std::string line;
    while (std::getline(infile, line))
    {
        words.push_back(line);
        t.insert(line);
    }

    for (int i = 0; i < words.size(); i++)
    {
        if (!t.find(words[i]))
        {
            std::cout << words[i] << " not found!" << std::endl;
            return;
        }
    }
    std::cout << "All words found!" << std::endl;

    for (int i = 0; i < words.size(); i++)
    {
        t.remove(words[i]);
        if (t.find(words[i]))
        {
            std::cout << words[i] << " wasn't removed successfully!" << std::endl;
            return;
        }
    }
    std::cout << "All words removed successfully!" << std::endl;

    std::cout << "All tests passed." << std::endl;
}
