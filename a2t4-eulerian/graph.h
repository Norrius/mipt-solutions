#pragma once
#include <cstddef>
#include <vector>
#include <list>

//typedef size_t vertex_t;

struct Graph
{

public:
    std::vector<std::list<size_t> > arcs_;
    Graph(size_t size=0);

    void addArc(size_t a, size_t b);
};
