#include "dsu.h"

dsu::dsu(int n) :
    parent_(n),
    rank_(n)
{
    for (size_t i=0; i<n; ++i) make_set(i);
}

const int dsu::parent(int x) const
{
    return parent_[x];
}

const int dsu::rank(int x) const
{
    return rank_[x];
}

void dsu::make_set(int x)
{
    parent_[x] = x;
    rank_[x] = 1;
}

int dsu::unite_sets(int x, int y)
{
    x = find_set(x);
    y = find_set(y);
    if (x != y) {
        if (rank_[x] < rank_[y]) {
            std::swap(x, y);
        }
        parent_[y] = x;
        rank_[x] += rank_[y];
    }
    return x;
}

int dsu::find_set(int x)
{
    if (parent_[x] == x) {
        return x;
    } else {
        return (parent_[x] = find_set(parent_[x]));
    }
}

