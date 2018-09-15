#include <iostream>
#include <fstream>
#include <vector>
#include "alg.h"
#include "RBTree.h"

/**
 * read_integers
 * Reads the integers from the filename into the Arr vector.
 * L is the length of the vector.
 */
void read_integers(std::string filename, std::vector<int> &Arr, int &L);

/* Testing */
void run_tests();
void test_mergesort();
void test_linear_search();
void test_binary_search();
void test_interpolation_search();

/* Benchmarking */
void run_benchmarks(std::vector<int> &Arr, const int &L);

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

    // /* Testing */
    // run_tests();

    // /* Benchmarking */
    // run_benchmarks(Arr, L);

    rbt::Rbt t;

    for (auto n : Arr)
    {
        t.insert(n);
    }

    for (auto n : Arr)
    {
        if (!t.search(n))
        {
            std::cout << "Error, " << n << " not found!" << std::endl;
        }
    }

    if (t.search(-1))
    {
        std::cout << "Error, " << -1 << " found!" << std::endl;
    }

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

void run_tests()
{
    std::cout << "**" << std::endl
              << "* Running Tests" << std::endl
              << "**" << std::endl;
    test_mergesort();
    test_linear_search();
    test_binary_search();
    test_interpolation_search();
}

void test_mergesort()
{
    std::vector<int> Arr;
    int L = 10;

    for (int i = L; i >= 0; i--)
    {
        Arr.push_back(i);
    }

    alg::mergesort(Arr, L);

    for (int i = 1; i < L; i++)
    {
        if (Arr[i - 1] > Arr[i])
        {
            std::cout << Arr[i - 1]
                      << " > "
                      << Arr[i] << std::endl;
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

void run_benchmarks(std::vector<int> &Arr, const int &L)
{
    const int total_searches = L + 2000;
    const int min = Arr[0] - 1000;
    const int max = Arr[L - 1] + 1000;
    const int step = (max - min) / total_searches;

    std::cout << "**" << std::endl
              << "* Running Benchmarks" << std::endl
              << "* Calculating time in ms for " << total_searches << " searches." << std::endl
              << "**" << std::endl;

    // linear search benchmark.
    std::cout << "Linear search: ";
    alg::benchmark([&]() {
        for (int x = min; x < max; x += step)
        {
            alg::linear_search(x, Arr, L);
        }
    });

    // binary search benchmark.
    std::cout << "Binary search: ";
    alg::benchmark([&]() {
        for (int x = min; x < max; x += step)
        {
            alg::binary_search(x, Arr, L);
        }
    });

    // interpolation search benchmark.
    std::cout << "Interpolation search: ";
    alg::benchmark([&]() {
        for (int x = min; x < max; x += step)
        {
            alg::interpolation_search(x, Arr, L);
        }
    });
}
