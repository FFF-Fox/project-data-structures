#include "alg.h"

namespace alg
{
/**
 * mergesort
 * Sort a vector (Arr) of length L.
 */
void mergesort(std::vector<int> &Arr, int L)
{
    /* Return the single element. */
    if (L == 1)
    {
        return;
    }
    int m = L / 2; /* int division. */

    /* Create two vectors.
        A1 contains elements of Arr [0 m).
        A2 contains elements of Arr [m L). */
    std::vector<int> A1;
    for (int i = 0; i < m; i++)
    {
        A1.push_back(Arr[i]);
    }
    std::vector<int> A2;
    for (int i = m; i < L; i++)
    {
        A2.push_back(Arr[i]);
    }

    /* Sort the two vectors. */
    int L1 = m;
    mergesort(A1, L1);
    int L2 = L - m;
    mergesort(A2, L2);

    /* Merge the two vectors, creating a sorted one. */
    // std::vector<int> *out = new std::vector<int>;
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < L1 && j < L2)
    {
        if (A1[i] < A2[j])
        {
            Arr[k] = A1[i];
            i++;
        }
        else
        {
            Arr[k] = A2[j];
            j++;
        }
        k++;

        if (i == L1)
        {
            while (j != L2)
            {
                Arr[k] = A2[j];
                j++;
                k++;
            }
        }
        else if (j == L2)
        {
            while (i != L1)
            {
                Arr[k] = A1[i];
                i++;
                k++;
            }
        }
    }
}

/**
 * linear_search
 * Search each element of the vector from start to finish for x.
 */
int linear_search(const int &x, const std::vector<int> &Arr, const int &L)
{
    for (int i = 0; i < L; i++)
    {
        if (Arr[i] == x)
        {
            return i;
        }
    }

    return -1;
}

/**
 * binary_search
 * Search a sorted vector for x with binary search.
 */
int binary_search(const int &x, const std::vector<int> &Arr, const int &L)
{
    int l = 0;
    int r = L - 1;
    int m;

    while (l <= r)
    {
        m = l + (r + 1 - l) / 2;

        if (x == Arr[m])
        {
            return m;
        }
        else if (x < Arr[m])
        {
            r = m - 1;
        }
        else if (x > Arr[m])
        {
            l = m + 1;
        }
    }

    return -1;
}

/**
 * interpolation_search
 * Search a sorted vector for x with interpolation search.
 */
int interpolation_search(const int &x, const std::vector<int> &Arr, const int &L)
{
    int l = 0;
    int r = L - 1;
    int pos;

    while (l <= r && x >= Arr[l] && x <= Arr[r])
    {
        pos = l + ((r - l) / Arr[r] - Arr[l]) * (x - Arr[l]);

        if (x == Arr[pos])
        {
            return pos;
        }
        else if (x < Arr[pos])
        {
            r = pos - 1;
        }
        else if (x > Arr[pos])
        {
            l = pos + 1;
        }
    }

    return -1;
}
} // namespace alg