#include "test.h"

void test_random_fb() {
    srand(time(0));
    int n = rand()%100;
    Graph g(n);
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            g.edges[i].push_back(edge(j, (i==j)?1:rand()%10));
        }
    }
    vector<int> path = ford_bellman(g);
    if (path.size()>1 && path[0] != -1) {
        double a = 1;
        for (int i=0; i+1<path.size(); ++i) {
            a *= find(g.edges[path[i]].begin(), g.edges[path[i]].end(), edge(path[i+1], 0))->weight;
        }
        assert(a > 1);
    }
}

void test_random_fw() {
    srand(time(0));
    int n = rand()%100;
    MGraph g(n);
    for (int i=0; i<n; ++i) {
        for (int j=0; j<n; ++j) {
            g.edges[i][j] = (i==j)?1:rand()%10;
        }
    }
    vector<int> path = floyd_warshall(g);
    if (path.size()>1 && path[0] != -1) {
        double a = 1;
        for (int i=0; i+1<path.size(); ++i) {
            a *= g.edges[path[i]][path[i+1]];
        }
        assert(a > 1);
    }
}

void test() {
    for (int u=0; u<1000; ++u) test_random_fb();

    for (int u=0; u<1000; ++u) test_random_fw();
}
