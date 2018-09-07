#include "alg.h"

namespace alg
{
std::vector<int> *mergesort(std::vector<int> *Arr, int L)
{
    /* Return the single element. */
    if (L == 1)
    {
        return Arr;
    }
    int m = L / 2; /* int division. */

    /* Create two vectors.
        A1 contains elements of Arr [0 m).
        A2 contains elements of Arr [m L). */
    std::vector<int> *A1 = new std::vector<int>;
    for (int i = 0; i < m; i++)
    {
        A1->push_back((*Arr)[i]);
    }
    std::vector<int> *A2 = new std::vector<int>;
    for (int i = m; i < L; i++)
    {
        A2->push_back((*Arr)[i]);
    }

    /* Sort the two vectors. */
    int L1 = m;
    A1 = mergesort(A1, L1);
    int L2 = L - m;
    A2 = mergesort(A2, L2);

    /* Merge the two vectors, creating a sorted one. */
    std::vector<int> *out = new std::vector<int>;
    int i = 0;
    int j = 0;
    while (i < L1 && j < L2)
    {
        if ((*A1)[i] < (*A2)[j])
        {
            out->push_back((*A1)[i]);
            i++;
        }
        else
        {
            out->push_back((*A2)[j]);
            j++;
        }

        if (i == L1)
        {
            while (j != L2)
            {
                out->push_back((*A2)[j]);
                j++;
            }
        }
        else if (j == L2)
        {
            while (i != L1)
            {
                out->push_back((*A1)[i]);
                i++;
            }
        }
    }

    return out;
}
} // namespace alg