#pragma once
/**
 * Longest Increasing Subsequence
 */

#include <list>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>

namespace ns_lissq {
const int neg_inf = std::numeric_limits<int>::min();
const int inf = std::numeric_limits<int>::max();

struct extended_array;
int upper_bound(extended_array &a, int *d, int n, int x);
}

std::list<int> lissq(int *data, size_t n);
