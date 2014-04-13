#ifndef DSU_H
#define DSU_H
#include <vector>
#include <cstddef>

class dsu
{
    std::vector<int> parent_;
    std::vector<int> rank_;

public:
    dsu(int n);

    const int parent(int x) const;
    const int rank(int x) const;

    void make_set(int x);
    int unite_sets(int x, int y);
    int find_set(int x);
};

#endif // DSU_H
