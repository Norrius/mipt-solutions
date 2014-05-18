#include "graph.h"

Graph::Graph(size_t size) :
    edges(size)
{}

Graph::Graph(const Graph &other) :
    edges(other.edges)
{}
