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

/**
 * fill_tree
 * Insert the elements of the Arr vector to the tree.
 */
void fill_tree(rbt::Rbt &t, std::vector<int> &Arr);

/* Testing */
void run_tests(std::vector<int> &Arr, int &L, rbt::Rbt &t);
void test_mergesort(std::vector<int> &Arr, int &L);
void test_linear_search(std::vector<int> &Arr, int &L);
void test_binary_search(std::vector<int> &Arr, int &L);
void test_interpolation_search(std::vector<int> &Arr, int &L);
void test_tree(rbt::Rbt &t, std::vector<int> &Arr, int &L);

/* Benchmarking */
void run_benchmarks(std::vector<int> &Arr, const int &L, rbt::Rbt &t);

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

    rbt::Rbt t;
    fill_tree(t, Arr);

    /* Testing */
    run_tests(Arr, L, t);

    /* Benchmarking */
    // run_benchmarks(Arr, L, t);

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

void fill_tree(rbt::Rbt &t, std::vector<int> &Arr)
{
    for (auto n : Arr)
    {
        t.insert(n);
    }
}

void run_tests(std::vector<int> &Arr, int &L, rbt::Rbt &t)
{
    std::cout << "**" << std::endl
              << "* Running Tests" << std::endl
              << "**" << std::endl;
    test_mergesort(Arr, L);
    // test_linear_search(Arr, L);
    test_binary_search(Arr, L);
    test_interpolation_search(Arr, L);
    test_tree(t, Arr, L);
}

void test_mergesort(std::vector<int> &Arr, int &L)
{
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

void test_linear_search(std::vector<int> &Arr, int &L)
{
    for (int i = -1; i < L; i++)
    {
        if (i < 0)
        {
            if (alg::linear_search(-1, Arr, L) != -1)
            {
                std::cout << "Linear search fails for " << i << std::endl;
                return;
            }
        }
        else
        {
            if (alg::linear_search(Arr[i], Arr, L) < 0)
            {
                std::cout << "Linear search fails for " << i << std::endl;
                return;
            }
        }
    }

    std::cout << "Linear search passed the test." << std::endl;
}

void test_binary_search(std::vector<int> &Arr, int &L)
{
    for (int i = -1; i < L; i++)
    {
        if (i < 0)
        {
            if (alg::binary_search(-1, Arr, L) != -1)
            {
                std::cout << "Binary search fails for " << i << std::endl;
                return;
            }
        }
        else
        {
            if (alg::binary_search(Arr[i], Arr, L) < 0)
            {
                std::cout << "Binary search fails for " << i << std::endl;
                return;
            }
        }
    }

    std::cout << "Binary search passed the test." << std::endl;
}

void test_interpolation_search(std::vector<int> &Arr, int &L)
{
    for (int i = -1; i < L; i++)
    {
        if (i < 0)
        {
            if (alg::interpolation_search(-1, Arr, L) != -1)
            {
                std::cout << "Interpolation search fails for " << i << std::endl;
                return;
            }
        }
        else
        {
            if (alg::interpolation_search(Arr[i], Arr, L) < 0)
            {
                std::cout << "Interpolation search fails for " << i << std::endl;
                return;
            }
        }
    }

    std::cout << "Interpolation search passed the test." << std::endl;
}

void test_tree(rbt::Rbt &t, std::vector<int> &Arr, int &L)
{
    if (!t.check_rules())
    {
        std::cout << "The red-black tree is not correct." << std::endl;
        return;
    }

    for (int i = 0; i < L; i++)
    {
        if (!t.search(Arr[i]))
        {
            std::cout << "Red-black tree search for " << i << " failed." << std::endl;
            return;
        }
    }

    std::cout << "Red-black tree passed the test." << std::endl;
}

void run_benchmarks(std::vector<int> &Arr, const int &L, rbt::Rbt &t)
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

    // red-black tree search benchmark.
    std::cout << "Red-black tree search: ";
    alg::benchmark([&]() {
        for (int x = min; x < max; x += step)
        {
            t.search(x);
        }
    });
}
