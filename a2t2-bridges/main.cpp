#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include "graph.h"
#include "bridges.h"
#include "test.h"

using namespace std;

#ifdef MANUAL
void test_bridges() {
    int n, m, x, y;
    cin >> n >> m;
    vector<edge> edges;
    Graph g(n);
    for (int i=0; i<m; ++i) {
        cin >> x >> y;
        edges.push_back(edge(x, y));
        g.addEdge(x, y);
    }

    vector<edge> bridges;
    findBridges(g, bridges);

    cout << bridges.size() << endl;
    vector<edge>::iterator edge_it;
    for (vector<edge>::iterator it=bridges.begin(); it != bridges.end(); ++it) {
        edge_it = find(edges.begin(), edges.end(), *it);
        cout << edge_it-edges.begin()+1 << ' ';
    }
    cout << endl;
}

void test_div_points() {
    int n, m, x, y;
    cin >> n >> m;
    Graph g(n);
    for (int i=0; i<m; ++i) {
        cin >> x >> y;
        g.addEdge(x, y);
    }

    vector<int> points;
    findDivPoints(g, points);

    cout << points.size() << endl;
    for (vector<int>::iterator it=points.begin(); it != points.end(); ++it) {
        cout << *it << ' ';
    }
    cout << endl;
}

void test_biconnected_edges() {
    int n, m, x, y;
    cin >> n >> m;
    Graph g(n);
    for (int i=0; i<m; ++i) {
        cin >> x >> y;
        g.addEdge(x, y);
    }

    vector<int> components;
    findBiconnectedEdgeComponents(g, components);

    for (int i=1; i<=n; ++i) {
        cout << components[i] << ' ';
    }
    cout << endl;
}
#endif

int main() {
#ifdef MANUAL
    test_biconnected_edges();
#else
    test();
#endif

    return 0;
}

