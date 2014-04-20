#include "test.h"

#define MAX_TESTS 1000
#define MAX_GRAPH_SIZE 10
#define MIN_EDGES 5
#define MAX_EDGES 20

void test_positive() {

    // generate
    int n = 2+rand()%(MAX_GRAPH_SIZE-1);
    Graph g(n);
    int arc_count = 0;
    {
        int m = MIN_EDGES + rand()%(MAX_EDGES-MIN_EDGES);
        int current = 1;
        int next;
        for (int i=0; i<m; ++i) {
            if (i == m-1) {
                if (current != 1) {
                    next = 1;
                    g.addArc(current, next);
                    ++arc_count;
                }
                break;
            }
            next = 1+rand()%(n-1);
            if (next == current) ++next;
            g.addArc(current, next);
            ++arc_count;
            if (next == 1 && i >= MIN_EDGES) break;
            current = next;
        }
    }

    // run
    vector<int> cycle = find_cycle(g);

    // verify
    assert(cycle.size() == size_t(arc_count+1));

    assert(cycle[0] == cycle[cycle.size()-1]);

    int current = cycle[cycle.size()-1];
    int next;
    for (int i=cycle.size()-2; i>=0; --i) {
        next = cycle[i];
        list<size_t>::iterator edge = find(g.arcs_[current].begin(), g.arcs_[current].end(), next);
        assert(edge != g.arcs_[current].end());
        g.arcs_[current].erase(edge);
        current = next;
    }
}

void test_negative() {

    // generate
    int n = 2+rand()%(MAX_GRAPH_SIZE-1);
    Graph g(n);
    vector<int> arc_count(n+1, 0);

    bool expected = true;

    int x, y;
    int m = MIN_EDGES + rand()%(MAX_EDGES-MIN_EDGES);
    for (int i=0; i<m; ++i) {
        x = 1+rand()%n;
        y = 1+rand()%n;
        g.addArc(x, y);
        ++arc_count[x];
        --arc_count[y];
    }

    for (int i=1; i<=n; ++i) {
        if (arc_count[i]) {
            expected = false;
        }
    }

    // run
    vector<int> cycle = find_cycle(g);

    // verify
    if (expected == false) {
        assert(cycle.size() == 1);
        assert(cycle[0] == -1);
    }
}

void test() {
    srand(time(0));

    for (int u = 0; u < MAX_TESTS; ++u) test_positive();

    for (int u = 0; u < MAX_TESTS; ++u) test_negative();
}
