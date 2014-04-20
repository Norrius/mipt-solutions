#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include "graph.h"
#include "bridges.h"

using namespace std;

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

int main() {
    test_div_points();

    return 0;
}

