#include "graph.h"

bool operator==(const edge &larg, const edge &rarg) {
    return larg.to == rarg.to;
}

Graph::Graph(size_t size) :
    edges(size)
{}

Graph::Graph(const Graph &other) :
    edges(other.edges)
{}

/*std::vector<double> &Graph::operator[](size_t i) {
    return edges[i];
}

const std::vector<double> &Graph::operator[](size_t i) const {
    return edges[i];
}*/

MGraph::MGraph(size_t size) :
    edges(size, std::vector<double>(size, 0))
{}

MGraph::MGraph(const MGraph &other) :
    edges(other.edges)
{}
