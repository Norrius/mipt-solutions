#pragma once
#include <vector>
#include <stack>
#include "graph.h"

using namespace std;

enum vertex_colour {
    white,
    gray,
    black
};

void findBridges(Graph &graph, vector<edge> &result);
void findDivPoints(Graph &graph, vector<int> &result);
