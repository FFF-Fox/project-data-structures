#include <iostream>
#include <fstream>
#include <vector>
#include "alg.h"

/**
 * read_integers
 * Reads the integers from the filename into the Arr vector.
 * L is the length of the vector.
 */
void read_integers(std::string filename, std::vector<int> &Arr, int &L);

/* Testing */
void test_mergesort();
void test_linear_search();
void test_binary_search();
void test_interpolation_search();

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

    Arr = *alg::mergesort(&Arr, L);

    /* Testing */
    // test_mergesort();
    // test_linear_search();
    // test_binary_search();
    test_interpolation_search();

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

void test_mergesort()
{
    std::vector<int> Arr;
    int L = 10;

    for (int i = L; i >= 0; i--)
    {
        Arr.push_back(i);
    }

    Arr = *alg::mergesort(&Arr, L);

    for (int i = 1; i < L; i++)
    {
        if (Arr[i - 1] > Arr[i])
        {
            std::cout << "integers[i - 1] "
                      << " > "
                      << "integers[i]." << std::endl;
            return;
        }
    }
    std::cout << "Mergesort sorts correctly." << std::endl;
}

void test_linear_search()
{
    int L = 10;
    std::vector<int> Arr;

    for (int i = 0; i < L; i++)
    {
        Arr.push_back(i);
    }

    for (int i = -1; i < L; i++)
    {
        if (i < 0 || i >= L)
        {
            if (alg::linear_search(-1, Arr, L) != -1)
            {
                std::cout << "Linear search fails for " << i << std::endl;
                return;
            }
        }
        else
        {
            if (alg::linear_search(Arr[i], Arr, L) != i)
            {
                std::cout << "Linear search fails for " << i << std::endl;
                return;
            }
        }
    }

    std::cout << "Linear search passed the test." << std::endl;
}

void test_binary_search()
{
    int L = 10;
    std::vector<int> Arr;

    for (int i = 0; i < L; i++)
    {
        Arr.push_back(i);
    }

    for (int i = -1; i < L + 1; i++)
    {
        if (i < 0 || i >= L)
        {
            if (alg::binary_search(i, Arr, L) != -1)
            {
                std::cout << "Binary search fails for " << i << std::endl;
                return;
            }
        }
        else
        {
            if (alg::binary_search(Arr[i], Arr, L) != i)
            {
                std::cout << "Binary search fails for " << i << std::endl;
                return;
            }
        }
    }

    std::cout << "Binary search passed the test." << std::endl;
}

void test_interpolation_search()
{
    int L = 10;
    std::vector<int> Arr;

    for (int i = 0; i < L; i++)
    {
        Arr.push_back(i);
    }

    for (int i = -20; i < L + 20; i++)
    {
        if (i < 0 || i >= L)
        {
            if (alg::interpolation_search(i, Arr, L) != -1)
            {
                std::cout << "Interpolation search fails for " << i << std::endl;
                return;
            }
        }
        else
        {
            if (alg::interpolation_search(Arr[i], Arr, L) != i)
            {
                std::cout << "Interpolation search fails for " << i << std::endl;
                return;
            }
        }
    }

    std::cout << "Interpolation search passed the test." << std::endl;
}