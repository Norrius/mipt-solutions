#include "kuhn.h"

namespace kuhn_ns {
vector<vector<char> > cubes;
vector<bool> used;
vector<int> matching;
}

bool dfs_kuhn(Graph g, int v) {
    using namespace kuhn_ns;

    if (used[v]) {
        return false;
    } else {
        used[v] = true;
        for (int i=0; i<g.edges[v].size(); ++i) {
            int j = g.edges[v][i];
            if (matching[j] == -1 || dfs_kuhn(g, matching[j])) {
                matching[j] = v;
                return true;
            }
        }
        return false;
    }
}

vector<pair<int, int> > assign_cubes(Graph g, size_t k) {
    using namespace kuhn_ns;
    int n = g.edges.size();
    matching.assign(k, -1);
    for (int i=0; i<n; ++i) {
        used.assign(n, false);
        dfs_kuhn(g, i);
    }
    vector<pair<int, int> > cubes;
    for (int i=0; i<matching.size(); ++i) {
        if (matching[i] != -1) {
            cubes.push_back(make_pair(i, matching[i]));
        }
    }
    return cubes;
}
