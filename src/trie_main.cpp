#include <iostream>
#include <fstream>
#include <string>
#include "Cli.h"
#include "Trie.h"

/* testing */
#include <vector>
#include <algorithm>

void read_words(std::string filename, trie::Trie &t);
void make_trie_cli(cli::Cli &trie_cli, trie::Trie &t);

/* testing */
void test_trie(std::string filename);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Παρακαλώ εισάγετε το path του αρχείου με τις λέξεις για εισαγωγή στο trie..." << std::endl;
        std::cerr << "Χρήση: " << argv[0] << " FILENAME" << std::endl;

        return 1;
    }
    std::string filename = argv[1];

    /**
     *  testing
     *  /!\ Contains O(n^2) operation (n: total words).
     * 
     *  test_trie(filename);
     */

    /**
     * main program
     * Initializes the trie and starts the cli.
     * 1. Reads the words from the txt file and inserts them in the trie.
     * 2. Starts the cli. The user can search, insert, remove words.
     */
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

    /**
     * Sort and filter unique words.
     */
    std::sort(words.begin(), words.end());
    std::vector<std::string> unq_words;
    std::string w;
    for (int i = 0; i < words.size(); i++)
    {
        if (i == 0)
        {
            w = words[i];
            unq_words.push_back(w);
        }
        else
        {
            if (words[i] != w)
            {
                w = words[i];
                unq_words.push_back(w);
            }
        }
    }
    words = unq_words;

    /* Test insertions */
    for (int i = 0; i < words.size(); i++)
    {
        if (!t.find(words[i]))
        {
            std::cout << words[i] << " not found!" << std::endl;
            return;
        }
    }
    std::cout << "All words found!" << std::endl;

    /* Test removals */
    for (int i = 0; i < words.size(); i++)
    {
        /* Test that removed word doesn't exist anymore. */
        t.remove(words[i]);
        if (t.find(words[i]))
        {
            std::cout << words[i] << " wasn't removed successfully!" << std::endl;
            return;
        }
        /* Test that no other existing word got removed. */
        for (int j = i + 1; j < words.size(); j++)
        {
            if (!t.find(words[j]))
            {
                std::cout << words[j] << " not found, after deleting " << words[i] << "!" << std::endl;
                return;
            }
        }
    }
    std::cout << "All words removed successfully!" << std::endl;

    std::cout << "All tests passed." << std::endl;
}
