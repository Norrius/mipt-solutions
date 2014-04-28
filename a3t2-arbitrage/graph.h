#pragma once
#include <cstddef>
#include <vector>
#include <list>
#include <limits>

const int infty = std::numeric_limits<int>::max();

struct Graph
{
    std::vector<std::vector<std::pair<int, double> > > edges;

    Graph(size_t size=0);
    Graph(const Graph &other);

//    std::vector<double>& operator[](size_t i);
//    const std::vector<double> &operator[](size_t i) const;
};
