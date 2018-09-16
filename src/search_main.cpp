#include <iostream>
#include <fstream>
#include <vector>
#include "alg.h"
#include "Cli.h"
#include "RBTree.h"

/**
 * read_integers
 * Reads the integers from the filename into the Arr vector.
 * L is the length of the vector.
 */
void read_integers(std::string filename, std::vector<int> &Arr, int &L);

/**
 * make_search_cli
 * Creates the user cli for integer searching.
 */
void make_search_cli(cli::Cli &search_cli, std::vector<int> &Arr, int &L);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Παρακαλώ εισάγετε το path του αρχείου με τις λέξεις για εισαγωγή στο trie..." << std::endl;
        std::cerr << "Χρήση: " << argv[0] << " FILENAME" << std::endl;

        return 1;
    }
    std::string filename = argv[1];

    std::vector<int> Arr;
    int L;
    read_integers(filename, Arr, L);

    alg::mergesort(Arr, L);

    cli::Cli search_cli;
    make_search_cli(search_cli, Arr, L);
    search_cli.start();

    return 0;
}

void read_integers(std::string filename, std::vector<int> &Arr, int &L)
{
    /* open file */
    std::ifstream infile(filename);

    std::string line;
    int number;
    L = 0;
    while (std::getline(infile, line))
    {
        number = std::stoi(line);
        Arr.push_back(number);
        L++;
    }
}

void make_search_cli(cli::Cli &search_cli, std::vector<int> &Arr, int &L)
{
    std::string menu =
        R"(1 - Linear search
2 - Binary search
3 - Interpolation search
q - έξοδος)";

    search_cli.set_menu_message(menu);

    search_cli.add_command("1", [&]() {
        std::string context = "[Linear search] ";
        std::string str;

        std::cout << context << "Πληκτρολογήστε τον αριθμό για αναζήτηση." << std::endl;
        search_cli.show_prompt();
        std::cin >> str;

        int x = std::stoi(str);
        int i = alg::linear_search(x, Arr, L);
        if (i >= 0)
        {
            std::cout << context << "Ο αριθμός βρέθηκε στη θέση: " << i << "." << std::endl;
        }
        else
        {
            std::cout << context << "Ο αριθμός δεν βρέθηκε." << std::endl;
        }
    });
    search_cli.add_command("2", [&]() {
        std::string context = "[Binary search] ";
        std::string str;

        std::cout << context << "Πληκτρολογήστε τον αριθμό για αναζήτηση." << std::endl;
        search_cli.show_prompt();
        std::cin >> str;

        int x = std::stoi(str);
        int i = alg::binary_search(x, Arr, L);
        if (i >= 0)
        {
            std::cout << context << "Ο αριθμός βρέθηκε στη θέση: " << i << "." << std::endl;
        }
        else
        {
            std::cout << context << "Ο αριθμός δεν βρέθηκε." << std::endl;
        }
    });
    search_cli.add_command("3", [&]() {
        std::string context = "[Interpolation search] ";
        std::string str;

        std::cout << context << "Πληκτρολογήστε τον αριθμό για αναζήτηση." << std::endl;
        search_cli.show_prompt();
        std::cin >> str;

        int x = std::stoi(str);
        int i = alg::interpolation_search(x, Arr, L);
        if (i >= 0)
        {
            std::cout << context << "Ο αριθμός βρέθηκε στη θέση: " << i << "." << std::endl;
        }
        else
        {
            std::cout << context << "Ο αριθμός δεν βρέθηκε." << std::endl;
        }
    });
}
