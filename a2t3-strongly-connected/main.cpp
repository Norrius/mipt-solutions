#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

int condensation_kosaraju(Graph &g, vector<int> &condensation);

int main()
{
    int n, m, x, y;
    cin >> n >> m;
    Graph g(n);
    for (int i=0; i<m; ++i) {
        cin >> x >> y;
        g.addArc(x, y);
    }

    vector<int> condensation(n+1);
    int k = condensation_kosaraju(g, condensation);

    cout << k << endl;
    for (int i=1; i<=n; ++i) {
        cout << condensation[i] << ' ';
    }
    cout << endl;

    return 0;
}

