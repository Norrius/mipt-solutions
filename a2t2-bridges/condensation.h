#pragma once
#include <cstddef>
#include <vector>
#include <stack>
#include "graph.h"
using namespace std;

int condensation_kosaraju(Graph &g, vector<int> &condensation);
int condensation_tarjan(Graph &graph, vector<int> &condensation);
