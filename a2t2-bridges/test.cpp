#include "test.h"

#define MAX_TESTS 1000

#define GRAPH_SIZE 20
#define MIN_EDGES 5
#define MAX_EDGES 45

#ifndef MANUAL

void test_bridges() {

    // build a graph
    int n = GRAPH_SIZE;
    Graph g(n);
    vector<vector<int> > matrix(n, vector<int>(n, 0));
    int m = MIN_EDGES + rand()%(MAX_EDGES-MIN_EDGES);
    int x, y;
    for (int i=0; i<m; ++i) {
        x = rand()%n;
        y = rand()%(n-1);
        if (y == x) ++y;
        matrix[x][y] = 1;
    }
    for (int i=0; i<n; ++i) {
        for (int j=0; j<i+1; ++j) {
            if (matrix[i][j]) {
                g.addEdge(i+1, j+1);
            }
        }
    }

    // count scc's
    vector<int> unused;
    int k = condensation_tarjan(g, unused);

    // check each edge;
    vector<edge> sample;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<i+1; ++j) {
            if (matrix[i][j]) {
                matrix[i][j] = 0;
                Graph h(n);
                for (int x=0; x<n; ++x) {
                    for (int y=0; y<x+1; ++y) {
                        if (matrix[x][y]) {
                            h.addEdge(x+1, y+1);
                        }
                    }
                }
                if (condensation_tarjan(h, unused) > k) {
                    sample.push_back(edge(i+1, j+1));
                }
                matrix[i][j] = 1;
            }
        }
    }

    // run
    vector<edge> result;
    findBridges(g, result);

    // check the result against previous sample
    assert(is_permutation(result.begin(), result.end(), sample.begin()));
}

void test_points() {

    // build a graph
    int n = GRAPH_SIZE;
    Graph g(n);
    vector<vector<int> > matrix(n, vector<int>(n, 0));
    int m = MIN_EDGES + rand()%(MAX_EDGES-MIN_EDGES);
    int x, y;
    for (int i=0; i<m; ++i) {
        x = rand()%n;
        y = rand()%(n-1);
        if (y == x) ++y;
        matrix[x][y] = 1;
    }
    for (int i=0; i<n; ++i) {
        for (int j=0; j<i+1; ++j) {
            if (matrix[i][j]) {
                g.addEdge(i+1, j+1);
            }
        }
    }

    // count scc's
    vector<int> unused;
    int k = condensation_tarjan(g, unused);

    // check each vertex;
    vector<int> sample;
    for (int i=1; i<=n; ++i) {
        Graph h = g;
        int j = h.arcs_[i].front();
        while (!h.arcs_[i].empty()) {
            h.arcs_[j].remove(i);
            h.arcs_[i].erase(h.arcs_[i].begin());
        }
        if (condensation_tarjan(h, unused) > k+1) {
            sample.push_back(i);
        }
    }

    // run
    vector<int> result;
    findDivPoints(g, result);

    // check the result against previous sample
    assert(is_permutation(result.begin(), result.end(), sample.begin()));
}

void test() {

    for (int u=0; u<MAX_TESTS; ++u) test_bridges();

    for (int u=0; u<MAX_TESTS; ++u) test_points();
}

#endif
