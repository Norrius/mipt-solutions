#pragma once
#include <cstddef>
#include <vector>

struct Graph
{
    std::vector<std::vector<int> > edges;

    Graph(size_t size=0);
    Graph(const Graph &other);

};
