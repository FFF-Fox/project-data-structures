#pragma once
#include <vector>
#include <functional>

namespace alg
{
void mergesort(std::vector<int> &Arr, int &L);

int linear_search(const int &x, const std::vector<int> &Arr, const int &L);
int binary_search(const int &x, const std::vector<int> &Arr, const int &L);
int interpolation_search(const int &x, const std::vector<int> &Arr, const int &L);

unsigned long long benchmark(std::function<void()> func);
} // namespace alg