#include <iostream>
#include <fstream>
#include "graph.h"
#include "path.h"
#include "test.h"

using namespace std;

void fb_ftest() {
    ifstream fin("arbitrage.in");
    size_t n;
    fin >> n;
    Graph g(n);

    double x;
    for (size_t i=0; i<n; ++i) {
        for (size_t j=0; j<n; ++j) {
            fin >> x;
            g.edges[i].push_back(edge(j, x));
        }
    }

    vector<int> cycle = ford_bellman(g);
    for (int v : cycle) {
        cout << v << ' ';
    }
    cout << endl;
}

void fw_ftest() {
    ifstream fin("arbitrage.in");
    size_t n;
    fin >> n;
    MGraph g(n);

    double x;
    for (size_t i=0; i<n; ++i) {
        for (size_t j=0; j<n; ++j) {
            fin >> x;
            g.edges[i][j] = x;
        }
    }

    vector<int> cycle = floyd_warshall(g);
    for (int v : cycle) {
        cout << v << ' ';
    }
    cout << endl;
}

int main()
{
//    fw_ftest();
    test();

    return 0;
}

