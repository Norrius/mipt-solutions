#pragma once
#include <cstddef>
#include <vector>
#include <list>

//typedef size_t vertex_t;

struct edge
{
    edge(int from, int to);
    int from;
    int to;
};
bool operator==(const edge &larg, const edge &rarg);

struct Graph
{
    std::vector<std::list<size_t> > arcs_;

public:
    Graph(size_t size=0);
    Graph(const Graph &other);

    size_t size();

    void addArc(size_t a, size_t b);
    void addEdge(size_t a, size_t b);
    Graph getInverted();
};
