#include <iostream>
#include <vector>
#include <algorithm>
#include "graph.h"
#include "condensation.h"
#include "dfs.h"

using namespace std;

int main()
{
    int n, m, x, y;

    // read the graph
    cin >> n >> m;
    Graph g(n);
    for (int i=0; i<m; ++i) {
        cin >> x >> y;
        g.addArc(x, y);
    }

    // find strongly connected components
    vector<int> condensation(n+1);
    int k = condensation_tarjan(g, condensation);

    // condensate the graph
    Graph c(k);
    for (int v=1; v<=n; ++v) {
        for (list<size_t>::iterator it = g.arcs_[v].begin(); it != g.arcs_[v].end(); ++it) {
            if (condensation[v] != condensation[*it]) {
                c.addArc(condensation[v], condensation[*it]);
            }
        }
    }

    // sort "topologically" condensated graph
    vector<int> sorted = topologic_sort(c);

    cout << k << endl;
    for (int i=1; i<=n; ++i) {
        cout << k-(find(sorted.begin(), sorted.end(), condensation[i])-sorted.begin()) << ' ';
    }
    cout << endl;

    return 0;
}

