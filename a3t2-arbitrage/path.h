#pragma once
#include "graph.h"
#include <vector>
#include <algorithm>

using namespace std;

vector<int> ford_bellman(Graph &g);
vector<int> floyd_warshall(MGraph g);
