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

struct extended_array {
    int *a;

    extended_array(int *a)
    : a(a)
    {}

    int operator[](size_t n) {
        if (n == neg_inf) {
            return neg_inf;
        } else if (n == inf) {
            return inf;
        } else {
            return a[n];
        }
    }
};

int upper_bound(extended_array &a, int *d, int n, int x) {
    int l = 0;
    int r = n-1;
    int m;
    while (l<r) {
        m = l+(r-l)/2;
        if (x >= a[d[m]]) {
            l = m+1;
        } else {
            r = m;
        }
    }
    return l;
}
}

std::list<int> lissq(int *data, size_t n) {
    using namespace ns_lissq;
    extended_array a(data);
    int *d = new int[n+1];
    int *p = new int[n];
    int max = 0;
    d[0] = neg_inf;
    for (size_t i=1; i<=n; ++i) {
        d[i] = inf;
    }
    for (size_t i=0; i<n; ++i) {
        p[i] = neg_inf;
    }
    for (size_t i=0; i<n; ++i) {
        int j = upper_bound(a, d, n+1, a[i]);
        if (a[d[j-1]] < a[i] && a[i] < a[d[j]]) {
            d[j] = i;
            p[i] = d[j-1];
            if (a[d[max]] < a[d[j]]) {
                max = j;
            }
        }
    }

    std::list<int> subsequence;
    for (int i = d[max]; i != neg_inf; i = p[i]){
        subsequence.push_front(a[i]);
    }
    return subsequence;
}
