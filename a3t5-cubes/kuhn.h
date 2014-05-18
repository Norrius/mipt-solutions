#pragma once
#include <vector>
#include "graph.h"
using namespace std;

const int N = 2; // number of sides

bool dfs_kuhn(Graph g, int v);
vector<pair<int, int> > assign_cubes(Graph g, size_t k);
