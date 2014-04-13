#pragma once
#include <cstddef>
#include <vector>
#include <list>

//typedef size_t vertex_t;

struct Graph
{
    std::vector<std::list<size_t> > arcs_;

public:
    Graph(size_t size=0);
    Graph(const Graph &other);

    void addArc(size_t a, size_t b);
    Graph getInverted();
};
