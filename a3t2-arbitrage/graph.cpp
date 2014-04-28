#include "graph.h"

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
