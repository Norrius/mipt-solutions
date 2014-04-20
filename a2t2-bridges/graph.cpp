#include "graph.h"

edge::edge(int from, int to) :
    from(from),
    to(to)
{}

bool operator==(const edge &larg, const edge &rarg)
{
    return (rarg.from == larg.from && rarg.to == larg.to) ||
           (rarg.from == larg.to && rarg.to == larg.from);
}

Graph::Graph(size_t size) :
    arcs_(size+1)
{}

Graph::Graph(const Graph &other) :
    arcs_(other.arcs_)
{}

size_t Graph::size()
{
    return arcs_.size()-1;
}

void Graph::addArc(size_t a, size_t b)
{
    if (std::max(a,b)+1 > arcs_.size()) {
        arcs_.resize(std::max(a,b)+1);
    }
    arcs_[a].push_back(b);
}

void Graph::addEdge(size_t a, size_t b)
{
    addArc(a, b);
    addArc(b, a);
}
