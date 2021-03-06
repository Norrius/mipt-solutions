#include "graph.h"

Graph::Graph()
{}

void Graph::addArc(size_t a, size_t b)
{
    if (std::max(a,b)+1 > arcs_.size()) {
        arcs_.resize(std::max(a,b)+1);
    }
    arcs_[a].push_back(b);
}
