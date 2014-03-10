#pragma once
/**
 * Longest Increasing Subsequence
 */

#include <list>
#include <vector>
#include <limits>
#include <algorithm>

namespace ns_lissq {
const int neg_inf = std::numeric_limits<int>::min();
const int inf = std::numeric_limits<int>::max();

struct extended_vector;
int upper_bound(extended_vector &a, std::vector<int> d, int n, int x);
}

void lissq(const std::vector<int> &data, std::list<int> &lis);
