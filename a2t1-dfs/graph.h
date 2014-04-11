#ifndef GRAPH_H
#define GRAPH_H
#include <cstddef>
#include <vector>
#include <list>

//typedef size_t vertex_t;

struct Graph
{
    std::vector<std::list<size_t> > arcs_;

public:
    Graph();

    void addArc(size_t a, size_t b);
};

#endif // GRAPH_H
