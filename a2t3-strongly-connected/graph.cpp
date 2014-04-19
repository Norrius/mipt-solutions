#include "graph.h"

Graph::Graph(size_t size) :
    arcs_(size+1)
{}

Graph::Graph(const Graph &other) :
    arcs_(other.arcs_)
{}

void Graph::addArc(size_t a, size_t b)
{
    if (std::max(a,b)+1 > arcs_.size()) {
        arcs_.resize(std::max(a,b)+1);
    }
    arcs_[a].push_back(b);
}

Graph Graph::getInverted()
{
    Graph inverted(arcs_.size());
    for (std::vector<std::list<size_t> >::iterator it = arcs_.begin(); it != arcs_.end(); ++it) {
        for (std::list<size_t>::iterator jt = it->begin(); jt != it->end(); ++jt) {
            inverted.arcs_[*jt].push_back(it-arcs_.begin());
        }
    }
    return inverted;
}
