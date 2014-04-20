#pragma once
#include <algorithm>
#include <vector>
#include <stack>
#include "graph.h"

using namespace std;

void findBridges(Graph &graph, vector<edge> &result);
void findDivPoints(Graph &graph, vector<int> &result);
