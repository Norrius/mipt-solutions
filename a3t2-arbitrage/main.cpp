#include <iostream>
#include <fstream>
#include "graph.h"
#include "path.h"

using namespace std;

int main()
{
    ifstream fin("arbitrage.in");
    size_t n;
    fin >> n;
    Graph g(n);

    double x;
    for (size_t i=0; i<n; ++i) {
        for (size_t j=0; j<n; ++j) {
            fin >> x;
            g.edges[i].push_back(make_pair(j, x));
        }
    }

    ford_bellman(g, 0);

    return 0;
}

