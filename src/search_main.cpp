#include <iostream>
#include <fstream>
#include <vector>
#include "alg.h"

/**
 * read_integers
 * Reads the integers from the filename into the Arr vector.
 * L is the length of the vector.
 */
void read_integers(std::string filename, std::vector<int>& Arr, int& L);

/* Testing */
void test_mergesort(std::string filename);

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
     * Testing
     * 
     * test_mergesort(filename);
     */

    std::vector<int> Arr;
    int L;
    read_integers(filename, Arr, L);

    Arr = *alg::mergesort(&Arr, L);

    return 0;
}

void read_integers(std::string filename, std::vector<int>& Arr, int& L)
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

void test_mergesort(std::string filename)
{
    std::vector<int> *integers = new std::vector<int>;

    /* open file */
    std::ifstream infile(filename);

    std::string line;
    int number;
    int L = 0;
    while (std::getline(infile, line))
    {
        number = std::stoi(line);
        integers->push_back(number);
        L++;
    }

    integers = alg::mergesort(integers, L);

    for (int i = 1; i < L; i++)
    {
        if ((*integers)[i - 1] > (*integers)[i])
        {
            std::cout << "integers[i - 1] "
                      << " > "
                      << "integers[i]." << std::endl;
            return;
        }
    }
    std::cout << "Mergesort sorts correctly." << std::endl;
}