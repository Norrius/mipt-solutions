#pragma once
#include <cstddef>
#include <vector>
#include <list>
#include <limits>

const int infty = std::numeric_limits<int>::max();

struct edge {
    int to;
    double weight;
    edge(int to, double weight) :
        to(to),
        weight(weight)
    {}
};
bool operator==(const edge &larg, const edge &rarg);

struct Graph
{
    std::vector<std::vector<edge > > edges;

    Graph(size_t size=0);
    Graph(const Graph &other);

//    std::vector<double>& operator[](size_t i);
//    const std::vector<double> &operator[](size_t i) const;
};

struct MGraph
{
    std::vector<std::vector<double> > edges;

    MGraph(size_t size=0);
    MGraph(const MGraph &other);

//    std::vector<double>& operator[](size_t i);
//    const std::vector<double> &operator[](size_t i) const;
};
